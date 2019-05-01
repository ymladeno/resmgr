/*
 * CManager.hpp
 *
 *  Created on: Mar 31, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_LIB_SERVICE_SRC_SAMPLE_QNX_CMANAGER_HPP_
#define RESMGR_LIB_SERVICE_SRC_SAMPLE_QNX_CMANAGER_HPP_

#include "devctl/devctl_sample.h"
#include <string>
#include <memory>

namespace srv {
namespace sample {

class CManager {
public:
    CManager();
    virtual ~CManager();
    bool write  (const std::string& p_txt);
    bool read   (std::string& p_txt);

    //dcmd
    bool set_background_color();
    bool set_font();
    bool set_font_color(te_color p_color);
    bool get_background_color();
    bool get_font();
    bool get_font_color();

private:
    std::string m_path;
};

}
}

#endif /* RESMGR_LIB_SERVICE_SRC_SAMPLE_QNX_CMANAGER_HPP_ */
