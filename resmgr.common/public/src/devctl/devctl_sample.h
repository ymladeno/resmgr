/*
 * devctl_sample.hpp
 *
 *  Created on: Apr 21, 2019
 *      Author: YMLADENO
 */

#ifndef RESMGR_SAMPLE_SRC_DEVCTL_SAMPLE_H_
#define RESMGR_SAMPLE_SRC_DEVCTL_SAMPLE_H_

#include <devctl.h>

enum te_color {
    Blue,
    Red
};

#define CMD_CODE 1
#define DCMD_SET_FONT_COLOR         __DIOT(_DCMD_MISC, CMD_CODE + 0, enum te_color)
#define DCMD_SET_FONT_SIZE          __DIOT(_DCMD_MISC, CMD_CODE + 1, std::uint32_t)
#define DCMD_SET_BACKGROUND_COLOR   __DIOT(_DCMD_MISC, CMD_CODE + 2, enum te_color)
#define DCMD_GET_FONT_COLOR         __DIOF(_DCMD_MISC, CMD_CODE + 3, enum te_color)
#define DCMD_GET_FONT_SIZE          __DIOF(_DCMD_MISC, CMD_CODE + 4, std::uint32_t)
#define DCMD_GET_BACKGROUND_COLOR   __DIOF(_DCMD_MISC, CMD_CODE + 5, enum te_color)


#endif /* RESMGR_SAMPLE_SRC_DEVCTL_SAMPLE_H_ */
