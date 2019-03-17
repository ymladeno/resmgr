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
private:
    enum e_data {
        e_data_short,
        e_data_long,
        e_data_desc,
        e_data_arg
    };

public:
    // short, long, description
    using data_t     = std::tuple<  char,           //short option
                                    std::string,    //long option
                                    std::string,    //description
                                    std::string>;   //argument

    using container_t = std::vector<data_t>;
    using iterator_t  = container_t::iterator;

    CommandLine();
    virtual ~CommandLine();
    void add_option(const char l_short, const std::string& l_long, const std::string& l_description);
    void parse(const int argc, const char* argv[]);
//    template<typename key_t, typename map_t>
//    std::string get_program_argument(key_t& p_key)
    std::string get_program_argument(const char& p_option);
    std::string get_program_argument(const std::string& p_option);
//    template<typename key_t, typename map_t>
//    iterator_t find(key_t&& p_key, map_t&& p_map);

private:
    std::vector<std::string> arguments(const int argc, const char* argv[]);
    template<typename key_t, typename map_t>
    iterator_t get_container_iter(key_t& p_key, const map_t& p_map);

    //add options in main.cpp
    container_t m_container;
    std::map<char, iterator_t> m_input_short;
    std::map<std::string, iterator_t> m_input_long;
};

} /* namespace parser */
} /* namespace cmd */

#include "CommandLine.ipp"

#endif /* RESMGR_COMMON_SRC_PARSER_COMMANDLINE_HPP_ */
