#include <stdio.h>
#include <stdlib.h>
#include "microinstructions.h"


/*Comando para compilar:
cc -x c -c Instruction.c && cc -x c -c microinstructions.c && cc -x c -c CPU.c &&   cc -x c -c ALU.c &&  cc -x c -c Simulador-Von-Newman-Chaverri-Isaac-Gonzalez-Esteban.c &&  cc ALU.o CPU.o microinstructions.o  Instruction.o Simulador-Von-Newman-Chaverri-Isaac-Gonzalez-Esteban.o -o VonNeumann &&  ./VonNeumann AFOC.txt program.asm
*/


int main ( int argc, char *argv[] ){


	/*AFOCInstriction es una lista con toda la arquitectura (Instrucciones ASM)*/
	struct AFOCInstruction *AFOC;

	if (!initializeMemory()) {
		printf ("Calloc for memory failed\n");
		return 1;
	}else{
		printf("Memory initialized correctly!\n");
	}
	/*Leer un programa en ensamblador*/

	/*Al ejecutar, hay que reemplazar X por arg1 y Y por arg2 (no dentro de AFOC,
	si no una copia que es el que se va a ejecutar) */
	if (argc == 1){
		printf ("Not enough arguments. Use -h for help\n");
		return 1;
	}
	else if (argc == 2){
		if (!strcmp(argv[1], "-h") ){
			printf ("Usage <nombreArchivoAFOC> <nombreArchivoASM>. AFOC.txt is the default file. Please specify it.\n");
			return 0;
		}else{
			printf ("Argument \"%s\" not recognized. Use -h for help", argv[1]);
			return 1;
		}
	}
	else if (argc == 3){
		printf ("Loading AFOC from file %s\n", argv[1]);
		int loadAFOCresult = loadAFOC(argv[1]);
		if (loadAFOCresult == -1){
			printf ("An error has occured loading AFOC\n");
			return 1;
		}
		loadASMProgramToMemory(argv[2]);
	} else{
		printf("Not enough arguments. Use -h for help.\n");
		return 1;
	}



	printf("Here ends what has been done of the progam. \nThe following are parsings of microinstructions to prove that the parser works");

	printf("Running command MicroInstruction a = string2StructMicroInstruction(\"B1<-11\");\n Parsing a");
	MicroInstruction a = string2StructMicroInstruction("B1<-11");
	parseMicroInstruction(a);

	printf("Running command MicroInstruction b = string2StructMicroInstruction(\"B2<-5\");\n Parsing b");
	MicroInstruction b = string2StructMicroInstruction("B2<-5");
	parseMicroInstruction(b);

	printf("Running command MicroInstruction c = string2StructMicroInstruction(\"ALU:add\");\n Parsing c");
	MicroInstruction c = string2StructMicroInstruction("ALU:add");
	parseMicroALU(c);

	printf("Running command c = string2StructMicroInstruction(\"ALU:mul\");\n Parsing c");
	c = string2StructMicroInstruction("ALU:mul");
	parseMicroALU(c);

	int i = 0;
	for (i = 0; i < registerNamesLength; i++){
		printf("Value of %s is %d\n", registerNames[i], registers[i]);
	}



	return 0;

}
