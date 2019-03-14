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
#include <map>

namespace res {
namespace impl {

using func_t = std::function<void(std::string&)>;

class CResourceManagerImpl {
public:
    CResourceManagerImpl();
    virtual ~CResourceManagerImpl();
    virtual void run(const std::string& path, const uint16_t amode) = 0;
    void initcallback(const std::string& p_key, const func_t& p_func);

protected:
    static std::map<std::string, func_t> m_callback;
};

} //namespace res
} //namespace impl


#endif /* SRC_CRESOURCEMANAGERIMPL_HPP_ */
