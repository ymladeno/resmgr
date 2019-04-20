/*
 * CManager.hpp
 *
 *  Created on: Mar 31, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_LIB_SERVICE_SRC_SAMPLE_QNX_CMANAGER_HPP_
#define RESMGR_LIB_SERVICE_SRC_SAMPLE_QNX_CMANAGER_HPP_

#include <string>
#include <memory>

namespace srv {
namespace sample {

class CManager {
public:
    CManager();
    virtual ~CManager();
    bool write(const std::string& p_txt);
    bool read(std::string& p_txt);

private:
    std::string m_path;
};

}
}

#endif /* RESMGR_LIB_SERVICE_SRC_SAMPLE_QNX_CMANAGER_HPP_ */
