/*
 * Callback.cpp
 *
 *  Created on: Mar 12, 2019
 *      Author: YMLADENO
 */

#include "Callback.hpp"

Callback::Callback(Editor& p_editor) :
m_data{},
m_editor{p_editor} {
}

Callback::~Callback() = default;

void Callback::read(res::impl::data::data_t& p_callbackData) {
    auto& l_value = p_callbackData.m_read->m_data;

	if (m_editor.is_colorful()) {
	    l_value = m_editor.prefix() + m_data + m_editor.postfix();
	}
	else
	{
	    l_value = m_data;
	}
}

void Callback::write(res::impl::data::data_t& p_callbackData) {
    const auto& l_value = p_callbackData.m_write->m_data;
	m_data = l_value;
}

void Callback::devctl(res::impl::data::data_t& p_callbackData) {
    (void)p_callbackData;
}
