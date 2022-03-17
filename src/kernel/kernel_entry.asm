;Ensures that we jump directly into the kernel's entry function without 
;executing code which is preceeding the main function 

[bits 32] ;Entering protected mode
[extern main] ;this helps the linker substitute the final address of main function at 
              ;link time since main is not in this code.     

call main ;invoke main in our C kernel.
jmp $ ;Hang forever when we return from our kernel