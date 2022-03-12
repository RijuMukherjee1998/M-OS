[bits 32]

;Define some constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_32:
    pusha    ;push all registors in stack
    mov edx, VIDEO_MEMORY ;push video memory location in edx

print_loop:
    mov al, [ebx] ;pour contents of ebx to al
    mov ah, WHITE_ON_BLACK ;store char display type in ah

    cmp al, 0
    je  print_done

    mov [edx], ax ;store char and attributes in the location of VIDEO MEMORY

    add  ebx, 1    ;increment ebx to the next char in the string
    add  edx, 2    ; each VIDEO_MEM == 2bytes so increase the next location by 2
    jmp print_loop ;loop around to print next char

print_done:
    popa ;pop all the registors from stack
    ret ;return from the func

