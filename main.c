/**
 * @file main.c
 * @author your name (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-15 16:43:08
 * @copyright Copyright (c) 2014-present, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/

#include <stdio.h>
#include <pthread.h>
#include "gt_linux_lcd.h"
#include "gt_linux_touch.h"
#include "GT-HMI-Engine/gt.h"
#include "ui/gt_ui.h"
#include <unistd.h>

/* private define -------------------------------------------------------*/

int fp_bin = 0;

/* private typedef ------------------------------------------------------*/



/* static variables -----------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* class ----------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/



/* global functions / API interface -------------------------------------*/

/**
 * @brief 字库读取函数
 * 
 * @param address 读取地址
 * @param DataLen 读取长度
 * @param pBuff 数据保存地址
 * @return unsigned long 
 */
unsigned long r_dat_bat(unsigned long address, unsigned long DataLen, unsigned char* pBuff)
{
    // printf("addr = %08X  len_read = %d\r\n", address, DataLen);
    lseek(fp_bin, address, SEEK_SET); //偏移光标到对应的位置
    read(fp_bin, pBuff, DataLen);

}

/**
 * @brief 发送读取函数
 *
 * @param sendbuf 发送数据的buff
 * @param sendlen 发送数据长度
 * @param receivebuf 读取数据的buff
 * @param receivelen 读取数据长度
 */
unsigned char gt_read_data(unsigned char* sendbuf, unsigned char sendlen, unsigned char* receivebuf, \
                            unsigned int receivelen)
{

}

/**
 * @brief 
 * 
 * @param drv 此参数不需要用户配置
 * @param area area->x为绘图的起始x坐标
 *             area->y为绘图的起始y坐标
 *             area->w为绘图区域的宽度
 *             area->h为绘图区域的高度
 * @param color 为图片数据数组
 */
void _flush_cb(struct _gt_disp_drv_s * drv, gt_area_st * area, gt_color_t * color)
{
    //显示界面
    display_interface(area->x, area->y, area->w, area->h, (unsigned char *)color);
}


/**
 * @brief 
 * 
 * @param indev_drv 此参数不需要用户配置
 * @param data data->state有无输入事件发生
 *             data->point.x触摸点的x坐标
 *             data->point.y触摸点的y坐标
 */
void read_cb(struct _gt_indev_drv_s * indev_drv, gt_indev_data_st * data)
{
    gt_touch_st tp = get_touch_value();//获取触摸坐标
    if(!tp.status)
    {
        data->state = GT_INDEV_STATE_RELEASED;//如果没有触摸事件则返回
        return ;
    }
    data->point.x = tp.x;
    data->point.y = tp.y;
    data->state = GT_INDEV_STATE_PRESSED;
    GT_LOGD(GT_LOG_TAG_TP,"point: x: %d , y: %d , state = %d\r\n", data->point.x , data->point.y , data->state);
}


/**
 * @brief 
 * 
 * @param indev_drv 此参数不需要用户配置
 * @param data 
 */
void read_cb_btn(struct _gt_indev_drv_s * indev_drv, gt_indev_data_st * data)
{
    // uint8_t status = 0;
    // status = KEY_Scan(1);
    // if( status )
    // {
    //     data->btn_id = status;
    //     data->state = GT_INDEV_STATE_PRESSED;
    // }
    // else
    // {
    //     data->state = GT_INDEV_STATE_RELEASED;
    // }
}


/**
 * @brief 
 * 
 * @param data_write data_write 此指针存放着 24 位的地址值。*(data_write+1)为高八位地址
 *                                                        *(data_write+2)为中八位地址
 *                                                        *(data_write+3)为低八位地址
 * @param len_write len_write 参数无需用户适配
 * @param data_read data_read 为存放读取数据的指针
 * @param len_read len_read 为读取数据的长度
 * @return uint32_t 
 */
uint32_t spi_wr(uint8_t * data_write, uint32_t len_write, uint8_t * data_read, uint32_t len_read)
{
    unsigned long ReadAddr;
    if (len_write > 4)
    {
        ReadAddr =  *(data_write+1)<<24; //高八位地址
        ReadAddr += *(data_write+2)<<16; //中八位地址
        ReadAddr += *(data_write+3)<<8;  //低八位地址
        ReadAddr += *(data_write+4);     //低八位地址
    }
    else
    {
        ReadAddr =  *(data_write+1)<<16; //高八位地址
        ReadAddr += *(data_write+2)<<8;  //中八位地址
        ReadAddr += *(data_write+3);     //低八位地址
    }
    // printf("addr = %08X  len_read = %d\r\n", ReadAddr, len_read);
    lseek(fp_bin, ReadAddr, SEEK_SET);  //偏移光标到对应的位置
    read(fp_bin, data_read, len_read);
    return 0;
}

/**
 * @brief HMI心跳函数
 * 
 */
void tick_task()
{
    while(1)
    {
        gt_tick_inc(1);
        usleep(1000);
    }   
}



int main(void)
{
    printf(">>>>>2024.7.19 - 1003\r\n");
    gt_lcd_init();//lcd初始化
    gt_touch_init();//触摸初始化

    //打开图片资源文件 
    fp_bin = open("/lqd/tp/test.bin", O_RDWR);
    if(fp_bin == -1)
    {
        perror("open error");
        return 0;
    }

    gt_init();//hmi初始化
    gt_ui_init();//ui初始化

    pthread_t thread;
    pthread_create(&thread, NULL, tick_task, NULL);//创建心跳线程

    while(1)
    {
        gt_task_handler();//gui事务处理函数
        usleep(1000);
    }

    //关闭图片资源文件
    close(fp_bin);

    gt_touch_close();//关闭触摸文件
    gt_lcd_close();//关闭lcd文件

    return 0;
}


/* end ------------------------------------------------------------------*/
