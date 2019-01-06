/*
 * CResourceMngFactory.cpp
 *
 *  Created on: Jan 5, 2019
 *      Author: YMLADENO
 */

#include "CResourceMngFactory.hpp"

namespace res {
namespace factory {

CResourceMngFactory::CResourceMngFactory() = default;
CResourceMngFactory::~CResourceMngFactory() = default;

std::shared_ptr<res::impl::CResourceManagerImpl> CResourceMngFactory::createResManagerImpl(ResManagerTypes type) {
    std::shared_ptr<res::impl::CResourceManagerImpl> pImpl;

//    if (!type.compare("qnx")) {
//        pImlp = make_shared<CQnxResMgrImpl>();
//    }
//    else {
//        pImlp = nullptr;
//    }

    return pImpl;
}

} //namespace res
} //namespace factory
