/*
 * InvalidFile.hpp
 *
 *  Created on: Apr 11, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_LIB_SERVICE_SRC_EXCEPTIONS_INVALIDFILE_HPP_
#define RESMGR_LIB_SERVICE_SRC_EXCEPTIONS_INVALIDFILE_HPP_

#include <exception>

namespace exception {

class InvalidFile : public std::exception {
public:
    InvalidFile() = default;
    virtual ~InvalidFile() = default;
};

} /* namespace exception */

#endif /* RESMGR_LIB_SERVICE_SRC_EXCEPTIONS_INVALIDFILE_HPP_ */
