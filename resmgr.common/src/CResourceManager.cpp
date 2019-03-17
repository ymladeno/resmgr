/*
 * CResourceManager.cpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#include "CResourceManager.hpp"

namespace res {

CResourceManager::CResourceManager(std::shared_ptr<CResourceManagerImpl> p_resmgrImpl)
: p_impl{p_resmgrImpl} {
}

CResourceManager::~CResourceManager() = default;

void CResourceManager::run(const std::string path, const uint16_t amode) {
    p_impl->run(path, amode);
}

void CResourceManager::initcallback(const std::string& p_key, const func_t& p_func) {
	p_impl->initcallback(p_key, p_func);
}

}
