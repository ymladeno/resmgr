/*
 * CBadAttached.hpp
 *
 *  Created on: Jan 23, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_ERROR_ATTACHERR_HPP_
#define RESMGR_COMMON_SRC_ERROR_ATTACHERR_HPP_

#include <string>

class AttachErr : public std::runtime_error {
public:
    AttachErr(const std::string& s) : std::runtime_error{"Unable to attach name " + s} {}
    virtual ~AttachErr() = default;
};

#endif /* RESMGR_COMMON_SRC_ERROR_ATTACHERR_HPP_ */
