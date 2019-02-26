/*
 * CommandLineParser.cpp
 *
 *  Created on: Feb 21, 2019
 *      Author: YMLADENO
 */

#include "CommandLine.hpp"
#include <iostream>

namespace res {
namespace parser {

CommandLine::CommandLine() {

}

CommandLine::~CommandLine() {
    // TODO Auto-generated destructor stub
}

void CommandLine::add_option(const char l_short, const std::string& l_long, const std::string& l_description) {
    auto l_data_iter = m_init_options.emplace(m_init_options.end(), data_t{l_short, l_long, l_description});

    if (l_data_iter == m_init_options.end()) {
        std::cout << "Cannot put element in m_prog_arguments\n";
    }

    auto l_short_iter = m_input_short.emplace(std::piecewise_construct, std::forward_as_tuple(l_short), std::forward_as_tuple(l_data_iter));

    if (!l_short_iter.second) {
        std::cout << "m_input_short error";
    }

    auto l_long_iter = m_input_long.emplace(std::piecewise_construct, std::forward_as_tuple(l_long), std::forward_as_tuple(l_data_iter));

    if (!l_long_iter.second) {
        std::cout << "m_input_long error";
    }
}

//read 1 option + 1 argument. for example:
//option    argument
//-c        /etc/res.ini
void CommandLine::parse(const int argc, const char* argv[]) {
    std::vector<std::string> vargv = arguments(argc, argv);

    CProgramArgument l_argument{Kind::none};
    std::vector<CProgramArgument> v_arguments;

    for (const auto& a : vargv) {
        l_argument = l_argument.get_command_line_argument(a);

        if (l_argument.kind == Kind::option) {
            continue;
        }
        else if (l_argument.kind != Kind::error) {
            v_arguments.push_back(l_argument);
            l_argument = {Kind::none};
        }
        else {
            throw Config_error{};
        }
    }

    fill_map_arguments(v_arguments);
}

std::string CommandLine::get_program_argument(const char& p_option) {
    return get_program_argument(std::string{p_option});
}

std::string CommandLine::get_program_argument(const std::string& p_option) {
    auto l_iter = m_map_arguments.find(p_option);
    if (l_iter == m_map_arguments.end()) {
        return "";
    }
    return l_iter->second.argument;
}

std::vector<std::string> CommandLine::arguments(const int argc, const char* argv[]) {
    std::vector<std::string> res{};
    for(auto i=1; i<argc; i++) {
        res.push_back(argv[i]);
    }
    return res;
}

void CommandLine::fill_map_arguments(std::vector<CProgramArgument>& v_arguments) {
    for (auto& l_program_argument : v_arguments) {

        if (l_program_argument.option.config == Config::eshort) {
            auto l_iter = m_input_short.find(l_program_argument.option.char_value);
            if (l_iter == m_input_short.end()) {
                std::cout << "invalid short program option\n";
                //throw ;
            }

            m_map_arguments[std::string{l_program_argument.option.char_value}] = l_program_argument;   //???????????
        }
        else if (l_program_argument.option.config == Config::elong) {
            auto l_iter = m_input_long.find(l_program_argument.option.string_value);
            if (l_iter == m_input_long.end()) {
                std::cout << "invalid long program option\n";
                //throw ;
            }

            m_map_arguments[l_program_argument.option.string_value] = l_program_argument;
        }
        else {
            throw Config_error{};
        }
    }
}
} /* namespace parser */
} /* namespace cmd */
