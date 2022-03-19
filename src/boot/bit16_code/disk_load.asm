; Load DH sectors to ES:BX from drive DL

disk_load:
    mov [SECTORS],dh
    mov ch,0x00 ;C=0
    mov dh,0x00 ;H=0
    mov cl,0x02 ;S=2
    next_group:
        mov di, 5 ;MAX tries 5
    read_sectors:
        mov ah,0x02 ;BIOS read sector function
        mov al,[SECTORS] ;No of sectors to read
        int 0x13 ;BIOS interrupt to start reading from disk
        
        jc retry_read_sectors ; if disk fails to read (i.e carry set to 1)
        sub [SECTORS], al ;Remaining sectors to read
        jz done

        mov cl, 0x01 ;always sector 1
        xor dh, 1  ;Next head on diskette
        jnz next_group
        inc ch ;Next Cylinder
        jmp next_group
        
    retry_read_sectors:
        mov ah, 0x00 ;Reset disk drive
        int 0x13
        dec di ;decrease no of retries by 1
        jnz read_sectors
        jmp disk_error
    
    done:
        ret

disk_error:
    mov si, DISK_ERROR_MSG
    call print_string
    jmp $
disk_invalid_sector_error:
    mov si, DISK_INVALID_SECTOR_MSG
    call print_string
    jmp $

;Global variables
DISK_ERROR_MSG:
    db "Disk read error!",0
DISK_INVALID_SECTOR_MSG:
    db "Invalid sectors read!",0

SECTORS:
    db 0





; push dx  ; Storing dx on stack so that we can recall 
;              ; how many sectors we have to read 

;     mov ah,0x02 ; BIOS read sector function
;     mov al, dh  ; Read DH sectors
;     mov ch, 0x00 ;Select Cylinder 0 of HDD
;     mov dh, 0x00 ;Select head 0
;     mov cl, 0x02 ; Start reading from second sector

;     int 0x13     ;BIOS interrupt to start reading from disk

;     jc disk_error ;if carry flag is set (Jump to error lablel) i.e disk failed to read

;     pop dx      ; retrieve contents of dx register
;     cmp dh,al   ; if AL (sectors read) != DH (Sectors expected)
;     jne disk_error ; display error msg
;     ret