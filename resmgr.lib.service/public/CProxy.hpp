/*
 * CProxy.hpp
 *
 *  Created on: Mar 31, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_LIB_SERVICE_SRC_CPROXY_HPP_
#define RESMGR_LIB_SERVICE_SRC_CPROXY_HPP_

#include <string>

namespace srv {
namespace sample {

class CManager;

class CProxy {
public:
    CProxy();
    virtual ~CProxy();
    bool write(const std::string& p_txt);
    bool read(std::string& p_txt);

private:
    std::unique_ptr<CManager> m_manager;
};

}
}

#endif /* RESMGR_LIB_SERVICE_SRC_CPROXY_HPP_ */
