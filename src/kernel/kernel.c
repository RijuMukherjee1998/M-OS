#include "../include/display.h"

void main() {
    char* video_memory = (char*)0xb8000;
    // *(video_memory) = 'X';
    // *(video_memory + 2) = 'H';
    // *(video_memory + 4) = 'E';
    // *(video_memory + 6) = 'L';
    // *(video_memory + 8) = 'O';
    // *(video_memory + 10) = ' ';
    // *(video_memory + 12) = 'I';
    // *(video_memory + 14) = 'N';
    // *(video_memory + 16) = 'F';

    char* message = "Hello World RIJU!!!\n\0";
    char* m1 = "FINALLY THE DISPLAY DRIVER IS WORKING ;)\n\0";
    clear_screen();
    printk(message);
    printk(m1);

    // int i = 0;
    // int offset = 0;
    // while(message[i] != '\0')
    // {
    //     *(video_memory + offset) = *(message + i);
    //     *(video_memory + offset + 1) = 0x0f;
    //     i++;
    //     offset = offset + 2;
    // }   
}