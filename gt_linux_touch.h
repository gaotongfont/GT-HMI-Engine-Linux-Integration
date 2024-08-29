/**
 * @file gt_linux_touch.h
 * @author your name (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-11 14:53:31
 * @copyright Copyright (c) 2014-present, Company Genitop. Co., Ltd.
 */
#ifndef _GT_LINUX_TOUCH_H_
#define _GT_LINUX_TOUCH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>

/* define ---------------------------------------------------------------*/



/* typedef --------------------------------------------------------------*/

typedef struct gt_touch_s{
    int x;
    int y;
    char status;
}gt_touch_st;

/* macros ---------------------------------------------------------------*/



/* class ----------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/

void gt_touch_init(void);
void gt_touch_close(void);
gt_touch_st get_touch_value(void);
gt_touch_st test_get_touch_value(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_GT_LINUX_TOUCH_H_
