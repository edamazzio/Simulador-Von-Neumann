#include <stdio.h>
#include <stdlib.h>
#include "microinstructions.h"


/*Comando para compilar:
cc -x c -c Instruction.c && cc -x c -c microinstructions.c && cc -x c -c CPU.c &&   cc -x c -c ALU.c &&  cc -x c -c Simulador-Von-Newman-Chaverri-Isaac-Gonzalez-Esteban.c &&  cc ALU.o CPU.o microinstructions.o  Instruction.o Simulador-Von-Newman-Chaverri-Isaac-Gonzalez-Esteban.o -o VonNeumann &&  ./VonNeumann
*/


int main ( int argc, char *argv[] ){


	/*AFOCInstriction es una lista con toda la arquitectura (Instrucciones ASM)*/
	struct AFOCInstruction *AFOC;

	/*Leer un programa en ensamblador*/

	/*Al ejecutar, hay que reemplazar X por arg1 y Y por arg2 (no dentro de AFOC,
	si no una copia que es el que se va a ejecutar) */
	if (argc == 2){
		if (!strcmp(argv[1], "-h") ){
			printf ("Printing help.");
			return 0;
		}else{
			printf ("Loading AFOC from file %s\n", argv[1]);
			int loadAFOCresult = loadAFOC(argv[1]);
			if (loadAFOCresult == -1){
				printf ("An error has occured loading AFOC\n");
			}
		}
	}else{
		loadAFOC("AFOC.txt");
		rintf ("Loading AFOC from file AFOC.txt\n");
	}
	printf ("argv[1] is %s\n", argv[1]);

	if (!initializeMemory()) printf ("Calloc for memory failed\n");


	//loadASMProgramToMemory("program.asm");

	//Instruction ins = {0,0,1,0,1};
	//decodeAndExec(ins);
	return 0;

/*
	MicroInstruction a = scanMicroInstruction("B1<-11");
	parseMicroInstruction(a);

	MicroInstruction b = scanMicroInstruction("B2<-5");
	parseMicroInstruction(b);

	MicroInstruction c = scanMicroInstruction("ALU:add");
	parseMicroALU(c);*/





}
