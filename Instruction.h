#ifndef INSTRUCTIONH
#define INSTRUCTIONH

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "CPU.h"

typedef struct Instruction {
	int instruction;
	int arg1;
	int arg2;
	int cuartoDato;
	short isInstruction;
}Instruction ;


Instruction codificar(char *line);

#endif
