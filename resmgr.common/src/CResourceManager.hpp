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
    CResourceManager(std::shared_ptr<CResourceManagerImpl> p_resmgrImpl);
    virtual ~CResourceManager();
    void init(const std::string path, const uint16_t amode);
    void run();
    void initcallback(const std::string& p_key, const impl::data::func_t& p_func);

private:
    std::shared_ptr<CResourceManagerImpl> p_impl;
};

} //namespace res

#endif /* SRC_CRESOURCEMANAGER_HPP_ */
