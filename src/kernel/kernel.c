#include "low_level.h"
#include "../drivers/screen.h"

void main()
{
    // char* video_memory = (char*)0xb8000;

    // *video_memory = 'X';
    char* message = "Hello\0";
    print(message);
}