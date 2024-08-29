/**
 * @file gt_linux_touch.c
 * @author your name (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-11 14:53:26
 * @copyright Copyright (c) 2014-present, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/

#include "gt_linux_touch.h"

/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static variables -----------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* class ----------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/

static int fd_touch = 0;


/* global functions / API interface -------------------------------------*/

/**
 * @brief 触摸初始化
 * 
 */
void gt_touch_init(void)
{
    fd_touch = open("/dev/input/event1", O_RDWR);
    if(-1 == fd_touch)
    {
        perror("open event0 error!!!");
        return ;
    }
}


/**
 * @brief 关闭触摸
 * 
 */
void gt_touch_close(void)
{
    if(-1 == fd_touch)
    {
        perror("close event0 error!!!");
        return ;
    }

    close(fd_touch);
}

/**
 * @brief 获取触摸坐标
 * 
 * @param x 
 * @param y 
 */
gt_touch_st get_touch_value(void)
{
    gt_touch_st tp;
    tp.x = -1;
    tp.y = -1;

    struct input_event ev;
    
    int ret = 0;
    while(1)
    {
        ret = read(fd_touch, &ev, sizeof(ev));
        if(ret != sizeof(ev))
        {
            printf("read fd_touch error!!!\r\n");
            return tp;
        }

        if(ev.type == EV_ABS && ev.code == ABS_MT_POSITION_X)
        {
            if(tp.x < 0)
            {
                tp.x = ev.value;
            }
        }
        else if(ev.type == EV_ABS && ev.code == ABS_MT_POSITION_Y)
        {
            if(tp.y < 0)
            {
                tp.y = ev.value;
            }
        }
        else if(ev.type == 0 && ev.value == 0) //当手指离开触摸屏的时候
        {
            // printf("value = %d\r\n", ev.value);
            // printf("(%d , %d)  status = %d\r\n", tp.x, tp.y, tp.status);
            if(tp.x == -1 || tp.y == -1)
            {
                tp.status = 0;
            }        
            else
            {
                tp.status = 1;
            }    
            return tp;
        }
    } 

}



gt_touch_st test_get_touch_value(void)
{
    gt_touch_st tp;
    tp.x = -1;
    tp.y = -1;

    struct input_event ev;
    
    int ret = 0;
    while(1)
    {
        ret = read(fd_touch, &ev, sizeof(ev));
        if(ret != sizeof(ev))
        {
            printf("read fd_touch error!!!\r\n");
            return tp;
        }

        printf("tpye = %d  code = %d  value = %d \r\n", ev.type, ev.code, ev.value);

    } 
}


/* end ------------------------------------------------------------------*/
