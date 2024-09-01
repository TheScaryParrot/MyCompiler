ExecuteSpeedC : ExecuteSpeed.c
	gcc -o ExecuteSpeedC ExecuteSpeed.c

ExecuteSpeedTHS : ExecuteSpeed.ths
	../../THSCompiler/THScompiler ExecuteSpeed.ths -s -o ExecuteSpeedTHS.o
	ld ExecuteSpeedTHS.o ../thsLib/print.o -o ExecuteSpeedTHS
	rm ExecuteSpeedTHS.o