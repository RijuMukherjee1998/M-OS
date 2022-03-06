;
; A simple boot code
;
[bits 16]
[org 0x7c00]  ;Boot secotr origin

KERNEL_OFFSET equ 0x9000
start:
  xor ax,ax  ;ax = 0
  mov ds,ax  ; set ds = ax = 0
  mov es,ax  ; set es = ax = 0
  mov [BOOT_DRIVE],dl ;store value of dl in [BOOT_DRIVE]
  mov ax, 0x7e0
  cli            ;clears interrupt flag
  mov ss, ax     ;set ss to 0x7e0
  mov sp, 0x1200 ;set sp to 0x1200
  sti            ;sets interrupt flag
  
  mov si,MSG_REAL_MODE
  call print_string
  
  call load_kernel

  mov dx, [0x9000]
  call print_hex
  
  mov dx, [0x9000+512]
  call print_hex

  ; mov ax, 0x1900 
  ; call print_hex

  jmp halt



load_kernel:
  mov bx, KERNEL_OFFSET
  mov dh, 2 ;No of sectors to read
  mov dl, [BOOT_DRIVE]
  call disk_load
  ret



;
;Infinite loop (Hang)
;  
halt:
  jmp halt

;
;Include Part
;
%include "disk_load.asm"
%include "print.asm"
%include "print_hex.asm"



;
;Data Part
;
;Global Variables
boot_string:
  db 'Booting OS',0x0a,0

HEX_STRING:
  dw 0xdada,0
BOOT_DRIVE:
  db 0
SECTORS:
  db 0
MSG_REAL_MODE:
  db 'Started in 16-bit real mode',0



;
;Padding and magic number to make BIOS understand this is the boot program.
;
times 510-($-$$) db 0 

dw 0xaa55

;Note the padding code is not executed by the CPU rather it gets worked out by the asm compiler,
;where the compiler fills the rest of the bytes leaving the code and the magic number to 0.
;e.g. bin bin bin bin 0 0 0 0 0 0 0 0.................
;     ................................................
;     ..............................0 0 0 0 0 0 0xaa55  

times 256 dw 0xdada
times 256 dw 0xface




;
;OLD CODE
;

; mov [BOOT_DRIVE],dl

; mov bp, 0x8000 ;Put the stack out of the way so that it dosen't get overwritten
; mov sp ,bp

; mov bx,0x9000        ;Load 5 sectors to 0x0000(ES):0x9000(BX)
; mov dh, 5            ;from the boot disk
; mov dl, [BOOT_DRIVE]
; call disk_load

; mov si, [0x9000]     ;Print out the first loaded word which we expect to be 
;                      ;0xdada stored at 0x9000
; call print_string

; mov si, [0x9000 + 512] ;Print out the first word which we expect to be 
;                        ;0xface from second loaded sector
; call print_string


; ; ;Moving address of boot_string to bx so that it can be used to print the string
; ; mov si, boot_string
; ; call print_string

; ; mov si, HEX_STRING
; ; call print_string