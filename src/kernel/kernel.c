#include "../include/display.h"

void main() {
    char* message = "Hello W@rld RIJU!!!\n";
    char* m1 = "FINALLY THE DISPLAY DRIVER IS WORKING ;)\n";
    clear_screen();
    printk("Hello World\n");
    printk("Hi checking vga driver.\n");

    clear_screen();
    printk(message);
    printk(m1);
}