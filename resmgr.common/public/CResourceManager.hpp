/*
 * CResourceManager.hpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#ifndef SRC_CRESOURCEMANAGER_HPP_
#define SRC_CRESOURCEMANAGER_HPP_

#include "CResourceManagerImpl.hpp"
#include <memory>

namespace res {

class CResourceManager {
public:
    CResourceManager(std::shared_ptr<impl::CResourceManagerImpl> p_resmgrImpl);
    virtual ~CResourceManager();
    void run(const std::string path, const uint16_t amode);

private:
    std::shared_ptr<impl::CResourceManagerImpl> p_impl;
};

} //namespace res

#endif /* SRC_CRESOURCEMANAGER_HPP_ */
