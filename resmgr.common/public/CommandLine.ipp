/*
 * CommandLine.ipp
 *
 *  Created on: Mar 16, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_PARSER_COMMANDLINE_IPP_
#define RESMGR_COMMON_SRC_PARSER_COMMANDLINE_IPP_

#include <iostream>

namespace res {
namespace parser {

template<typename key_t, typename map_t>
CommandLine::iterator_t CommandLine::get_container_iter(key_t& p_key, const map_t& p_map) {
    auto l_iter = p_map.find(p_key);

    if (l_iter != p_map.end()) {
        std::cout << "get_container_iter() error\n";
    }
    return l_iter->second;
}

}   //namespace parser
}   //namespace res



#endif /* RESMGR_COMMON_SRC_PARSER_COMMANDLINE_IPP_ */
