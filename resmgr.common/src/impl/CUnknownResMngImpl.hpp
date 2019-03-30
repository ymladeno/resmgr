/*
 * CUnknownResourceManagerImpl.hpp
 *
 *  Created on: Jan 6, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_IMPL_CUNKNOWNRESOURCEMANAGERIMPL_HPP_
#define RESMGR_COMMON_SRC_IMPL_CUNKNOWNRESOURCEMANAGERIMPL_HPP_

#include "CResourceManagerImpl.hpp"

namespace res {
namespace impl {

class CUnknownResMngImpl: public res::CResourceManagerImpl {
public:
    CUnknownResMngImpl();
    virtual ~CUnknownResMngImpl();
    virtual void init        (const std::string& path, const uint16_t amode) override;
    virtual void initcallback(const std::string& p_key, const func_t& p_func) override;
    virtual void run() override;
};

} //namespace res
} //namespace impl


#endif /* RESMGR_COMMON_SRC_IMPL_CUNKNOWNRESOURCEMANAGERIMPL_HPP_ */
