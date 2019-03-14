/*
 * Callback.cpp
 *
 *  Created on: Mar 12, 2019
 *      Author: YMLADENO
 */

#include "Callback.hpp"

Callback::Callback() {
	// TODO Auto-generated constructor stub

}

Callback::~Callback() {
	// TODO Auto-generated destructor stub
}

void Callback::read(std::string& p_value) {
	p_value = m_data;
}

void Callback::write(std::string& p_value) {
	m_data = p_value;
}
