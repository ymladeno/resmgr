/*
 * CQnxResMgrImpl.hpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#ifndef SRC_CQNXRESMGRIMPL_HPP_
#define SRC_CQNXRESMGRIMPL_HPP_

#include "CResourceManagerImpl.hpp"
#include "data/CQnxResData.hpp"
#include <vector>

namespace res {
namespace impl {

class CQnxResMngImpl: public res::CResourceManagerImpl {
public:
    CQnxResMngImpl();
    virtual ~CQnxResMngImpl();

    virtual void init(const std::string& path, const uint16_t amode) override;
    virtual void initcallback(const std::string& p_key, const data::func_t& p_func) override;
    virtual void run() override;

private:
    dispatch_t*         m_dispatch;
    dispatch_context_t* ctp;
    std::shared_ptr<data::CQnxResData> m_qnxdata;
};

} //namespace res
} //namespace impl


#endif /* SRC_CQNXRESMGRIMPL_HPP_ */
