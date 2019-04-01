/*
 * CResourceMngFactory.cpp
 *
 *  Created on: Jan 5, 2019
 *      Author: YMLADENO
 */

#include "CQnxResMngImpl.hpp"
#include "CUnknownResMngImpl.hpp"
#include "CResourceMngFactory.hpp"

namespace res {
namespace factory {

CResourceMngFactory::CResourceMngFactory() = default;
CResourceMngFactory::~CResourceMngFactory() = default;

std::shared_ptr<res::CResourceManagerImpl> CResourceMngFactory::createResManagerImpl(const ResManagerTypes type) {
    std::shared_ptr<res::CResourceManagerImpl> pImpl;

    if (type == ResManagerTypes::QnxResourceManager) {
        pImpl = std::make_shared<res::impl::CQnxResMngImpl>();
    }
    else {
        pImpl = std::make_shared<res::impl::CUnknownResMngImpl>();
    }

    return pImpl;
}

} //namespace factory
} //namespace res
