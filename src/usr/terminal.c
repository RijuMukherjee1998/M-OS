#include <stdint.h>
#include <stdbool.h>
#include "../include/terminal.h"
#include "../include/utils.h"
#include "../include/display.h"

static char key_buffer[MAX_BUFFER_LEN];

bool caps_on = false;
const char scancode_to_char[] = {'?', '?', '1', '2', '3', '4', '5',
                                '6', '7', '8', '9', '0', '-', '=',
                                '?', '?', 'q', 'w', 'e', 'r', 't',
                                'y', 'u', 'i', 'o', 'p', '[', ']',
                                '?', '?', 'a', 's', 'd', 'f', 'g',
                                'h', 'j', 'k', 'l', ';', '/', '`', 
                                '?', '\\', 'z', 'x', 'c', 'v', 'b',
                                'n', 'm', ',', '.', '?', '?', '?',
                                '?', ' ', '?'};

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
    if(compare_string(input,"exit") == 0) {
        printk("Shutting Down. Bye!!!\n");
        asm volatile("hlt");
        return;
    }
    
    if(compare_string(input,"clear") == 0) {
        clear_screen();
        printk("> ");
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
    else if (scancode == CAPSLOACK)
    {
        if(caps_on == false)
            caps_on = true;
        else
            caps_on = false;
    }

    else
    {
        char letter = scancode_to_char[(int) scancode];
        if(caps_on == true)
        {
            int ascii_val = (int) letter;
            ascii_val -= 32;
            letter = (char) ascii_val; 
        }
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        printk(str);
    }
}