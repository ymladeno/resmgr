/*
 * CQnxResMgrImpl.cpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#include "CQnxResMngImpl.hpp"
#include "data/CQnxResData.hpp"
#include <cstdlib>
#include <stdexcept>

namespace res {
namespace impl {

CQnxResMngImpl::CQnxResMngImpl()
: m_dispatch(nullptr),
  ctp(nullptr),
  m_qnxdata{new CQnxResData} {
    if ((m_dispatch = dispatch_create()) == NULL) {
        throw std::runtime_error("Unable to allocate dispatch context");
    }
}

CQnxResMngImpl::~CQnxResMngImpl() = default;

void CQnxResMngImpl::init(const std::string& path, const uint16_t amode) {
    m_qnxdata->init(path, amode);
    m_qnxdata->register_data(m_dispatch);
}

void CQnxResMngImpl::initcallback(const std::string& p_key, const func_t& p_func) {
    m_qnxdata->initcallback(p_key, p_func);
}

void CQnxResMngImpl::run() {
    //allocate context structure
    ctp = dispatch_context_alloc(m_dispatch);

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
