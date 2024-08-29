# include ui/ui.mk

TARGET = test_hmi_10_1_c
CC = arm-none-linux-gnueabihf-gcc
OBJ = main.o gt_linux_lcd.o gt_linux_touch.o

# STATIC_LIB = GT-HMI-Engine/driver/libgt_gui_driver.a

CFLAGS += -g -Wall --std=c99
LFLAGS += -lm -pthread
LDFLAGS = -LGT-HMI-Engine/driver -lgt_gui_driver

STATIC = -static



#搜索源文件，设定文件名
# SRC = $(wildcard *.c)
# OBJ = $(SRC:%.c=%.o)


# $(TARGET) : $(OBJ)
# 	$(CC) $^ $(LFLAGS) -o $@

# %.o : %.c 
# 	$(CC) $(CFLAGS) -c $< -o $@


# GT-HMI-Engine
# driver
OBJ += GT-HMI-Engine/driver/gt_port_disp.o
OBJ += GT-HMI-Engine/driver/gt_port_indev.o
OBJ += GT-HMI-Engine/driver/gt_port_src.o
OBJ += GT-HMI-Engine/driver/gt_port_vf.o
# src/core
OBJ += GT-HMI-Engine/src/core/gt_disp.o
OBJ += GT-HMI-Engine/src/core/gt_draw.o
OBJ += GT-HMI-Engine/src/core/gt_event.o
OBJ += GT-HMI-Engine/src/core/gt_fs.o
OBJ += GT-HMI-Engine/src/core/gt_graph_base.o
OBJ += GT-HMI-Engine/src/core/gt_handler.o
OBJ += GT-HMI-Engine/src/core/gt_img_decoder.o
OBJ += GT-HMI-Engine/src/core/gt_indev.o
OBJ += GT-HMI-Engine/src/core/gt_layout.o
OBJ += GT-HMI-Engine/src/core/gt_mem.o
OBJ += GT-HMI-Engine/src/core/gt_obj_pos.o
OBJ += GT-HMI-Engine/src/core/gt_obj_scroll.o
OBJ += GT-HMI-Engine/src/core/gt_refr.o
OBJ += GT-HMI-Engine/src/core/gt_scr_stack.o
OBJ += GT-HMI-Engine/src/core/gt_style.o
OBJ += GT-HMI-Engine/src/core/gt_timer.o
# src/extra
OBJ += GT-HMI-Engine/src/extra/gt_extra.o
# src/extra/draw
OBJ += GT-HMI-Engine/src/extra/draw/gt_draw_blend.o
OBJ += GT-HMI-Engine/src/extra/draw/gt_draw_blend_with_argb888.o
OBJ += GT-HMI-Engine/src/extra/draw/gt_draw_blend_with_rgb565.o
OBJ += GT-HMI-Engine/src/extra/draw/gt_draw_blend_with_rgb888.o
# src/extra/gif
OBJ += GT-HMI-Engine/src/extra/gif/gifdec.o
# src/extra/jpeg
OBJ += GT-HMI-Engine/src/extra/jpeg/gt_sjpg.o
OBJ += GT-HMI-Engine/src/extra/jpeg/tjpgd.o
# src/extra/png
OBJ += GT-HMI-Engine/src/extra/png/gt_png.o
OBJ += GT-HMI-Engine/src/extra/png/lodepng.o
# src/font
OBJ += GT-HMI-Engine/src/font/gt_font.o
OBJ += GT-HMI-Engine/src/font/gt_symbol.o
# src/hal
OBJ += GT-HMI-Engine/src/hal/gt_hal_disp.o
OBJ += GT-HMI-Engine/src/hal/gt_hal_fs.o
OBJ += GT-HMI-Engine/src/hal/gt_hal_indev.o
OBJ += GT-HMI-Engine/src/hal/gt_hal_src.o
OBJ += GT-HMI-Engine/src/hal/gt_hal_tick.o
OBJ += GT-HMI-Engine/src/hal/gt_hal_vf.o
OBJ += GT-HMI-Engine/src/hal/gt_hal_file_header.o
# src/others
OBJ += GT-HMI-Engine/src/others/gt_anim.o
OBJ += GT-HMI-Engine/src/others/gt_area.o
OBJ += GT-HMI-Engine/src/others/gt_color.o
OBJ += GT-HMI-Engine/src/others/gt_effects.o
OBJ += GT-HMI-Engine/src/others/gt_gc.o
OBJ += GT-HMI-Engine/src/others/gt_ll.o
OBJ += GT-HMI-Engine/src/others/gt_math.o
OBJ += GT-HMI-Engine/src/others/gt_tlsf.o
OBJ += GT-HMI-Engine/src/others/gt_txt.o
# src/utils
OBJ += GT-HMI-Engine/src/utils/gt_stack.o
OBJ += GT-HMI-Engine/src/utils/gt_vector.o
# src/widgets
OBJ += GT-HMI-Engine/src/widgets/gt_barcode.o
OBJ += GT-HMI-Engine/src/widgets/gt_btn.o
OBJ += GT-HMI-Engine/src/widgets/gt_btnmap.o
OBJ += GT-HMI-Engine/src/widgets/gt_chat.o
OBJ += GT-HMI-Engine/src/widgets/gt_checkbox.o
OBJ += GT-HMI-Engine/src/widgets/gt_clock.o
OBJ += GT-HMI-Engine/src/widgets/gt_dialog.o
OBJ += GT-HMI-Engine/src/widgets/gt_gif.o
OBJ += GT-HMI-Engine/src/widgets/gt_group.o
OBJ += GT-HMI-Engine/src/widgets/gt_img.o
OBJ += GT-HMI-Engine/src/widgets/gt_imgbtn.o
OBJ += GT-HMI-Engine/src/widgets/gt_input_number.o
OBJ += GT-HMI-Engine/src/widgets/gt_input.o
OBJ += GT-HMI-Engine/src/widgets/gt_keypad.o
OBJ += GT-HMI-Engine/src/widgets/gt_label.o
OBJ += GT-HMI-Engine/src/widgets/gt_line.o
OBJ += GT-HMI-Engine/src/widgets/gt_listview.o
OBJ += GT-HMI-Engine/src/widgets/gt_obj_class.o
OBJ += GT-HMI-Engine/src/widgets/gt_obj.o
OBJ += GT-HMI-Engine/src/widgets/gt_option.o
OBJ += GT-HMI-Engine/src/widgets/gt_player.o
OBJ += GT-HMI-Engine/src/widgets/gt_progress_bar.o
OBJ += GT-HMI-Engine/src/widgets/gt_qrcode.o
OBJ += GT-HMI-Engine/src/widgets/gt_radio.o
OBJ += GT-HMI-Engine/src/widgets/gt_rect.o
OBJ += GT-HMI-Engine/src/widgets/gt_roller.o
OBJ += GT-HMI-Engine/src/widgets/gt_slider.o
OBJ += GT-HMI-Engine/src/widgets/gt_status_bar.o
OBJ += GT-HMI-Engine/src/widgets/gt_switch.o
OBJ += GT-HMI-Engine/src/widgets/gt_template.o
OBJ += GT-HMI-Engine/src/widgets/gt_textarea.o
OBJ += GT-HMI-Engine/src/widgets/gt_view_pager.o
OBJ += GT-HMI-Engine/src/widgets/gt_wordart.o

