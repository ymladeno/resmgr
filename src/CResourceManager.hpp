/*
 * CResourceManager.hpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#ifndef SRC_CRESOURCEMANAGER_HPP_
#define SRC_CRESOURCEMANAGER_HPP_

#include "CResourceManagerImpl.hpp"

class CResourceManager {
public:
    CResourceManager(CResourceManagerImpl& resmgrImpl);
    virtual ~CResourceManager();
    void run(const std::string path, const uint16_t amode);

private:
    CResourceManagerImpl& m_details;
};

#endif /* SRC_CRESOURCEMANAGER_HPP_ */
