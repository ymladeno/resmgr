/*
 * CToken.hpp
 *
 *  Created on: Feb 23, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_COMMON_SRC_PARSER_CPROGRAMARGUMENT_HPP_
#define RESMGR_COMMON_SRC_PARSER_CPROGRAMARGUMENT_HPP_

#include <string>

class CProgramArgument {
public:
    CProgramArgument(const std::string& p_argument);
    bool is_long_option() {
        return m_kind == Kind::e_long ? true : false;
    }

    bool is_short_option() {
        return m_kind == Kind::e_short ? true : false;
    }

    std::string get_long_option() const {
        return m_option;
    }

    char get_short_option() const {
        return m_option[0];
    }

    std::string get_argument() const {
        return m_argument;
    }

private:
    enum class Kind {
        e_short,
        e_long,
        e_argument,
        e_none
    };

    Kind        m_kind;
    std::string m_option;
    std::string m_argument;
};


#endif /* RESMGR_COMMON_SRC_PARSER_CPROGRAMARGUMENT_HPP_ */
