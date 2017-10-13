#include "registers.h"


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


/*void assignMovRegisters(char * X, char * Y, char * separator);
void doMicroMov(char *X, char*Y);*/
