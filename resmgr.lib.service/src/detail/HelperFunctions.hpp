/*
 * HelperFunctions.hpp
 *
 *  Created on: Apr 10, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_LIB_SERVICE_SRC_DETAIL_HELPERFUNCTIONS_HPP_
#define RESMGR_LIB_SERVICE_SRC_DETAIL_HELPERFUNCTIONS_HPP_

#include "exceptions/InvalidFile.hpp"
#include <string>
#include <fstream>
#include <sys/types.h>
#include <unistd.h>
#include <devctl.h>

std::string read_line(const std::string& p_file) {
    std::ifstream l_stream {p_file, std::ifstream::in};
    std::string l_data {};

    if (!l_stream.is_open() || !l_stream.good()) {
        throw exception::InvalidFile{};
    }

    std::getline(l_stream, l_data);

    return l_data;
}

void write_line(const std::string& p_file, const std::string& p_data) {
    std::ofstream l_stream {p_file, std::ifstream::out};

    if (!l_stream.is_open() || !l_stream.good()) {
        throw exception::InvalidFile{};
    }

    l_stream << p_data;
}

template<typename type_t>
std::int32_t send_devctl(std::int32_t p_fd, std::int32_t p_cmd, type_t&& p_data) {
    return ::devctl(p_fd, p_cmd, &p_data, sizeof(type_t), nullptr);
}

#endif /* RESMGR_LIB_SERVICE_SRC_DETAIL_HELPERFUNCTIONS_HPP_ */
