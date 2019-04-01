/*
 * CProxy.hpp
 *
 *  Created on: Mar 31, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_LIB_SERVICE_SRC_CPROXY_HPP_
#define RESMGR_LIB_SERVICE_SRC_CPROXY_HPP_

class CProxy {
public:
    CProxy();
    virtual ~CProxy();
    bool write(const std::string& s);
    bool read(std::string& s);
};

#endif /* RESMGR_LIB_SERVICE_SRC_CPROXY_HPP_ */
