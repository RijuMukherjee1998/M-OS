#include "display.h"
#include "ports.h"



void set_cursor(int offset) {
    // The device uses its control register as an index
    // to select its internal registers , of which we are
    // interested in
    offset /=2;

    // This is similar to get_cursor , only now we write
    // bytes to those internal device registers .
    port_byte_out (REG_SCREEN_CTRL , VGA_OFFSET_HIGH);
    port_byte_out (REG_SCREEN_DATA , (unsigned char)(offset >> 8));
    port_byte_out (REG_SCREEN_CTRL , VGA_OFFSET_LOW);
    port_byte_out (REG_SCREEN_DATA, (unsigned char)(offset & 0xff));

}
int get_cursor() {
    // The device uses its control register as an index
    // to select its internal registers , of which we are
    // interested in
    // reg 14: which is the high byte of the cursor ’s offset
    // reg 15: which is the low byte of the cursor ’s offset
    // Once the internal register has been selected , we may read or
    // write a byte on the data register .
    port_byte_out(REG_SCREEN_CTRL, VGA_OFFSET_HIGH);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, VGA_OFFSET_LOW);
    offset += port_byte_in(REG_SCREEN_DATA);
    // Since the cursor offset reported by the VGA hardware is the
    // number of characters , we multiply by two to convert it to
    // a character cell offset .
    return offset * 2;
}

int get_row_from_offset(int offset)
{
    return offset / (2 * MAX_COLS);
}

int get_offset(int col, int row)
{
    return  2 * (row * MAX_COLS + col);
}

int move_offset_to_new_line(int offset)
{
    return get_offset(0, get_row_from_offset(offset) + 1);
}
void set_char_at_video_memory(char character, int offset)
{
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    *(vidmem + offset) = character;
    *(vidmem + offset + 1) = WHITE_ON_BLACK;
}



void print_string(char* string) {
    int offset = get_cursor();
    int i = 0;
    while (string[i] != '\0') {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scrolling(offset);
        }
        
        if(string[i] == '\n') {
            offset = move_offset_to_new_line(offset);
        } 
        else {
            set_char_at_video_memory(string[i],offset);
            offset += 2;
        }
        i++;
    }
    set_cursor(offset);
}

void clear_screen() {
    for ( int i = 0; i < MAX_COLS; ++i)
    {
        set_char_at_video_memory(' ', i * 2);
    }
    set_cursor(get_offset(0,0));
}

void memory_copy(char* src, char* dest, int no_bytes)
{
    int i;
    for (i = 0; i < no_bytes; i++)
    {
        *(dest + i) = *(src + i);
    }
}

int scrolling(int offset)
{
    memory_copy((char*)(get_offset(0,1) + VIDEO_ADDRESS), 
                (char*)(get_offset(0,0) + VIDEO_ADDRESS),
                MAX_COLS * (MAX_ROWS - 1) * 2);
    for (int col = 0; col < MAX_COLS; col++)
    {
        set_char_at_video_memory(' ', get_offset(col, MAX_ROWS-1));
    }
    return offset - 2 * MAX_COLS;
}

