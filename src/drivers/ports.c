#include "../include/ports.h"

//Writing all low_level in_out functions that will be required later.
// A handy C wrapper function to read a byte from the specific port
unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    //inline assembly code; where %% means a register also the source and destination are swapped.
    // "=a" (result) means put contents of AL register in result variable
    //  "d" (port)   means load EDX with port 
    __asm__("in %%dx, %%al" :"=a" (result) :"d" (port));
    return result;
}

// A handy C wrapper function to write a byte to the specific port
void port_byte_out(unsigned short port, unsigned char data) {
    //"a" (data) means load EAX with data
    //"d" (port) means load EDX with port
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

// A handy C wrapper function to read a word from the specific port
unsigned short port_word_in(unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" :  "=a" (result) : "d" (port));
    return result;
}

// A handy C wrapper function to write a word to the specific port
void port_word_out(unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}