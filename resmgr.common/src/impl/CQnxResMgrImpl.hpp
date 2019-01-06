/*
 * CQnxResMgrImpl.hpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#ifndef SRC_CQNXRESMGRIMPL_HPP_
#define SRC_CQNXRESMGRIMPL_HPP_

#include "CResourceManagerImpl.hpp"
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <vector>

namespace res {
namespace impl {

class CQnxResMgrImpl: public CResourceManagerImpl {
private:
    struct _resmgr_data {
        resmgr_attr_t resmgr_attr;
        resmgr_connect_funcs_t connect_func;
        resmgr_io_funcs_t io_func;
        iofunc_attr_t attr;
    };
    using resmgr_data_t = _resmgr_data;

public:
    using buffer_t = std::string;

    CQnxResMgrImpl();
    virtual ~CQnxResMgrImpl();
    virtual void run(const std::string& path, const uint16_t amode) override;

    std::string read();
    void write(std::string& s);

    static int io_open(resmgr_context_t *ctp, io_open_t *msg, RESMGR_HANDLE_T *handle, void *extra);
    static int io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb);
    static int io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb);

private:
    void init(const uint16_t& amode, resmgr_data_t& r);
    void attach(const std::string& path, resmgr_data_t& r);
    void loop();
    dispatch_t *dpp;
    dispatch_context_t *ctp;
    static buffer_t buf;
};

} //namespace res
} //namespace impl


#endif /* SRC_CQNXRESMGRIMPL_HPP_ */
