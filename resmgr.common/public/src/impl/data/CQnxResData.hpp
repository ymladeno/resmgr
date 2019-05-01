/*
 * CQnxData.hpp
 *
 *  Created on: Mar 12, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_IMPL_DATA_CQNXRESDATA_HPP_
#define RESMGR_COMMON_SRC_IMPL_DATA_CQNXRESDATA_HPP_

#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <string>
#include "CQnxCallbackData.hpp"

namespace res  {
namespace impl {
namespace data {

class CQnxResData {
public:
    CQnxResData();
    ~CQnxResData();
    void init         (const std::string& path,  const uint16_t amode);
    void initcallback (const std::string& p_key, const func_t& p_func);
    void register_data(dispatch_t* p_dispatch);
    void deregister_data();

private:
    struct _resmgr_data {
        resmgr_attr_t          resmgr_attr;
        resmgr_connect_funcs_t connect_func;
        resmgr_io_funcs_t      io_func;
        iofunc_attr_t          attr;
    };
    using resmgr_data_t = _resmgr_data;

    resmgr_data_t    m_data;
    std::string      m_path;
    //res::impl::callback::CQnxCallbackData m_data;
};

}   //namespace data
}   //namespace impl
}   //namespace res

#endif /* RESMGR_COMMON_SRC_IMPL_DATA_CQNXRESDATA_HPP_ */
