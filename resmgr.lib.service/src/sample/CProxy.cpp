/*
 * CProxy.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: YMLADENO
 */

#include "CProxy.hpp"
#include "CManager.hpp"

namespace srv {
namespace sample {

CProxy::CProxy() : m_manager{new CManager{}} {
}

CProxy::~CProxy() {
}

bool CProxy::write(const std::string& p_txt) {
    return m_manager->write(p_txt);
}

bool CProxy::read(std::string& p_txt) {
    return m_manager->read(p_txt);
}

bool CProxy::set_background_color() {
    return m_manager->set_background_color();
}

bool CProxy::set_font() {
    return m_manager->set_font();
}

bool CProxy::set_font_color(te_color p_color) {
    return m_manager->set_font_color(p_color);
}

bool CProxy::get_background_color() {
    return m_manager->get_background_color();
}

bool CProxy::get_font() {
    return m_manager->get_font();
}

bool CProxy::get_font_color() {
    return m_manager->get_font_color();
}

}
}
