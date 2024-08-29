/**
 * @file gt_linux_lcd.c
 * @author your name (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-11 14:06:08
 * @copyright Copyright (c) 2014-present, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/

#include "gt_linux_lcd.h"


#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static variables -----------------------------------------------------*/

static int fd_lcd = 0;
static unsigned short * plcd = NULL;


/* macros ---------------------------------------------------------------*/



/* class ----------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/



/* global functions / API interface -------------------------------------*/



/**
 * @brief lcd 初始化
 * 
 */
void gt_lcd_init(void)
{
    struct fb_fix_screeninfo fb_fix;
    struct fb_var_screeninfo fb_var;

    //打开屏幕文件
    fd_lcd = open("/dev/fb0", O_RDWR);
    if(-1 == fd_lcd)
    {
        perror("open fb0 error!!!");
        return ;
    }

    //映射屏幕
    plcd = mmap(NULL, LCD_MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd_lcd, 0);
    if(NULL == plcd)
    {
        perror("mmap lcd error!!!");
        return ;
    }

     /* 获取参数信息 */
    ioctl(fd_lcd, FBIOGET_VSCREENINFO, &fb_var);
    ioctl(fd_lcd, FBIOGET_FSCREENINFO, &fb_fix);
    printf("分辨率: %d*%d\n"
        "像素深度bpp: %d\n"
        "一行的字节数: %d\n"
        "像素格式: R<%d %d> G<%d %d> B<%d %d>\n",
        fb_var.xres, fb_var.yres, fb_var.bits_per_pixel,
        fb_fix.line_length,
        fb_var.red.offset, fb_var.red.length,
        fb_var.green.offset, fb_var.green.length,
        fb_var.blue.offset, fb_var.blue.length);
}

/**
 * @brief 关闭屏幕
 * 
 */
void gt_lcd_close(void)
{
    if(NULL == plcd)
    {
        perror("lcd close error!!!");
        return ;
    }

    munmap(plcd, LCD_MAP_SIZE);

    close(fd_lcd);
}

/**
 * @brief 映射画点
 * 
 * @param x 起点坐标x
 * @param y 起点坐标y
 * @param p 屏幕文件映射地址
 * @param color 颜色数据
 */
void draw_point(int x, int y, unsigned short * p, unsigned short color)
{
    if(x >= 0 && x < 1024 && y >= 0 && y < 600)
    {
        *(p+(1024*y+x)) = color;
    }
}

/**
 * @brief 画矩形
 * 
 * @param x 起点坐标x
 * @param y 起点坐标y
 * @param w 宽
 * @param h 高
 * @param color 颜色数据数组 
 */
void draw_rectangle(int x, int y, int w, int h, unsigned char * color)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < h; i++)
    {
        for(j = 0; j < w; j++)
        {
            draw_point(x+j, y+i, plcd, color[i*1024+j]);
        }
    }
}


