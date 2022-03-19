all : os-image

os-image : kernel.bin boot.bin
	cat ./build/boot.bin ./build/kernel.bin > os-image.bin

boot.bin :
	nasm ./src/boot/boot.asm -f bin -o ./build/boot.bin

kernel.bin : compile_all kernel_entry.o
	ld -m elf_x86_64 -o ./build/kernel.bin -Ttext 0x1000 ./build/*.o -- oformat binary

compile_all:
	gcc -c ./src/drivers/*.c -ffreestanding 
	gcc -c ./src/kernel/*.c -ffreestanding
	mv *.o ./build

kernel_entry.o :
	nasm ./src/kernel/kernel_entry.asm -f elf64 -o ./build/kernel_entry.o

clean :
	rm -fr ./build/*.bin ./build/*.dis ./build/*.o os-image