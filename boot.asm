; A boot sector that enters 32-bits protected mode.
[bits 16]
[org 0x7c00]

mov bp, 0x9000 ;Set the stack
mov sp, bp

mov si, MSG_REAL_MODE
call print_string

call switch_to_pm  ;We never return from here

jmp $

%include "./bit16_code/print.asm"
%include "gdt.asm"
%include "print_32.asm"
%include "protected_mode_32.asm"

[bits 32]
; This is where we arrive after switching to nad initializing protected mode.
BEGIN_PM:
    mov ebx, MSG_PROTECTED_MODE
    call print_32 ;use our 32-bit print routine

    jmp $ ;Hang

;Global variables
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROTECTED_MODE db "Landed in 32-bit Protected Mode", 0

;Boot-Sector padding
times 510-($-$$) db 0
dw 0xaa55