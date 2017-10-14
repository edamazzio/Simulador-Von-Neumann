#include <stdio.h>
#include <stdlib.h>
#include "microinstructions.h"


/*Comando para compilar:
cc -x c -c microinstructions.c && cc -x c -c CPU.c &&   cc -x c -c ALU.c &&  cc -x c -c Simulador-Von-Newman-Chaverri-Isaac-Gonzalez-Esteban.c &&  cc -o VonNeumann ALU.o CPU.o microinstructions.o Simulador-Von-Newman-Chaverri-Isaac-Gonzalez-Esteban.o &&  ./VonNeumann
*/


int main (){
	if (!initializeMemory()) printf ("Calloc for memory failed\n");

	/*AFOCInstriction es una lista con toda la arquitectura (Instrucciones ASM)*/
	struct AFOCInstruction *AFOC;

	/*Leer un programa en ensamblador*/

	/*Al ejecutar, hay que reemplazar X por arg1 y Y por arg2 (no dentro de AFOC,
	si no una copia que es el que se va a ejecutar) */

	loadAFOC();

/*
	MicroInstruction a = scanMicroInstruction("B1<-11");
	parseMicroInstruction(a);

	MicroInstruction b = scanMicroInstruction("B2<-5");
	parseMicroInstruction(b);

	MicroInstruction c = scanMicroInstruction("ALU:add");
	parseMicroALU(c);*/





}
