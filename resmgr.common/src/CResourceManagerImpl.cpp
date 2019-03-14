/*
 * CResourceManagerImpl.cpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#include "CResourceManagerImpl.hpp"

namespace res {
namespace impl {

std::map<std::string, func_t> CResourceManagerImpl::m_callback;

CResourceManagerImpl::CResourceManagerImpl() = default;

CResourceManagerImpl::~CResourceManagerImpl() = default;

void CResourceManagerImpl::initcallback(const std::string& p_key, const func_t& p_func) {
//	auto l_iter = m_callback.emplace(m_callback.end(), p_key, p_func);
//	if (l_iter == m_callback.end()) {
//		//problem
//	}
	m_callback[p_key] = p_func;
}

} //namespace res
} //namespace impl


