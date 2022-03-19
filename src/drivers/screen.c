#include "screen.h"
#include "../kernel/low_level.h"
void set_cursor(int offset) {
    // The device uses its control register as an index
    // to select its internal registers , of which we are
    // interested in
    offset /=2;

    // This is similar to get_cursor , only now we write
    // bytes to those internal device registers .
    port_byte_out ((unsigned short)REG_SCREEN_CTRL , (unsigned char)14);
    port_byte_out ((unsigned short)REG_SCREEN_DATA , (unsigned char)(offset >> 8));
    port_byte_out ((unsigned short)REG_SCREEN_CTRL , (unsigned char)15);

}
int get_cursor() {
    // The device uses its control register as an index
    // to select its internal registers , of which we are
    // interested in
    // reg 14: which is the high byte of the cursor ’s offset
    // reg 15: which is the low byte of the cursor ’s offset
    // Once the internal register has been selected , we may read or
    // write a byte on the data register .
    port_byte_out((unsigned short)REG_SCREEN_CTRL, (unsigned char)14);
    int offset = port_byte_in((unsigned short)REG_SCREEN_DATA) << 8;
    port_byte_out((unsigned short)REG_SCREEN_CTRL,(unsigned char)15);
    offset += port_byte_in((unsigned short)REG_SCREEN_DATA);
    // Since the cursor offset reported by the VGA hardware is the
    // number of characters , we multiply by two to convert it to
    // a character cell offset .
    return offset*2;
}
int get_screen_offset(int col, int row)
{
    int screen_offset = (row * 80 + col) * 2;
    return screen_offset;
}

void print_char(char character, int col, int row, char atrribute_byte)
{
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;

    if(!atrribute_byte) {
        atrribute_byte = WHITE_ON_BLACK;
    }

    int offset;

    if (col >= 0 && row >=0) {
        offset = get_screen_offset(col, row);
    } else {
        offset = get_cursor();
    }

    if(character == '\n'){
        int rows = offset / (2*MAX_COLS);
        offset = get_screen_offset(79,rows);
    } else {
        vidmem[offset] = character;
        vidmem[offset+1] = atrribute_byte;
    }

    offset += 2;
    //offset = handle_scrolling(offset);

    set_cursor(offset);
}

void print_at(char* message, int col, int row) {
    //Update the cursor if the row and col are non-negative.
    if(col >= 0 && row >= 0) {
        set_cursor(get_screen_offset(col, row));
    }
    //Loop through each char of message and print it.
    int i=0;
    while (message[i] != 0){
        print_char(message[i++], col, row, WHITE_ON_BLACK);
    }
}

void print(char* message) {
    print_at(message, -1, -1);
}

void clear_screen() {
    int row = 0;
    int col = 0;

    for ( row = 0; row < MAX_ROWS; row++)
    {
        for ( col = 0; col < MAX_COLS; col++)
        {
            print_char(' ',col,row,WHITE_ON_BLACK);
        }
    }
}

