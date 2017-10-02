#include "microinstructions.h"

void parseMicroInstruction (char *instruction){
	
	char *separator;
	char *registerX = calloc(3, sizeof(char));
	char *registerY = calloc(3, sizeof(char));

	separator = strstr(instruction, "<");
	if (separator) {
		assignMovRegisters(registerX, registerY, separator);
		doMicroMov(registerX, registerY);
	}else {
		separator = strstr(instruction, ":");
		if (separator){
			//Check which instruction
		}
		else{
			//Is in, out or undefined
		}
	}
} 

void doMicroMov(char *X, char*Y){
	short reg1 = -1;
	short reg2 = -1;
	if (strcmp(X, "AX")){
		
	}
}




void assignMovRegisters(char * X, char * Y, char * separator){
	X[0] = separator[-2];
	X[1] = separator[-1];
	X[2] = '\0';

	Y[0] = separator[2];
	Y[1] = separator[3];
	Y[2] = '\0';
}

doMicroMov