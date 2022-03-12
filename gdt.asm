;GDT (Flat Memory Model)

gdt_start:

gdt_null:   ;the mandatory null descriptor (4bytes)
    dd 0x0
    dd 0x0
gdt_code: ; the code segment descriptor
    ; base =0x0 , limit =0xfffff ,
    ; 1st flags : ( present )1 ( privilege )00 ( descriptor type )1 -> 1001 b
    ; type flags : ( code )1 ( conforming )0 ( readable )1 ( accessed )0 -> 1010 b
    ; 2nd flags : ( granularity )1 (32 - bit default )1 (64 - bit seg )0 ( AVL )0 -> 1100 b
    dw 0xffff ; Limit (bits 0-15) 
    dw 0x0    ; Base  (bits 0-15)
    db 0x0    ; Base  (bits 16-23)
    db 10011010b  ; 1st Flags, type flags
    db 11001111b  ; 2nd Flags, Limit (bits 16-19)
    db 0x0        ; Base (bits 24-31) 

gdt_data: ;the data segment descriptor
    ; Same as code segment except for the type flags
    ; type flags: ( code )0 ( expand down )0 ( writable )1 ( accessed )0 -> 0010 b
    dw 0xffff ; Limit (bits 0-15)
    dw 0x0    ; Base (bits 0-15)
    db 0x0    ; Base (bits 16-23)
    db 10010010b ; 1st flags, type flags
    db 11001111b ; 2nd flags, Limit (bits 16-19)
    db 0x0       ; Base (bits 24-31)

gdt_end:   ;The reason for putting this label is to help us calculate
           ;the size of GDT for the GDT descriptor

;GDT Descriptor (16-bits GDT size, 32-bits GDT Address)
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; Size of our GDT, always less 1 of true size

    dd gdt_start               ; Start address of our GDT

;Defining some constants for the GDT segment descriptor offsets,
;which are what segment registors must contain when in protected mode.
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start