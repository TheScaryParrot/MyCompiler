ExecuteSpeedC : ExecuteSpeed.c
	gcc -o ExecuteSpeedC ExecuteSpeed.c

ExecuteSpeedTHS : ExecuteSpeed.ths
	../../THSCompiler/THScompiler ExecuteSpeed.ths -s -o ExecuteSpeedTHS.o
	ld ExecuteSpeedTHS.o ../thsLib/print.o -o ExecuteSpeedTHS
	rm ExecuteSpeedTHS.o

ExecuteSpeedQHS : ExecuteSpeed.qhs
	cp ../../QHSCompiler/testing/lib.qhs ../qhsLib/
	../../QHSCompiler/QHScompiler ExecuteSpeed.qhs -o ExecuteSpeedQHS