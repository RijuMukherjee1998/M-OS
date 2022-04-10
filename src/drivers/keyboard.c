#include <stdint.h>
#include "../include/keyboard.h"
#include "../include/display.h"
#include "../include/ports.h"
#include "../include/isr.h"

// void print_letter(uint8_t scancode){
//     if (scancode >= 0x80) 
//     {
//         return;
//     }

//     else if (scancode == 0x2)
//     {
//         printk("1\0");
//     }
//     else if (scancode == 0x2c)
//     {
//         printk("Z\0");
//     }
//     else if (scancode == 0x39)
//     {
//         printk(" ");
//     }
//     else
//     {
//         printk("Hi ");
//     }
// }
void print_letter(uint8_t scancode)
{
    switch (scancode)
    {
        case 0x0:
            printk("Keyboard Error!");
            break;
        case 0x1:
            printk("Esc");
            break;
        case 0x2:
            printk("1");
            break;
        case 0x3:
            printk("2");
            break;
        case 0x4:
            printk("3");
            break;
        case 0x5:
            printk("4");
            break;
        case 0x6:
            printk("5");
            break;
        case 0x7:
            printk("6");
            break;
        case 0x8:
            printk("7");
            break;
        case 0x9:
            printk("8");
            break;
        case 0x0a:
            printk("9");
            break;
        case 0x0b:
            printk("0");
            break;
        case 0x0c:
            printk("-");
            break;
        case 0x0d:
            printk("=");
            break;
        case 0xe:
            printk("Backspace");
            break;
        case 0x0f:
            printk("  ");
            break;
        case 0x10:
            printk("Q");
            break;
        case 0x11:
            printk("W");
            break;
        case 0x12:
            printk("E");
            break;
        case 0x13:
            printk("R");
            break;
        case 0x14:
            printk("T");
            break;
        case 0x15:
            printk("Y");
            break;
        case 0x16:
            printk("U");
            break;
        case 0x17:
            printk("I");
            break;
        case 0x18:
            printk("O");
            break;
        case 0x19:
            printk("P");
            break;
        case 0x1a:
            printk("[");
            break;
        case 0x1b:
            printk("]");
            break;
        case 0x1c:
            printk("\n");
            break;
        case 0x1d:
            printk("LCtrl");
            break;
        case 0x1e:
            printk("A");
            break;
        case 0x1f:
            printk("S");
            break;
        case 0x20:
            printk("D");
            break;
        case 0x21:
            printk("F");
            break;
        case 0x22:
            printk("G");
            break;
        case 0x23:
            printk("H");
            break;
        case 0x24:
            printk("J");
            break;
        case 0x25:
            printk("K");
            break;
        case 0x26:
            printk("L");
            break;
        case 0x27:
            printk(";");
            break;
        case 0x28:
            printk("'");
            break;
        case 0x29:
            printk("`");
            break;
        case 0x2a:
            printk("LShift");
            break;
        case 0x2b:
            printk("/");
            break;
        case 0x2c:
            printk("Z");
            break;
        case 0x2d:
            printk("X");
            break;
        case 0x2e:
            printk("C");
            break;
        case 0x2f:
            printk("V");
            break;
        case 0x30:
            printk("B");
            break;
        case 0x31:
            printk("N");
            break;
        case 0x32:
            printk("M");
            break;
        case 0x33:
            printk(",");
            break;
        case 0x34:
            printk(".");
            break;
        case 0x35:
            printk("/");
            break;
        case 0x36:
            printk("RShift");
            break;
        case 0x38:
            printk("LAlt");
            break;
        case 0x39:
            printk(" ");
            break;
        case 0x3a:
            printk("CAPSLOCK");
            break;
        default:
            break;
    }
}
static void keyboard_callback(registers_t *regs) {
    uint8_t scode = port_byte_in(0x60);
    print_letter(scode);    
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}