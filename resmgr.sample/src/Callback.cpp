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

void Callback::read(std::string& p_value) {
	p_value = m_editor.prefix() + m_data + m_editor.postfix();
}

void Callback::write(std::string& p_value) {
	m_data = p_value;
}
