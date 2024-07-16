testFile: testFile.s
	nasm -f elf64 testFile.s && gcc -o testFile testFile.o -lm

testFile.s: testFile.QHS
	../QHScompiler testFile.QHS > testFile.s




