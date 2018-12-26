#include "CQnxResMgrImpl.hpp"
#include "CResourceManager.hpp"

#define READ_WRITE_ACCESS 0x0666

/* */
/*
#define FILE_ATTACHED "/dev/sample"
#define PRINT_FUNC_NAME fprintf(stdout, __FUNCTION__)

//inline static void print(const char* s) {
//	fprintf(stdout, __FUNCTION__);
//	//fflush(stdout);
//}

extern char* __progname;
//std::vector<uint8_t> buf;
//std::string buf;
char buf[20];

static int	my_io_open(resmgr_context_t *ctp, io_open_t *msg, RESMGR_HANDLE_T *handle, void *extra) {
    return iofunc_open_default(ctp, msg, handle, extra);
}

static int my_io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb) {
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
    //nleft = strlen(buf) - off;
    nleft = strlen(buf) - off;
    ocb->offset += nleft;
    //ocb->attr->nbytes -= nleft;

    //number of bytes returning to the client
    nbytes = std::min<int>(nleft, _IO_READ_GET_NBYTES(msg));

    //if returning data, write it to client
    if (nbytes) {
        MsgReply(ctp->rcvid, nbytes, buf, nbytes);
    }
    else {
        //do not return data, just unblock client
        MsgReply(ctp->rcvid, EOK, NULL, 0);
    }

    //indicate we already did MsgReply to the library
    return (_RESMGR_NOREPLY);
}

static int my_io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb) {
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

    //Set up the number of bytes returned by client's write()
    _IO_SET_WRITE_NBYTES(ctp, nbytes);

    //Reread data from the sender's data buffer
    resmgr_msgread(ctp, buf, nbytes, sizeof(msg->i));
    buf[nbytes] = '\0'; //NULL terminated string
    fprintf(stdout, "Received %d bytes = %s\n", nbytes, buf);

    if (nbytes > 0) {
        ocb->attr->flags |= IOFUNC_ATTR_MTIME | IOFUNC_ATTR_CTIME;
    }

    return (_RESMGR_NPARTS(0));
}

int main() {
    dispatch_t *dpp;
    dispatch_context_t *ctp;
    resmgr_attr_t resmgr_attr;
    resmgr_connect_funcs_t connect_func;
    resmgr_io_funcs_t io_func;
    iofunc_attr_t attr;

    if ((dpp = dispatch_create()) == NULL) {
        fprintf(stderr, "%s: Unable to allocate dispatch context.\n", __progname);
        return EXIT_FAILURE;
    }

    iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &connect_func, _RESMGR_IO_NFUNCS, &io_func);
    iofunc_attr_init(&attr, S_IFNAM | 0666, 0, 0);

    memset(&resmgr_attr, 0, sizeof (resmgr_attr));
    resmgr_attr.nparts_max = 1;
    resmgr_attr.msg_max_size = 2048;

    //add my own functions
    connect_func.open = my_io_open;
    io_func.read = my_io_read;
    io_func.write = my_io_write;

    //attach device name
    if (-1 == resmgr_attach(dpp,
                            &resmgr_attr,
                            FILE_ATTACHED,
                            _FTYPE_ANY,     // accepts any type of open request
                            0,              // accepts only requests for /dev/sample
                            &connect_func,
                            &io_func,
                            &attr)) {
        fprintf(stderr, "%s: Unable to attach name.\n", FILE_ATTACHED);
        return EXIT_FAILURE;
    }

    //allocate context structure
    ctp = dispatch_context_alloc(dpp);

    //start the resource manager message loop
    while(1) {
        if ((ctp = dispatch_block(ctp)) == NULL) {
            fprintf(stderr, "block error\n");
            return EXIT_FAILURE;
        }
        dispatch_handler(ctp);
    }

	return 0;
}
*/

int main() {
    CQnxResMgrImpl qnxResMgr;
    CResourceManager resmgr(qnxResMgr);

    //call blocked mehtod
    resmgr.run("/dev/sample", READ_WRITE_ACCESS);
    //normally never execute code after line above

    return 0;
}
