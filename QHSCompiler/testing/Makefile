testFile: testFile.s
	nasm -f elf64 testFile.s && ld -o testFile testFile.o

testFile.s: testFile.QHS
	../QHScompiler testFile.QHS > testFile.s




