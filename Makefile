# Build to get the os-image
all : os-image

# Build the os-image
os-image : boot.bin kernel.bin
	cat ./build/boot.bin ./build/kernel.bin > os-image.bin
# Build the boot_sect binary
boot.bin:
	nasm ./src/boot.asm -f bin -o ./build/boot.bin	
# Build the kernel binary
kernel.bin : kernel_entry.o kernel.o
	ld -m elf_x86_64 -o ./build/kernel.bin -Ttext 0x1000 ./build/kernel_entry.o ./build/kernel.o --oformat binary
# Build the kernel object file
kernel.o :
	gcc -ffreestanding -c ./src/kernel/kernel.c -o ./build/kernel.o
# Build the kernel entry object file .
kernel_entry.o :
	nasm ./src/kernel/kernel_entry.asm -f elf64 -o ./build/kernel_entry.o

clean :
	rm *.bin ./build/*.bin ./build/*.o

# kernel.dis : kernel.bin
# 	ndisasm -b 32 ./build/kernel.bin -o kernel.dis

