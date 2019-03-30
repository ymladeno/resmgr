/*
 * CQnxCallback.hpp
 *
 *  Created on: Mar 25, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_CALLBACK_CQNXCALLBACK_HPP_
#define RESMGR_COMMON_SRC_CALLBACK_CQNXCALLBACK_HPP_

#include <string>
#include <map>
#include <sys/iofunc.h>
#include "data\DataType.hpp"

namespace res {
namespace impl {
namespace callback {

class CQnxCallback {
public:
    CQnxCallback();
    virtual ~CQnxCallback();

    static int io_open(resmgr_context_t *ctp, io_open_t *msg, RESMGR_HANDLE_T *handle, void *extra);
    static int io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb);
    static int io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb);
    static void initcallback(const std::string& p_key, const func_t& p_func);

private:
    static std::map<std::string, func_t> m_callback;
};

}   //callback
}   //impl
}   //res

#endif /* RESMGR_COMMON_SRC_CALLBACK_CQNXCALLBACK_HPP_ */
