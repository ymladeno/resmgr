/*
 * CManager.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: YMLADENO
 */

#include "CManager.hpp"
#include "detail/HelperFunctions.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace srv {
namespace sample {

CManager::CManager() : m_path("/dev/sample") {
}

CManager::~CManager()  = default;

bool CManager::write(const std::string& p_txt) {
    bool l_ret {false};

    try {
        write_line(m_path, p_txt);
        l_ret = true;
    }
    catch(...) {

    }

    return l_ret;
}

bool CManager::read(std::string& p_txt) {
    bool l_ret {false};

    try {
        p_txt = read_line(m_path);
    }
    catch(...) {

    }

    return l_ret;
}

bool CManager::set_background_color() {
    return true;
}

bool CManager::set_font() {
    return true;
}

bool CManager::set_font_color(te_color p_color) {
    std::unique_ptr<std::int32_t, std::function<void(std::int32_t*)>> l_fd_p {new int32_t{::open(m_path.c_str(), O_RDONLY | O_NONBLOCK)},
                                        [](std::int32_t* p_fd){
                                            if(p_fd) {
                                                ::close(*p_fd);
                                            }
                                        }};

    send_devctl(*l_fd_p, DCMD_SET_FONT_COLOR, p_color);
    return true;
}

bool CManager::get_background_color() {
    return true;
}

bool CManager::get_font() {
    return true;
}

bool CManager::get_font_color() {
    return true;
}

}
}
