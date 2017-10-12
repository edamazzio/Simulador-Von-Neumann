#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "structs/ALU.c"

#include "ALU.c"
#include "microinstructions.c"
#include "archivos.c"

#define MEM_SIZE 256

struct Instruction {
	short codigo;
	short arg1;
	short arg2;
	short cuartoDato;
} instruction;

struct Instruction *memory;

int initializeMemory(){
	//Reserva memoria para la memoria (lol)
	memory = calloc(MEM_SIZE, sizeof(instruction));

	//Si calloc reornó un puntero y no NULL (cero), retorna 1.
	if (memory){
		return 1;
	}
	return 0;
}



int main (){
	//Inicializa la memoria y de paso revisa si el puntero es nulo.
	if (!initializeMemory()) printf ("Calloc for memory failed\n");

	//printf ("El codigo de la instruccion en la posicion 0 de la memoria es %d\n", memory[0].codigo);

	LeerArchivo();

	struct MicroInstruction a = scanMicroInstruction("B1<-11");
	parseMicroInstruction(a);

	struct MicroInstruction b = scanMicroInstruction("B2<-5");
	parseMicroInstruction(b);

	struct MicroInstruction c = scanMicroInstruction("ALU:div");
	parseMicroALU(c);



	//a = scanMicroInstruction("AX<-BX");
	//parseMicroInstruction(a);

	//struct ALU alu = {65535,-1,0,0};
	// printf("%lu \n",);

	//printf ("LEFTOP = %s\n RIGHTOP = %s\n OP = %s\n", a.leftOP, a.rightOP, a.operator);


}
