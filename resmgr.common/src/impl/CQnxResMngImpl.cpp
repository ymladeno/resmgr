/*
 * CQnxResMgrImpl.cpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#include "CQnxResMngImpl.hpp"
#include "error/AttachErr.hpp"
#include "data/CQnxData.hpp"
#include <cstdlib>
#include <stdexcept>

namespace res {
namespace impl {

CQnxResMngImpl::CQnxResMngImpl()
: dpp(nullptr),
  ctp(nullptr) {
    if ((dpp = dispatch_create()) == NULL) {
        throw std::runtime_error("Unable to allocate dispatch context");
    }
}

CQnxResMngImpl::~CQnxResMngImpl() = default;

void CQnxResMngImpl::run(const std::string& path, const uint16_t amode) {
    resmgr_data_t resmgr_data;

    //init structure
    init(amode, resmgr_data);
    //register to Process Manager
    attach(path, resmgr_data);
    //wait for msg
    loop();
}

int CQnxResMngImpl::io_open(resmgr_context_t *ctp, io_open_t *msg, RESMGR_HANDLE_T *handle, void *extra) {
    return iofunc_open_default(ctp, msg, handle, extra);
}

int CQnxResMngImpl::io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb) {
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

    data_t l_data{};
    m_callback["read"](l_data);

    ocb->attr->nbytes = l_data.size();

    //how many bytes are left
    std::int64_t l_nleft = ocb->attr->nbytes - ocb->offset;
    std::int64_t l_nbytes =std::min<int>(l_nleft, _IO_READ_GET_NBYTES(msg));

    data_t l_buffer{};
    if (l_nbytes) {
    	SETIOV(ctp->iov, l_buffer.data() + ocb->offset, l_nbytes);
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

int CQnxResMngImpl::io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb) {
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

    data_t l_data{};

    //resize buffer
    l_data.resize(l_nbytes+1);
    l_data[l_nbytes] = '\0';

    //Set up the number of bytes returned by client's write()
    _IO_SET_WRITE_NBYTES(ctp, l_nbytes);

    //Reread data from the sender's data buffer
    resmgr_msgread(ctp, const_cast<char*>(l_data.data()), l_nbytes, sizeof(msg->i));

    //buf[nbytes] = '\0'; //NULL terminated string
    fprintf(stdout, "Received %d bytes = %s\n", l_nbytes, l_data.c_str());

    if (l_nbytes > 0) {
        ocb->attr->flags |= IOFUNC_ATTR_MTIME | IOFUNC_ATTR_CTIME;
    }

    return (_RESMGR_NPARTS(0));
}

void CQnxResMngImpl::init(const uint16_t& amode, resmgr_data_t& r) {
    iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &r.connect_func, _RESMGR_IO_NFUNCS, &r.io_func);
    iofunc_attr_init(&r.attr, S_IFNAM | amode, 0, 0);

    memset(&r.resmgr_attr, 0, sizeof (r.resmgr_attr));
    r.resmgr_attr.nparts_max = 1;
    r.resmgr_attr.msg_max_size = 2048;

    //add my own functions
    r.connect_func.open = io_open;
    r.io_func.read = io_read;
    r.io_func.write = io_write;
}

void CQnxResMngImpl::attach(const std::string& path, resmgr_data_t& r) {

    //attach device name
    if (-1 == resmgr_attach(dpp,
                            &r.resmgr_attr,
                            path.c_str(),
                            _FTYPE_ANY,     // accepts any type of open request
                            0,              // accepts only requests for /dev/sample
                            &r.connect_func,
                            &r.io_func,
                            &r.attr)) {
        throw AttachErr{path};
    }
}


void CQnxResMngImpl::loop() {
    //allocate context structure
    ctp = dispatch_context_alloc(dpp);

    //start the resource manager message loop
    while(1) {
        if ((ctp = dispatch_block(ctp)) == NULL) {
            throw std::runtime_error("block error");
        }
        dispatch_handler(ctp);
    }
}

} //namespace res
} //namespace impl
