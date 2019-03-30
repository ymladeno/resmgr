/*
 * CQnxResData.cpp
 *
 *  Created on: Mar 26, 2019
 *      Author: YMLADENO
 */

#include "callback\CQnxCallback.hpp"
#include "CQnxResData.hpp"
#include "error/AttachErr.hpp"

CQnxResData::CQnxResData() :
m_data{},
m_path{} {
}

CQnxResData::~CQnxResData() = default;

void CQnxResData::init(const std::string& path, const uint16_t amode) {
    iofunc_func_init(_RESMGR_CONNECT_NFUNCS,
                    &m_data.connect_func,
                    _RESMGR_IO_NFUNCS,
                    &m_data.io_func);

    iofunc_attr_init(&m_data.attr, S_IFNAM | amode, 0, 0);

    memset(&m_data.resmgr_attr, 0, sizeof (m_data.resmgr_attr));
    m_data.resmgr_attr.nparts_max = 1;
    m_data.resmgr_attr.msg_max_size = 2048;

    //add my own functions
    m_data.connect_func.open = res::impl::callback::CQnxCallback::io_open;
    m_data.io_func.read  = res::impl::callback::CQnxCallback::io_read;
    m_data.io_func.write = res::impl::callback::CQnxCallback::io_write;

    m_path = path;
}

void CQnxResData::initcallback(const std::string& p_key, const func_t& p_func) {
    res::impl::callback::CQnxCallback::initcallback(p_key, p_func);
}

void CQnxResData::register_data(dispatch_t* p_dispatch) {

    //attach device name
    if (-1 == resmgr_attach(p_dispatch,
                            &m_data.resmgr_attr,
                            m_path.c_str(),
                            _FTYPE_ANY,     // accepts any type of open request
                            0,              // accepts only requests for /dev/sample
                            &m_data.connect_func,
                            &m_data.io_func,
                            &m_data.attr)) {
        throw AttachErr{m_path};
    }
}

void CQnxResData::deregister_data() {

}

