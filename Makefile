# Build to get the os-image
all : os-image

# Build the os-image
os-image : boot.bin kernel.bin
	cat ./build/boot.bin ./build/kernel.bin > os-image.bin
# Build the boot_sect binary
boot.bin:
	nasm ./src/boot/boot.asm -f bin -o ./build/boot.bin	
# Build the kernel binary
kernel.bin : cpu.o drivers.o kernel_entry.o kernel.o
	ld -m elf_i386 -o ./build/kernel.bin -Ttext 0x1000 ./build/kernel_entry.o ./build/display.o ./build/keyboard.o ./build/isr.o ./build/idt.o ./build/interrupt.o ./build/ports.o ./build/kernel.o --oformat binary
# ld -m elf_i386 -o ./build/kernel.bin -Ttext 0x1000 ./build/kernel_entry.o ./build/kernel.o --oformat binary
# ld -m elf_i386 -o ./build/kernel.bin -Ttext 0x1000 ./build/kernel_entry.o ./build/display.o ./build/ports.o ./build/kernel.o --oformat binary


#Build the ISR code
cpu.o :
	gcc -fno-pie -m32 -ffreestanding -c ./src/cpu/isr.c -o ./build/isr.o
	gcc -fno-pie -m32 -ffreestanding -c ./src/cpu/idt.c -o ./build/idt.o
	nasm ./src/cpu/interrupt.asm -f elf32 -o ./build/interrupt.o
#Build the drivers
drivers.o :
	gcc -fno-pie -m32 -ffreestanding -c ./src/drivers/display.c -o ./build/display.o
	gcc -fno-pie -m32 -ffreestanding -c ./src/drivers/keyboard.c -o ./build/keyboard.o
	gcc -fno-pie -m32 -ffreestanding -c ./src/drivers/ports.c   -o ./build/ports.o
# Build the kernel object file
kernel.o :
	gcc -fno-pie -m32 -ffreestanding -c ./src/kernel/kernel.c -o ./build/kernel.o
# Build the kernel entry object file .
kernel_entry.o :
	nasm ./src/kernel/kernel_entry.asm -f elf32 -o ./build/kernel_entry.o

clean :
	rm *.bin ./build/*.bin ./build/*.o

# kernel.dis : kernel.bin
# 	ndisasm -b 32 ./build/kernel.bin -o kernel.dis

