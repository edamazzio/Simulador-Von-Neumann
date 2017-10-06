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
	if (separator){
		microInstruction.operator[0] = separator[0];
		microInstruction.operator[1] = separator[1];
		microInstruction.operator[2] = '\0';
	} else {

		//If not <, find :
		separator = strstr(line, ":");
		if (separator){
			microInstruction.operator[0] = separator[0];
			microInstruction.operator[2] = '\0';
		} else {

			//If also not :, might be In or out
			//Next step would be to separate the separator from the two operands,
			//so, let's use the same pointer, point to the end of the string, to store only the left operand
			separator = line;
			while (*separator) separator++;

			printf("Separator is %c\n", *separator);
		}
	}

	//obtains the left operator
	while (iterator != separator) {
		if (*iterator == ' ') {
			iterator++; 
			continue;
		}
		microInstruction.leftOP[counter++] = *iterator++;
	}

	//Adds a \0 to end the char string
	microInstruction.leftOP[counter] = '\0';

	counter = 0;

	//If the operator is <-, the iterator must be incremented to point to the next letter
	if (microInstruction.operator[0]== '<') iterator++;
	iterator++;

	if (microInstruction.operator[0] == '\0') return microInstruction;
	
	//obtains the right operator
	while (*iterator != '\0') {
		if (*iterator == ' ') {
			iterator++; 
			continue;
		}
		microInstruction.rightOP[counter++] = *iterator++;
	}
	return microInstruction;
}



void parseMicroInstruction (struct MicroInstruction microInstruction){
	
	char *separator;
	char *registerX = calloc(3, sizeof(char));
	char *registerY = calloc(3, sizeof(char));

	separator = strstr(microInstruction.operator, "<");
	if (separator) {
		parseMicroMov(microInstruction);
		//assignMovRegisters(registerX, registerY, separator);
		//doMicroMov(registerX, registerY);
	}else {
		separator = strstr(microInstruction.operator, ":");
		if (separator){
			 if(!strcmp(microInstruction.leftOP, "ALU")){
			 	printf("ALU found\n");
			 } else if (!strcmp(microInstruction.leftOP, "MEM")){
			 	printf("MEM found\n");
			 } else if (!strcmp(microInstruction.leftOP, "TEST")){
			 	printf("TEST found\n");
			 } else printf("Microinstruction %s not recognized in %s%s%s\n", microInstruction.leftOP, microInstruction.leftOP, microInstruction.operator, microInstruction.rightOP);
			
		}
		else{
			// !!!strcmp returns 0 if strings are equal!!!
			if (!strcmp(microInstruction.leftOP, "IN")){
				printf("IN found\n");
			}else if (!strcmp(microInstruction.leftOP, "OUT")){
				printf("OUT found\n");
			}
			//microInstruction not recognized, print error to stdout.
			else printf("Microinstruction %s not recognized", microInstruction.leftOP);	

		}
	}
} 


void parseMicroMov(struct MicroInstruction microInstruction){
	i = 0;
	for (i = 0; i < )
}

/*void doMicroMov(char *X, char*Y){
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
*/