# ui
OBJ += ui/gt_ui.o
OBJ += ui/gt_init_screen_1.o
OBJ += ui/gt_init_screen_home.o
OBJ += ui/gt_init_screen_2.o
OBJ += ui/gt_init_screen_3.o
OBJ += ui/gt_init_screen_4.o
OBJ += ui/gt_init_screen_5.o
OBJ += ui/gt_init_screen_6.o
OBJ += ui/gt_init_screen_7.o
OBJ += ui/gt_init_screen_8.o
OBJ += ui/gt_init_screen_9.o
OBJ += ui/gt_init_screen_10.o
OBJ += ui/gt_init_screen_11.o





$(TARGET) : $(OBJ)
	$(CC) $^ $(LFLAGS) $(LDFLAGS) $(STATIC) -o $@

# gt_linux_lcd.o : gt_linux_lcd.c
# $(CC) $(CFLAGS) -c gt_linux_lcd.c -o gt_linux_lcd.o

# gt_linux_touch.o : gt_linux_touch.c
# $(CC) $(CFLAGS) -c gt_linux_touch.c -o gt_linux_touch.o

# ui/gt_init_screen_1.c : ui/gt_init_screen_1.o
# 	$(CC) $(CFLAGS) -c ui/gt_init_screen_1.c -o ui/gt_init_screen_1.o

# gt_linux_lcd.o : gt_linux_lcd.c gt_linux_lcd.h
# gt_linux_touch.o : gt_linux_touch.c gt_linux_touch.h
# #ui
# ui/gt_ui.o : ui/gt_ui.c ui/gt_ui.h
# ui/gt_init_screen_1.o : ui/gt_init_screen_1.c ui/gt_ui.h
# ui/gt_init_screen_home.o : ui/ui/gt_init_screen_home.c ui/gt_ui.h


.PHONY: clean
clean:
	$(RM) -r $(OBJ) test_hmi