//显示图片
void show_bmp(int x0, int y0,const char * pathname)
{
    //打开BMP图片 
    int fd_pic = open(pathname,O_RDWR);
    if(fd_pic == -1)
    {
        perror("open error");
        return ;
    }
    //读取BMP文件的宽度 高度 色深信息 
    unsigned char buf[4]={0};
    int width,height;
    short depth;
    //读取宽度 
    lseek(fd_pic,0X12,SEEK_SET);
    read(fd_pic,buf,4);
    width = buf[3]<<24 | buf[2] << 16 | buf[1] << 8 | buf[0];
    //读取高度 
    read(fd_pic,buf,4);
    height = buf[3]<<24 | buf[2] << 16 | buf[1] << 8 | buf[0];
    //读取色深 
    lseek(fd_pic,0x1c,SEEK_SET);
    read(fd_pic,buf,2);
    depth = buf[1]<<8 | buf[0]; 
    //读取像素数组的大小（先要根据宽度 高度 色深 以及填充字节求出像素数组的大小）
    int line_bytes = abs(width) * depth/8;  //一行有效像素点的大小 
    printf("w = %d, h = %d, th = %d, line = %d\r\n", width, height, depth, line_bytes);
    // int laizi = 0; 
    // if( line_bytes %4 != 0)
    // {
    //     laizi = 4 - line_bytes %4; //求出laizi数
    // }
    // int line_total_bytes = line_bytes + laizi; //一行真正的总大小 = 一行有效像素点大小 + 癞子
    // int total_bytes =line_total_bytes * abs(height); //总的像素数组的大小 
    //开始读取 
    int total_bytes = line_bytes * abs(height);
    unsigned char * p = malloc(total_bytes); //申请空间用来保存像素数组的数据
    if(NULL == p)
    {
        perror("malloc p error!!!\r\n");
        return ;
    }
    lseek(fd_pic,0x36,SEEK_SET); //偏移光标到对应的位置
    read(fd_pic,p,total_bytes);
    //把p保存的像素点的数据还原到屏幕上 
    //24位色深 像素数组中只有RGB的值 而我们的屏幕的开发板的像素点是ARGB 
    //所以还原的时候 每次取像素数组中三个字节（RGB） 然后自己填充一个A=0的数据 组成ARGB 再显示到开发板上
   
    unsigned short color = 0;
    int n=0; 
    int i = 0;
    int j = 0;
    unsigned char hsb = 0, lsb = 0;
    // for(i = 0;i<abs(height);i++)
    // {
    //     for(j=0;j<abs(width); j++)
    //     {
    //           b = p[n++];
    //           g = p[n++];
    //           r = p[n++];
    //           if(depth == 32)
    //           {
    //                 a = p[n++];
    //           }  
    //           else 
    //           {
    //                 a = 0;
    //           }
    //           color = a<<24 | r << 16 | g << 8 | b;
    //           draw_point(x0+j , y0+abs(height)-1-i ,plcd,color);
    //     }
    //     //跳过癞子 
    //     n = n+laizi;
    // }


    for(i = 0; i < abs(height); i++)
    {
        for(j = 0; j < abs(width); j++)
        {
            lsb = p[n];
            hsb = p[n+1];
            // if(depth == 32)
            // {
            //     a = p[n++];
            // }  
            // else 
            // {
            //     a = 0;
            // }
            color = hsb;
            color = color<<8 | lsb;

            // b = p[n] & 0x1F;
            // g = (p[n+1] & 0x07)<< 3 | p[n]>>5;
            // r = p[n+1]>>3;
            // a = 0;
            // color = a<<24 | r << 16 | g << 8 | b;
            // printf("color[%d] = %04X\r\n", i*480+j, color);

            draw_point(x0+j , y0+abs(height)-1-i , plcd, color);n+=2;
        }
        //跳过癞子 
        
    }

    //关闭图片 
    close(fd_pic);
}




//显示图片
void show_bmp2(int x0, int y0, int width, int height, int depth, const char * pathname)
{
    //打开BMP图片 
    int fd_pic = open(pathname,O_RDWR);
    if(fd_pic == -1)
    {
        perror("open error");
        return ;
    }
    int line_bytes = abs(width) * depth/8;  //一行有效像素点的大小 
    printf("w = %d, h = %d, th = %d, line = %d\r\n", width, height, depth, line_bytes);

    //开始读取 
    int total_bytes = line_bytes * abs(height);
    unsigned char * p = malloc(total_bytes); //申请空间用来保存像素数组的数据
    if(NULL == p)
    {
        perror("malloc p error!!!\r\n");
        return ;
    }
    read(fd_pic, p, total_bytes);


    unsigned short color = 0;
    int n=0; 
    int i = 0;
    int j = 0;
    unsigned char hsb = 0, lsb = 0;

    for(i = 0; i < abs(height); i++)
    {
        for(j = 0; j < abs(width); j++, n+=2)
        {
            lsb = p[n];
            hsb = p[n+1];

            color = hsb;
            color = color<<8 | lsb;

            draw_point(x0+j , y0+i , plcd, color);
        }    
    }

    //关闭图片 
    close(fd_pic);
}



/**
 * @brief 显示界面
 * 
 * @param x x坐标
 * @param y y坐标
 * @param width 宽
 * @param height 高
 * @param color 颜色数据
 */
void display_interface(int x, int y, int width, int height, unsigned char * color)
{
    int n=0; 
    int i = 0;
    int j = 0;
    unsigned char hsb = 0, lsb = 0;
    unsigned short color_tp = 0;

    for(i = 0; i < abs(height); i++)
    {
        for(j = 0; j < abs(width); j++, n+=2)
        {
            lsb = color[n];
            hsb = color[n+1];

            color_tp = hsb;
            color_tp = (color_tp<<8) | lsb;

            //画点函数
            draw_point(x+j , y+i , plcd, color_tp);
        }    
    }
}

/* end ------------------------------------------------------------------*/

