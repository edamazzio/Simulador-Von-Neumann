#include <stdio.h>
#include <stdlib.h>
#include "microinstructions.h"


/*Comando para compilar:
 cc -x c -c ALU.c &&  cc -x c -c CPU.c &&  cc -x c -c microinstructions.c &&  cc -x c -c Simulador-Von-Newman-Chaverri-Isaac-Gonzalez-Esteban.c &&  cc -o VonNeumann ALU.o CPU.o microinstructions.o Simulador-Von-Newman-Chaverri-Isaac-Gonzalez-Esteban.o &&  ./VonNeumann
*/


int main (){
	if (!initializeMemory()) printf ("Calloc for memory failed\n");

	/*LeerArchivo();*/

	struct MicroInstruction a = scanMicroInstruction("B1<-11");
	parseMicroInstruction(a);

	struct MicroInstruction b = scanMicroInstruction("B2<-5");
	parseMicroInstruction(b);

	struct MicroInstruction c = scanMicroInstruction("ALU:add");
	parseMicroALU(c);





}
