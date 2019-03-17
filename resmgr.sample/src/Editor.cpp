/*
 * Editor.cpp
 *
 *  Created on: Mar 15, 2019
 *      Author: YMLADENO
 */

#include "Editor.hpp"

Editor::Editor() = default;

Editor::~Editor() = default;

void Editor::set_font_color(const std::string& p_font_color) {
    auto l_iter = m_font_color.find(p_font_color);
    if (l_iter == m_font_color.end()) {
        //throw
    }
    m_prefix = m_font_color[p_font_color];
}

void Editor::set_background_color(const std::string& p_background_color) {
    auto l_iter = m_background_color.find(p_background_color);
    if (l_iter == m_background_color.end()) {
        //throw
    }
    m_postfix = m_background_color[p_background_color];
}

