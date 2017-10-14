#ifndef MICROH
#define MICROH


#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>





typedef struct MicroInstruction{
	char leftOP[16];
	char OP[3];
	char rightOP[16];
} MicroInstruction;

/*No mover este include de aquí, es importante que MicroInstruction ya esté definido.
Podríamos hacer un solo archivo donde se definen todos los structs*/
#include "ALU.h"


void parseMicroMov(MicroInstruction microInstruction);
void parseMicroInstruction (MicroInstruction microInstruction);
void parseMicroMov(MicroInstruction microInstruction);
void parseMicroALU(MicroInstruction microInstruction);
void parseMicroMEM(MicroInstruction microInstruction);
MicroInstruction string2StructMicroInstruction(char *line);

#endif
