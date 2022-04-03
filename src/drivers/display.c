#include "../include/display.h"
#include "../include/ports.h"

void set_cursor(unsigned int offset) {
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
unsigned int get_cursor() {
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
    return (unsigned int)(offset * 2);
}

unsigned int get_row_from_offset(unsigned int offset)
{
    return (unsigned int)(offset / (2 * MAX_COLS));
}

unsigned int get_offset(int col, int row)
{
    return  (unsigned int) (2 * (row * MAX_COLS + col));
}

unsigned int move_offset_to_new_line(unsigned int offset)
{
    return (unsigned int) get_offset(0, get_row_from_offset(offset) + 1);
}

void set_char_at_video_memory(char character, unsigned int offset)
{
    unsigned char *videomem = (unsigned char*) VIDEO_ADDRESS;
    *(videomem + offset) = character;
    *(videomem + offset + 1) = WHITE_ON_BLACK;
}

void memory_copy(unsigned char* src, unsigned char* dest, unsigned int no_bytes)
{
    int i;
    for (i = 0; i < no_bytes; i++)
    {
        *(dest + i) = *(src + i);
    }
}

unsigned int scrolling(unsigned int offset)
{
    memory_copy((unsigned char*)((get_offset(0,1) + (unsigned int)VIDEO_ADDRESS)),
                (unsigned char*)((get_offset(0,0) + (unsigned int)VIDEO_ADDRESS)),
                (unsigned int) (MAX_COLS * (MAX_ROWS - 1) * 2)
                );
    for (int col = 0; col < MAX_COLS; col++)
    {
        set_char_at_video_memory(' ', get_offset(col, MAX_ROWS-1));
    }
    return (unsigned int) (offset - 2 * MAX_COLS);
}

void printk(char* charStream) {
    unsigned int offset = 0;
    offset = get_cursor();
    int i = 0;
    while (charStream[i] != '\0') {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scrolling(offset);
        }

        if(charStream[i] == '\n') {
            offset = move_offset_to_new_line(offset);
        }
        else {
            set_char_at_video_memory(charStream[i],offset);
            offset += 2;
        }
        i++;
    }
    set_cursor(offset);
}

void clear_screen() {
    unsigned int offset = 0;
    for (int r = 0; r < MAX_ROWS; ++r)
    {
      for ( int c = 0; c < MAX_COLS; ++c)
        {
            set_char_at_video_memory(' ', offset + 2 * c);
        }
        offset = move_offset_to_new_line(offset);
    }
    set_cursor(get_offset(0,0));
}



