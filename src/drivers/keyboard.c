#include "../include/keyboard.h"
#include "../include/display.h"
#include "../include/ports.h"
#include "../include/isr.h"
#include "../include/utils.h"
#include "../include/terminal.h"


static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_in(0x60);
    terminal(scancode);    
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}