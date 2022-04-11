#include <stdint.h>
#include <stdbool.h>
#include "../include/terminal.h"
#include "../include/utils.h"
#include "../include/display.h"

static char key_buffer[MAX_BUFFER_LEN];

const char scancode_to_char[] = {'?', '?', '1', '2', '3', '4', '5',
                                '6', '7', '8', '9', '0', '-', '=',
                                '?', '?', 'Q', 'W', 'E', 'R', 'T',
                                'Y', 'U', 'I', 'O', 'P', '[', ']',
                                '?', '?', 'A', 'S', 'D', 'F', 'G',
                                'H', 'J', 'K', 'L', ';', '/', '`', 
                                '?', '\\', 'Z', 'X', 'C', 'V', 'B',
                                'N', 'M', ',', '.', '?', '?', '?',
                                '?', ' '};

bool backspace(char buffer[]) {
    int len = string_length(buffer);
    if(len > 0) {
        buffer[len - 1] = '\0';
        return true;
    }
    else {
        return false;
    }
}

void execute_command(char* input) {
    if(input[0] == '\0'){
        printk("\n> ");
        return;
    }
    if(compare_string(input,"EXIT") == 0) {
        printk("Shutting Down. Bye!!!\n");
        asm volatile("hlt");
        return;
    }
    printk("Unkown Command: ");
    printk(input);
    printk("\n> ");
}
void terminal (uint8_t scancode) {
    if(scancode > SC_MAX) return;
    
    if(scancode == BACKSPACE) {
        if(backspace(key_buffer)) {
            print_backspace();
        }
    }

    else if (scancode == ENTER) {
        printk("\n");
        execute_command(key_buffer);
        key_buffer[0] = '\0';
    }
    else
    {
        char letter = scancode_to_char[(int) scancode];
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        printk(str);
    }
}