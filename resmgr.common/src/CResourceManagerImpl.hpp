/*
 * CResourceManagerImpl.hpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#ifndef SRC_CRESOURCEMANAGERIMPL_HPP_
#define SRC_CRESOURCEMANAGERIMPL_HPP_

#include <string>
#include <functional>
#include "DataType.hpp"

namespace res {

class CResourceManagerImpl {
public:
    CResourceManagerImpl();
    virtual ~CResourceManagerImpl();
    virtual void init(const std::string& path, const uint16_t amode) = 0;
    virtual void initcallback(const std::string& p_key, const func_t& p_func) = 0;
    virtual void run() = 0;
};

} //namespace res


#endif /* SRC_CRESOURCEMANAGERIMPL_HPP_ */
