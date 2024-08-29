/**
 * @file gt_linux_lcd.h
 * @author your name (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-11 14:53:20
 * @copyright Copyright (c) 2014-present, Company Genitop. Co., Ltd.
 */
#ifndef _GT_LINUX_LCD_H_
#define _GT_LINUX_LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/

#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

/* define ---------------------------------------------------------------*/

#define LCD_MAP_SIZE    (1024*600*2)

/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* class ----------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/

void gt_lcd_init(void);
void gt_lcd_close(void);
void draw_point(int x, int y, unsigned short * p, unsigned short color);
void draw_rectangle(int x, int y, int w, int h, unsigned char * color);
void show_bmp(int x0, int y0,const char * pathname);
void show_bmp2(int x0, int y0, int width, int height, int depth, const char * pathname);
void display_interface(int x0, int y0, int width, int height, unsigned char * color);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_GT_LINUX_LCD_H_
