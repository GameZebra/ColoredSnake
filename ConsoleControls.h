#pragma once
#ifndef __CONS_H__
#define __CONS_H__

void init_console(unsigned int Value);
void set_cursor_visible(int Visible);
void set_cursor_position(int x, int y);
void set_cursor_size(int large);
CHAR_INFO* get_screen(COORD* cd);
void put_screen(COORD* cd, CHAR_INFO* buffer);
void set_window_title(unsigned short* str);
void clrScr(void);

#endif /* __CONS_H__ */
