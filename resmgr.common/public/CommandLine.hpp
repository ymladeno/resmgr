/*
 * CommandLineParser.hpp
 *
 *  Created on: Feb 21, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_PARSER_COMMANDLINE_HPP_
#define RESMGR_COMMON_SRC_PARSER_COMMANDLINE_HPP_

#include <vector>
#include <string>
#include <utility>
#include <map>
#include "CProgramArgument.hpp"

namespace res {
namespace parser {

class CommandLine {
public:
    // short, long, description
    using data_t = std::tuple<char, std::string, std::string>;

    enum class ProgramOption {
        e_require,
        e_option
    };

    CommandLine();
    virtual ~CommandLine();
    void add_option(const char l_short, const std::string& l_long, const std::string& l_description);
    void parse(const int argc, const char* argv[]);
    std::string get_program_argument(const char& p_option);
    std::string get_program_argument(const std::string& p_option);

private:
    std::vector<std::string> arguments(const int argc, const char* argv[]);
    void fill_map_arguments(std::vector<CProgramArgument>& v_arguments);

    //add options in main.cpp
    std::vector<data_t> m_init_options;
    std::map<char, std::vector<data_t>::iterator> m_input_short;
    std::map<std::string, std::vector<data_t>::iterator> m_input_long;

    //read from command line
    std::map<std::string, CProgramArgument> m_map_arguments;
};

} /* namespace parser */
} /* namespace cmd */

#endif /* RESMGR_COMMON_SRC_PARSER_COMMANDLINE_HPP_ */
