include /home/pi/btoblas/make.inc

## VER should be gemver__2.c
## [CE]TESTER should be gemver[CE]Tester.c
## PREC should be either DREAL or SREAL
## DEFS are optional, allows for command line defines
##	for example: -DBTO_TILE
##
## make correctness VER=gemver__2.c CTESTER=gemverCTester.c PREC=DREAL
## make empirical VER=gemver__2.c ETESTER=gemverETester.c PREC=DREAL
## make empirical VER=gemver__2.c ETESTER=gemverETester.c PREC=DREAL DEFS=-DBTO_TILE
## run with ./a.out
##
## build setting are controlled from top level directory - make.inc


correctness : $(VER) $(CTESTER)
	@$(TCC) $(TFLAGS) $(CORRECT_INC) $(VER) $(CTESTER) -D$(PREC) $(DEFS)

empirical : $(VER) $(ETESTER)
	@$(TCC) $(TFLAGS) $(EMPIRIC_INC) $(VER) $(ETESTER) -D$(PREC) $(DEFS)

