[bits 16]
;switch to protected mode
switch_to_pm:
    cli  ;We must switch off all interrupts in protected mode
    lgdt [gdt_descriptor] ;load our global descriptor table which defines the 
                          ;protected mode segments
    mov eax, cr0          ; To make a switch to protected mode we set the 1st bit,
    or  eax, 0x1          ; of control reg(cr0) to 1
    mov cr0, eax

    jmp CODE_SEG:init_pm  ;Make a far jmp to a new segment to our 32-bit code
                          ;This also forces the CPU to flush all old pre-fetched
                          ;16-bits instruction and move safely to 32-bits instruction mode.
    
    [bits 32]
    ; Initialize all registers and the stack once in Protected Mode(PM)
    init_pm:

        mov ax, DATA_SEG   ;Now in PM our old segments are meaningless,
                           ;so we point our segment registers to the
                           ;data selector we defined in our GDT
        mov ds, ax
        mov ss, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        mov ebp, 0x90000   ;Update our stack position so it is right 
        mov esp, ebp       ;at the top of the free space.

        call BEGIN_PM      ;Finally call the protected mode begin label