/*
 * Callback.hpp
 *
 *  Created on: Mar 12, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_SAMPLE_SRC_CALLBACK_HPP_
#define RESMGR_SAMPLE_SRC_CALLBACK_HPP_

#include "CQnxData.hpp"
#include <string>

class Callback {
public:
	Callback();
	virtual ~Callback();
	void read(std::string& p_value);
	void write(std::string& p_value);

private:
	data_t m_data;
};

#endif /* RESMGR_SAMPLE_SRC_CALLBACK_HPP_ */
