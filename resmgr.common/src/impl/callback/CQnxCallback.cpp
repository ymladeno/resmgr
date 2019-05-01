/*
 * CQnxCallback.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: YMLADENO
 */

#include "CQnxCallback.hpp"
#include "data/CQnxCallbackData.hpp"
#include "data/CQnxResDAta.hpp"

#include <devctl.h>

namespace res {
namespace impl {
namespace callback {

std::map<std::string, res::impl::data::func_t> CQnxCallback::m_callback;

template<typename type_t>
struct XXX;

CQnxCallback::CQnxCallback() {
    // TODO Auto-generated constructor stub
}

CQnxCallback::~CQnxCallback() {
    // TODO Auto-generated destructor stub
}

int CQnxCallback::io_open(resmgr_context_t *ctp, io_open_t *msg, RESMGR_HANDLE_T *handle, void *extra) {
    return iofunc_open_default(ctp, msg, handle, extra);
}

int CQnxCallback::io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb) {
    int l_status{};
    int l_nparts{};

    //verify that device is opened for read
    if ((l_status = iofunc_read_verify(ctp, msg, ocb, NULL)) != EOK) {
        return l_status;
    }

    //check xtype
    if (msg->i.xtype & _IO_XTYPE_MASK != _IO_XTYPE_NONE) {
        return ENOSYS;
    }

    res::impl::data::CQnxCallbackData l_callback_data{};
    auto& l_buffer = l_callback_data.m_read;

    if (!l_buffer) {
        l_buffer.reset(new res::impl::data::Read{});
    }
    auto& l_data   = l_buffer->m_data;

    if (!ocb->offset) {
        m_callback["read"](l_callback_data);
    }

    ocb->attr->nbytes = l_data.size();

    //how many bytes are left
    std::int64_t l_nleft  {ocb->attr->nbytes - ocb->offset};
    std::int64_t l_nbytes {std::min<std::int64_t>(l_nleft, _IO_READ_GET_NBYTES(msg))};

    if (l_nbytes > 0) {
        SETIOV(ctp->iov, l_data.data() + ocb->offset, l_nbytes);
        _IO_SET_READ_NBYTES(ctp, l_nbytes);

        ocb->offset += l_nbytes;
        l_nparts = 1;
    }
    else {
        //do not return data, just unblock client
        _IO_SET_READ_NBYTES(ctp, 0);
        l_nparts = 0;
    }

    if (msg->i.nbytes > 0) {
        ocb->attr->flags |= IOFUNC_ATTR_ATIME;
    }

    return (_RESMGR_NPARTS(l_nparts));
}

int CQnxCallback::io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb) {
    int l_status{};

    //verify writing permissions
    if ((l_status = iofunc_write_verify(ctp, msg, ocb, NULL)) != EOK) {
        return (l_status);
    }

    //verify the type of input msg
    if ((msg->i.xtype & _IO_XTYPE_MASK) != _IO_XTYPE_NONE) {
        return (ENOSYS);
    }

    //Extract the length of client msg
    off_t l_nbytes {static_cast<off_t>(_IO_WRITE_GET_NBYTES(msg))};
    //ocb->attr->nbytes = nbytes;

    //Filter out malicious write requests that attempt to write more data than are available in msg
    if (l_nbytes > ctp->info.srcmsglen - ctp->offset - sizeof(io_write_t)) {
        return EBADMSG;
    }

    res::impl::data::CQnxCallbackData l_callback_data{};
    auto& l_buffer = l_callback_data.m_write;
    if(!l_buffer) {
        l_buffer.reset(new res::impl::data::Write{});
    }
    auto& l_data = l_buffer->m_data;

    //resize buffer
    l_data.resize(l_nbytes+1);
    l_data[l_nbytes] = '\0';

    //Set up the number of bytes returned by client's write()
    _IO_SET_WRITE_NBYTES(ctp, l_nbytes);

    //Reread data from the sender's data buffer
    resmgr_msgread(ctp, const_cast<char*>(l_data.data()), l_nbytes, sizeof(msg->i));

    //buf[nbytes] = '\0'; //NULL terminated string
    fprintf(stdout, "Received %d bytes = %s\n", l_nbytes, l_data.c_str());

    m_callback["write"](l_callback_data);

    if (l_nbytes > 0) {
        ocb->attr->flags |= IOFUNC_ATTR_MTIME | IOFUNC_ATTR_CTIME;
    }

    return (_RESMGR_NPARTS(0));
}

int CQnxCallback::io_devctl(resmgr_context_t *ctp, io_devctl_t *msg, RESMGR_OCB_T *ocb) {
    std::uint32_t l_status{EOK};

    //check system devctl's
    if ((l_status = iofunc_devctl_default(ctp, msg, ocb)) != _RESMGR_DEFAULT) {
        return l_status;
    }

    std::size_t l_sz_msg   {sizeof(msg)     };
    std::size_t l_sz_imsg  {sizeof(msg->i)  };
    std::size_t l_sz_req   {get_device_size(msg->i.dcmd)};
    auto l_sz_dst = ctp->info.dstmsglen;
    auto l_sz_src = ctp->info.srcmsglen;

    //read coming msg
    res::impl::data::CQnxCallbackData l_callback_data{};
    auto& l_devctl = l_callback_data.m_devctl;

    if (!l_devctl) {
        l_devctl.reset(new res::impl::data::Devctl{});
    }
    l_devctl->m_i_dcmd    = msg->i.dcmd;
    l_devctl->m_i_bytes   = msg->i.nbytes;
    l_devctl->m_o_bytes   = 0;
    l_devctl->m_o_ret_val = 0;

    if (l_sz_req == 0) {
        l_devctl->m_io_data = nullptr;
    }
    else {
        l_devctl->m_io_data =_DEVCTL_DATA(msg->i);
    }
    //std::string& l_data = l_devctl->m_io_data;

//    //call callback to handle custom command
//    //...
    //m_callback["devctl"](l_data);
//
//    //clear return buffer
//    memset(ctp->msg.o, 0, sizeof(ctp->msg.o));
//    SETIOV(ctp->iov, reply, sizeof(*reply) + l_nbytes);
    return _RESMGR_NPARTS(1);
}

void CQnxCallback::initcallback(const std::string& p_key, const res::impl::data::func_t& p_func) {
    m_callback[p_key] = p_func;
}

}   //callback
}   //impl
}   //res
