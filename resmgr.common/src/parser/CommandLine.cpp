/*
 * CommandLineParser.cpp
 *
 *  Created on: Feb 21, 2019
 *      Author: YMLADENO
 */

#include "CommandLine.hpp"

namespace res {
namespace parser {

CommandLine::CommandLine() {

}

CommandLine::~CommandLine() {
    // TODO Auto-generated destructor stub
}

void CommandLine::add_option(const char l_short, const std::string& l_long, const std::string& l_description) {
    auto l_data_iter = m_container.emplace(m_container.end(), data_t{l_short, l_long, l_description});

    if (l_data_iter == m_container.end()) {
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
    std::vector<std::string> l_command_line_vec = arguments(argc, argv);

    auto l_program_option_iter = m_container.end();
    for (auto l_command_line_iter=l_command_line_vec.begin();
            l_command_line_iter!=l_command_line_vec.end();
            l_command_line_iter++) {

        CProgramArgument l_program_argument{*l_command_line_iter};

        if (l_program_argument.is_long_option()) {
            const auto& l_option = l_program_argument.get_long_option();
            auto l_option_iter = m_input_long.find(l_option);
            if (l_option_iter != m_input_long.end()) {
                std::cout << "Wrong long option\n";
                continue;
            }

            const auto& l_argument = l_program_argument.get_argument();
            auto l_temp_iter = l_command_line_iter;
            l_temp_iter++;
            l_command_line_vec.insert(l_temp_iter, l_argument);

            l_program_option_iter = l_option_iter->second;
        }
        else if (l_program_argument.is_short_option()) {
            const auto& l_option = l_program_argument.get_short_option();
            auto l_option_iter = m_input_short.find(l_option);
            if (l_option_iter != m_input_short.end()) {
                std::cout << "Wrong short option\n";
                continue;
            }
            l_program_option_iter = l_option_iter->second;
        }
        else {
            //argument
            auto& l_data = *l_program_option_iter;
            auto& l_value = std::get<e_data_arg>(l_data);

            l_value = *l_command_line_iter;
        }
    }
}

std::string CommandLine::get_program_argument(const char& p_option) {
    auto l_iter = get_container_iter(p_option, m_input_short);
    auto& l_data = *l_iter;
    auto l_value = std::get<e_data_arg>(l_data);
    return l_value;
}

std::string CommandLine::get_program_argument(const std::string& p_option) {
    auto l_iter = get_container_iter(p_option, m_input_long);
    auto& l_data = *l_iter;
    auto& l_value = std::get<e_data_arg>(l_data);
    return l_value;
}

std::vector<std::string> CommandLine::arguments(const int argc, const char* argv[]) {
    std::vector<std::string> res{};
    for(auto i=1; i<argc; i++) {
        res.push_back(argv[i]);
    }
    return res;
}

} /* namespace parser */
} /* namespace cmd */
