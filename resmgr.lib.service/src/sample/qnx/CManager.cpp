/*
 * CManager.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: YMLADENO
 */

#include "CManager.hpp"
#include "detail/HelperFunctions.hpp"

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

}
}
