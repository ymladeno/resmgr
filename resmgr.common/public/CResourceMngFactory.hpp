/*
 * CResMngFactory.hpp
 *
 *  Created on: Jan 5, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_FACTORY_CRESMNGFACTORY_HPP_
#define RESMGR_COMMON_SRC_FACTORY_CRESMNGFACTORY_HPP_

#include "CResourceManagerImpl.hpp"
#include <memory>

namespace res {
namespace factory {

class CResourceMngFactory {
public:
    enum class ResManagerTypes {
        QnxResourceManager,
        Unknown
    };
    CResourceMngFactory();
    virtual ~CResourceMngFactory();
    std::shared_ptr<res::impl::CResourceManagerImpl> createResManagerImpl(const ResManagerTypes type);
};

} //namespace res
} //namespace factory

#endif /* RESMGR_COMMON_SRC_FACTORY_CRESMNGFACTORY_HPP_ */
