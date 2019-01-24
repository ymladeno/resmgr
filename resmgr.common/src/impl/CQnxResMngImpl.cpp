/*
 * CQnxResMgrImpl.cpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#include "CQnxResMngImpl.hpp"
#include "error/AttachErr.hpp"
#include <cstdlib>
#include <stdexcept>

namespace res {
namespace impl {

CQnxResMngImpl::buffer_t CQnxResMngImpl::buf;

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
    int status;
    int nleft;
    int off;
    int xtype;
    struct _xtype_offset *xoffset;
    int nbytes;

    //verify that device is opened for read
    if ((status = iofunc_read_verify(ctp, msg, ocb, NULL)) != EOK) {
        return status;
    }

    //check xtype
    xtype = msg->i.xtype & _IO_XTYPE_MASK;
    if (xtype == _IO_XTYPE_OFFSET) {
        xoffset = (struct _xtype_offset*)(&msg->i + 1);
        off = xoffset->offset;
    }
    else if (xtype == _IO_XTYPE_NONE) {
        off = ocb->offset;
    }
    else {
        return ENOSYS;
    }

    //how many bytes are left
    nleft = buf.size() - off;
    ocb->offset += nleft;

    //number of bytes returning to the client
    nbytes = std::min<int>(nleft, _IO_READ_GET_NBYTES(msg));

    //if returning data, write it to client
    if (nbytes) {
        MsgReply(ctp->rcvid, nbytes, static_cast<void*>(&buf.at(0)), nbytes);
    }
    else {
        //do not return data, just unblock client
        MsgReply(ctp->rcvid, EOK, NULL, 0);
    }

    //indicate we already did MsgReply to the library
    return (_RESMGR_NOREPLY);
}

int CQnxResMngImpl::io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb) {
    int status;
    size_t nbytes;

    //verify writing permissions
    if ((status = iofunc_write_verify(ctp, msg, ocb, NULL)) != EOK) {
        return (status);
    }

    //verify the type of input msg
    if ((msg->i.xtype & _IO_XTYPE_MASK) != _IO_XTYPE_NONE) {
        return (ENOSYS);
    }

    //Extract the length of client msg
    nbytes = _IO_WRITE_GET_NBYTES(msg);
    //ocb->attr->nbytes = nbytes;

    //Filter out malicious write requests that attempt to write more data than are available in msg
    if (nbytes > ctp->info.srcmsglen - ctp->offset - sizeof(io_write_t)) {
        return EBADMSG;
    }

    //resize buffer
    buf.resize(nbytes);

    //Set up the number of bytes returned by client's write()
    _IO_SET_WRITE_NBYTES(ctp, nbytes);

    //Reread data from the sender's data buffer
    resmgr_msgread(ctp, static_cast<void*>(&buf.at(0)), nbytes, sizeof(msg->i));
    //buf[nbytes] = '\0'; //NULL terminated string
    fprintf(stdout, "Received %d bytes = %s\n", nbytes, buf.c_str());

    if (nbytes > 0) {
        ocb->attr->flags |= IOFUNC_ATTR_MTIME | IOFUNC_ATTR_CTIME;
    }

    return (_RESMGR_NPARTS(0));
}

std::string CQnxResMngImpl::read() {
    return "";
}

void CQnxResMngImpl::write(std::string& s) {

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
