#include "Instruction.h"
#include <stdlib.h>
#define MEM_SIZE 256

extern char *registerNames[];
extern int registers[];
extern int registerNamesLength;
extern struct Instruction *memory;
struct Instruction MBR;

int initializeMemory();

struct flags {
	/*La Carry Flag, la Sign Flag, la Zero Flag y la Interrupt Flag*/
	short CF;
	short SF;
	short ZF;
	short IF;

};
