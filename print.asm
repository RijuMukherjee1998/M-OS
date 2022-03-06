;move address of message to si(source index)
;si is a pointer to a buffer of bytes (lodsb ,lodsw, lodsd  are used to retrieve data from buffer, 
;byte wise , word wise , double word wise res[ectively])
print_string:
    push ax
    push bx
    push si

.prints:
    mov bx, 0x0007 ; BL=White on black BH = Display page 0 
    mov ah, 0x0e ;tele-type on

.run:
    lodsb ;Gets each char from si and loads it to al reg
    cmp al, 0 ;compares al to 0 (i.e string terminated)
    je .done  ; if al == 0 return else 
    int 0x10  ; print each char by calling interrupt 0x10
    jmp .run  ; loops until the end of string.

.done:
    pop si
    pop bx
    pop ax 
    ret




;
;OLD CODE
;

; mov ah,0x0e ;to enable tele-type mode
; ;
; ;Prints hello in a loop
; ;
; message:
;   mov al, 'H'
;   int 0x10
  
;   mov al, 'e'
;   int 0x10
  
;   mov al, 'l'
;   int 0x10
  
;   mov al, 'l'
;   int 0x10
  
;   mov al, 'o'
;   int 0x10

;   mov al, ' '
;   int 0x10

;   mov bx, the_secret ;puts the labels offset address from the origin. 
;   ;add bx, 0x7c00 ;As we specified the origin to start at 0x7c00 so there is no need to add the, 
;                   ;origin offset 0x7c00 now.
;   mov al, [bx]
;   int 0x10

;   ; mov al, [0x7c21] ;Rather than calculating the offset in CPU here we calculated mannualy where 
;   ; int 0x10         ;X is present in memory and then we tried to access that address to get X.  


; ;Secret messgae
; the_secret:
;   db "X"
