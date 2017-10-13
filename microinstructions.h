
#ifndef MICROH
#define MICROH

#include "ALU.h"
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>


struct MicroInstruction{
	char leftOP[16];
	char operator[3];
	char rightOP[16];
};




void parseMicroMov(struct MicroInstruction microInstruction);
void parseMicroInstruction (struct MicroInstruction microInstruction);
void parseMicroMov(struct MicroInstruction microInstruction);
void parseMicroALU(struct MicroInstruction microInstruction);
void parseMicroMEM(struct MicroInstruction microInstruction);
struct MicroInstruction string2StructMicroInstruction(char *line);

#endif
