/*
 * CResourceManagerImpl.hpp
 *
 *  Created on: Dec 23, 2018
 *      Author: YMLADENO
 */

#ifndef SRC_CRESOURCEMANAGERIMPL_HPP_
#define SRC_CRESOURCEMANAGERIMPL_HPP_

#include <string>

namespace res {
namespace impl {

class CResourceManagerImpl {
public:
    CResourceManagerImpl();
    virtual ~CResourceManagerImpl();
    virtual void run(const std::string& path, const uint16_t amode) = 0;
};

} //namespace res
} //namespace impl


#endif /* SRC_CRESOURCEMANAGERIMPL_HPP_ */
