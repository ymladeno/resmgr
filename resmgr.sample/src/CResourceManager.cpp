/*
 * CResourceManager.cpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#include "CResourceManager.hpp"

CResourceManager::CResourceManager(CResourceManagerImpl& resmgrImpl)
: m_details{resmgrImpl} {
}

CResourceManager::~CResourceManager() = default;

void CResourceManager::run(const std::string path, const uint16_t amode) {
    m_details.run(path, amode);
}
