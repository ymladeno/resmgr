/*
 * CQnxCallbackData.hpp
 *
 *  Created on: Mar 31, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_IMPL_CALLBACK_CQNXCALLBACKDATA_HPP_
#define RESMGR_COMMON_SRC_IMPL_CALLBACK_CQNXCALLBACKDATA_HPP_

struct Open {
    std::int32_t m_errno;
};

struct Read {
    std::string m_buffer;
    std::int32_t m_errno;
};

struct Write {
    std::string m_buffer;
    std::int32_t m_errno;
};

struct CQnxCallbackData {
    //connect
    std::unique_ptr<Open> m_open;

    //io
    std::unique_ptr<Read> m_read;
    std::unique_ptr<Write> m_write;
};

#endif /* RESMGR_COMMON_SRC_IMPL_CALLBACK_CQNXCALLBACKDATA_HPP_ */
