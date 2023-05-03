all: program

cfile.o: cfile.c
	gcc -m32 -c -o cfile.o cfile.c

asmfile.o: asmfile.asm
	nasm -f elf32 -o asmfile.o asmfile.asm

program: cfile.o asmfile.o
	gcc -m32 -o program cfile.o asmfile.o -lm

clean:
	rm -rf cfile.o asmfile.o
	
