/*
 * CProxy.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: YMLADENO
 */

#include "CProxy.hpp"
#include "CManager.hpp"

namespace srv {
namespace sample {

CProxy::CProxy() : m_manager{new CManager{}} {
}

CProxy::~CProxy() {
}

bool CProxy::write(const std::string& p_txt) {
    return m_manager->write(p_txt);
}

bool CProxy::read(std::string& p_txt) {
    return m_manager->read(p_txt);
}

}
}
