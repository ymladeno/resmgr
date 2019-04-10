/*
 * CManager.hpp
 *
 *  Created on: Apr 3, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_LIB_SERVICE_SRC_SAMPLE_LINUX_CMANAGER_HPP_
#define RESMGR_LIB_SERVICE_SRC_SAMPLE_LINUX_CMANAGER_HPP_

#include <string>

namespace srv {
namespace sample {

class CManager {
public:
    CManager();
    virtual ~CManager();
    bool write(const std::string& p_txt);
    bool read(std::string& p_txt);
};

} /* namespace srv */
} /* namespace sample */

#endif /* RESMGR_LIB_SERVICE_SRC_SAMPLE_LINUX_CMANAGER_HPP_ */
