; A boot sector that enters 32-bits protected mode.
[bits 16]
[org 0x7c00]
KERNEL_OFFSET equ 0x1000 ; This is the memory offset to which we will load our kernel 

mov [BOOT_DRIVE], dl ;BIOS stores our boot drive in dl

mov bp, 0x9000 ;Set the stack
mov sp, bp

mov si, MSG_REAL_MODE

call print_string
call load_kernel
call switch_to_pm  ;We never return from here

jmp $


load_kernel:
    mov si, MSG_LOAD_KERNEL
    call print_string

    mov bx,KERNEL_OFFSET
    mov dh,25
    mov dl,[BOOT_DRIVE]
    call disk_load
    ret

%include "./src/boot/bit16_code/print.asm"
%include "./src/boot/bit16_code/disk_load.asm"
%include "./src/boot/bit32_code/gdt.asm"
%include "./src/boot/bit32_code/print_32.asm"
%include "./src/boot/bit32_code/protected_mode_32.asm"

[bits 32]
; This is where we arrive after switching to nad initializing protected mode.
BEGIN_PM:
    mov ebx, MSG_PROTECTED_MODE
    call print_32 ;use our 32-bit print routine
    
    call KERNEL_OFFSET ; Now jump to the address of our loaded
                       ; kernel code , assume the brace position ,
                       ; and cross your fingers. Here we go!
    jmp $ ;Hang

;Global variables
BOOT_DRIVE db 0

MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROTECTED_MODE db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

;Boot-Sector padding
times 510-($-$$) db 0
dw 0xaa55