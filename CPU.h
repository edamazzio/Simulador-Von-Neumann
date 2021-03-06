#include "microinstructions.h"
#include "Instruction.h"
#ifndef CPUH
#define CPUH



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEM_SIZE 256

extern char *registerNames[];
extern int registers[];
extern int registerNamesLength;
extern int cantInstruccionesASM;
extern struct Instruction *memory;
extern struct AFOCInstruction *AFOC;
struct Instruction MBR;

int initializeMemory();
void loadASMProgramToMemory(char *filename);
int loadAFOC(char *filename);

struct flags {
	/*La Carry Flag, la Sign Flag, la Zero Flag y la Interrupt Flag*/
	short CF;
	short SF;
	short ZF;
	short IF;

};


struct AFOCInstruction {
	char mnemonic[6];
	MicroInstruction micros[25];
};

#endif
