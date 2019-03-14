/*
 * InvalidArgument.hpp
 *
 *  Created on: Mar 12, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_ERROR_INVALIDARGUMENT_HPP_
#define RESMGR_COMMON_SRC_ERROR_INVALIDARGUMENT_HPP_

class InvalidArgument : public std::runtime_error {
	InvalidArgument(std::string& s) : runtime_error(s) {}
};



#endif /* RESMGR_COMMON_SRC_ERROR_INVALIDARGUMENT_HPP_ */
