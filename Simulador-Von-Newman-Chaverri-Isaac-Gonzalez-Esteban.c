#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instruction.h"
#include "ALU.c"
#include "microinstructions.c"

#define MEM_SIZE 256



int initializeMemory(){
	/*Reserva memoria para la memoria (lol)*/
	memory = calloc(MEM_SIZE, sizeof(instruction));

	/*Si calloc reornó un puntero y no NULL (cero), retorna 1.*/
	if (memory){
		return 1;
	}
	return 0;
}



int main (){
	/*.*/	if (!initializeMemory()) printf ("Calloc for memory failed\n");


	struct MicroInstruction a = scanMicroInstruction("B1<-11");
	parseMicroInstruction(a);

	struct MicroInstruction b = scanMicroInstruction("B2<-5");
	parseMicroInstruction(b);

	struct MicroInstruction c = scanMicroInstruction("ALU:div");
	parseMicroALU(c);





}
