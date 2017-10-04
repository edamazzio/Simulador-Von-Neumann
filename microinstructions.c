#include "microinstructions.h"

struct MicroInstruction{
	char leftOP[16];
	char operator[3];
	char rightOP[16];
};

struct MicroInstruction scanMicroInstruction(char *line){
	struct MicroInstruction microInstruction = {"","",""};
	short counter = 0;
	char *iterator = line;
	char *separator;

	//Look for <
	separator = strstr(line, "<");

	//If not <, find :
	if (!separator)	separator = strstr(line, ":");

	//If also not :, might be In or out
	//Next step would be to separate the separator from the two operands,
	//so, let's use the same pointer, point to the end of the string, to store only the left operand
	if (!separator) while ((separator=&line[counter])!='\0')counter++;
			
	while (iterator != separator){
		//do
	}

	return microInstruction;
}



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

	//Revisar si es un inmediato

	Y[0] = separator[2];
	Y[1] = separator[3];
	Y[2] = '\0';
}

