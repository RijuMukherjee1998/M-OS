#include "../include/display.h"
#include "../include/keyboard.h"
#include "../include/isr.h"
void main() 
{
    clear_screen();
    printk ("============================ WELCOME TO M-OS ===================================\n");
    printk("Installing interrupt service routines (ISRs).\n");
    isr_install();

    printk("Enabling external interrupts.\n");
    asm volatile("sti");

    printk("Initializing keyboard (IRQ 1).\n");
    init_keyboard();

}