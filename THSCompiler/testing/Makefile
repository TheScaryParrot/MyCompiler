testFile: testFile.s
	nasm -f elf64 testFile.s && ld testFile.o -o testFile

testFile.s: testFile.THS
	../THScompiler testFile.THS > testFile.s




