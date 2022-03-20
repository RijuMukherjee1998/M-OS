#pragma once

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
//Default color scheme
#define WHITE_ON_BLACK 0x0f

//Screen device I/O ports
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

int get_offset(int, int);

int get_row_from_offset(int);

int move_offset_to_new_line(int);

int get_cursor();

void set_cursor(int);

void set_char_at_video_memoryr(char, int);

void memory_copy(char*, char*, int);

int scrolling(int);

void clear_screen();

void print_string(char*);
