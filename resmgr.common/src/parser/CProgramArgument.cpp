/*
 * CToken.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: YMLADENO
 */

#include <cctype>
#include "CProgramArgument.hpp"

CProgramArgument CProgramArgument::get_command_line_argument(const std::string& p_option) {

    //long option
    if ((p_option[0] == '-') && (p_option[1] == '-')) {

        std::string delimiter = "=";
        auto delimiter_position = p_option.find(delimiter);
        if (delimiter_position == std::string::npos) {
            return CProgramArgument{Kind::error};
        }

        option.config = Config::elong;
        kind = Kind::argument;
        option.string_value = p_option.substr(2, delimiter_position-2);
        argument = p_option.substr(delimiter_position+1);
    }
    //short option
    else if (p_option[0] == '-') {
        option.config = Config::eshort;
        kind = Kind::option;
        option.char_value = p_option[1];
    }
    //argument for short option is separate string
    else if ((kind == Kind::option) && (option.config == Config::eshort)) {
        argument = p_option;
        kind = Kind::argument;
    }
    else {
        kind = Kind::error;
    }
    return *this;
}

