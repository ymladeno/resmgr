/*
 * Callback.hpp
 *
 *  Created on: Mar 12, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_SAMPLE_SRC_CALLBACK_HPP_
#define RESMGR_SAMPLE_SRC_CALLBACK_HPP_

#include "impl/data/CQnxCallbackData.hpp"
#include "Editor.hpp"

class Callback {
public:
	Callback(Editor& p_editor);
	virtual ~Callback();
	void read  (res::impl::data::data_t& p_callbackData);
	void write (res::impl::data::data_t& p_callbackData);
	void devctl(res::impl::data::data_t& p_callbackData);

private:
	std::string  m_data;
	Editor& m_editor;
};

#endif /* RESMGR_SAMPLE_SRC_CALLBACK_HPP_ */
