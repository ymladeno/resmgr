/*
 * CToken.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: YMLADENO
 */

#include <cctype>
#include "CProgramArgument.hpp"

namespace res {
namespace parser {

CProgramArgument::CProgramArgument(const std::string& p_argument) :
m_kind{Kind::e_none},
m_argument{} {
    auto l_dash_pos = p_argument.find_first_not_of('-');

    switch(l_dash_pos) {
    case 0: {
        //argument
        m_kind     = Kind::e_argument;
        m_option.clear();
        m_argument = p_argument;
        break;
    }
    case 1: {
        //short option
        m_kind     = Kind::e_short;
        m_option   = p_argument.substr(0, l_dash_pos);
        m_argument.clear();
        break;
    }
    case 2: {
        //long option
        m_kind     = Kind::e_long;
        auto l_delimiter_pos = p_argument.find('=');
        m_option   = p_argument.substr(l_dash_pos, l_delimiter_pos-l_dash_pos);
        m_argument = p_argument.substr(l_delimiter_pos+1);
        break;
    }
    default:
        //error
        //not expected
        break;
    }
}

}   //namespace parser
}   //namespace res

