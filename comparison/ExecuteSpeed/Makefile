ExecuteSpeed: ExecuteSpeed.c ExecuteSpeed.ths ExecuteSpeed.qhs
	gcc -o ExecuteSpeedC ExecuteSpeed.c

	../../THSCompiler/THScompiler ExecuteSpeed.ths -s -o ExecuteSpeedTHS.o
	ld ExecuteSpeedTHS.o ../thsLib/print.o -o ExecuteSpeedTHS
	rm ExecuteSpeedTHS.o

	../../QHSCompiler/QHScompiler ExecuteSpeed.qhs -o ExecuteSpeedQHS