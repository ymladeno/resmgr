/*
 * CQnxCallbackData.hpp
 *
 *  Created on: Mar 31, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_IMPL_CALLBACK_CQNXCALLBACKDATA_HPP_
#define RESMGR_COMMON_SRC_IMPL_CALLBACK_CQNXCALLBACKDATA_HPP_

#include <string>
#include <functional>

namespace res  {
namespace impl {
namespace data {

struct Open {
    std::int32_t m_errno;
};

struct Read {
    std::string  m_data;
    std::int32_t m_errno;
};

struct Write {
    std::string  m_data;
    std::int32_t m_errno;
};

struct Devctl {
    std::uint32_t m_i_dcmd;
    std::uint32_t m_i_bytes;
    void*         m_io_data;
    std::uint32_t m_o_bytes;
    std::int32_t  m_o_ret_val;
    std::int32_t  m_errno;
};

struct CQnxCallbackData {
    //connect
    std::unique_ptr<Open>   m_open;

    //io
    std::unique_ptr<Read>   m_read;
    std::unique_ptr<Write>  m_write;
    std::unique_ptr<Devctl> m_devctl;
};

using data_t = CQnxCallbackData;
using func_t = std::function<void(data_t&)>;

}   //namespace data
}   //namespace impl
}   //namespace res

#endif /* RESMGR_COMMON_SRC_IMPL_CALLBACK_CQNXCALLBACKDATA_HPP_ */
