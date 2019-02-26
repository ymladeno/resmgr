/*
 * CToken.hpp
 *
 *  Created on: Feb 23, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_PARSER_CPROGRAMARGUMENT_HPP_
#define RESMGR_COMMON_SRC_PARSER_CPROGRAMARGUMENT_HPP_

#include <string>

enum class Config {
    eshort,
    elong
};

enum class Kind {
    none, option, argument, end, error
};

struct CProgramOption {
    Config config;
    std::string string_value;
    char char_value;
};

struct CProgramArgument {
    Kind kind;
    CProgramOption option;
    std::string argument;
    CProgramArgument get_command_line_argument(const std::string& p_option);
};

struct Config_error {

};

#endif /* RESMGR_COMMON_SRC_PARSER_CPROGRAMARGUMENT_HPP_ */
