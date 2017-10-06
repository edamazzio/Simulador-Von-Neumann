#include "microinstructions.h"
#include <ctype.h>


char *registerNames[] = {"AX","BX","CX","DX","AL","BL","CL","DL","AH","BH","CH","DH","[dir]","[BL]","[BH]","B1", "B2", "B3", "B4", "BD","PC", "IR"};
short registers[sizeof(registerNames)/sizeof(registerNames[0])];



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
			else printf("Microinstruction %s not recognized\n", microInstruction.leftOP);

		}
	}
}


void parseMicroMov(struct MicroInstruction microInstruction){

	//Check if operands are memory addresses
	if (microInstruction.leftOP[0]=='[' ){
		printf("MicroInstruction invalid, can't <- between memory addresses: \"%s\"\n", microInstruction.leftOP);
		return;
	}
	if (microInstruction.rightOP[0]=='[' ){
		printf("MicroInstruction invalid, can't <- between memory addresses: \"%s\"\n", microInstruction.rightOP);
		return;
	}

	int i = 0;
	int size = sizeof(registerNames)/sizeof(registerNames[0]);
	int leftRegisterIndex = -1;
	int rightRegisterIndex = -1;

	//Check if leftOP is a register
	for (i = 0; i < size;i++){
		if (!strcmp(microInstruction.leftOP, registerNames[i])){
			leftRegisterIndex = i;
			printf ("leftOP found at registerNames[%d]=%s\n",i,registerNames[i]);
			break;
		}
	}

	//If a register was found on the left side
	if (leftRegisterIndex!= -1){

		//Check if rightOP is digit. If so, take the whole rightOP as a number
		if (isdigit(microInstruction.rightOP[0])){

			printf("It was a digit\n");

			//DO MOV. strtol converts a string to integer
			registers[leftRegisterIndex] = strtol(microInstruction.rightOP,0,10);
			return;
		}

		//Check if rightOP is a register
		for (i = 0; i < size;i++){
			if (!strcmp(microInstruction.rightOP, registerNames[i])){
				rightRegisterIndex = i;
				printf ("rightOP found at registerNames[%d]=%s\n",i,registerNames[i]);
				break;
			}
		}
		//If a register was found on the right side
		if (rightRegisterIndex!= -1){

			//DO MOV
			registers[leftRegisterIndex] = registers[rightRegisterIndex];
			for (i=0;i<size;i++){
				printf("registers[%d]=%d\n", i, registers[i]);
			}

		}else{
			printf("MicroInstruction <- not valid. Invalid right operand: \"%s\"\n", microInstruction.rightOP);
		}


	}else{
		printf("MicroInstruction <- not valid. Invalid left operand: \"%s\"\n", microInstruction.leftOP);
	}
}

void parseMicroALU(struct MicroInstruction microInstruction){

	

	int i = 0;
	int size = sizeof(registerNames)/sizeof(registerNames[0]);
	int B1 = -1;
	int B2 = -1;
	int B3 = -1;
	int B4 = -1;

	//Check if leftOP is a register
	for (i = 0; i < size;i++){
		if (!strcmp("B1", registerNames[i])){
			B1 = i;
			B2 = i+1;
			B3 = i+2;
			B4 = i+3;
			printf ("B registers found at registerNames[%d]=%s\n",i,registerNames[i]);
			break;
		}
	}

	struct ALU alu = {registers[B1],registers[B2],registers[B3],registers[B4]};

	printf("%s \n",microInstruction.leftOP);

	if (microInstruction.leftOP == "ALU"){

		if (microInstruction.rightOP == "add"){

			MicroAdd(&alu);

		}

		if (microInstruction.rightOP == "sub"){

			MicroSub(&alu);

		}

		if (microInstruction.rightOP == "mul"){

			MicroMul(&alu);

		}

		if (microInstruction.rightOP == "div"){

			MicroDiv(&alu);

		}

		if (microInstruction.rightOP == "and"){

			MicroAnd(&alu);

		}
		

		if (microInstruction.rightOP == "or"){

			MicroOr(&alu);

		}

		if (microInstruction.rightOP == "xor"){

			MicroXor(&alu);

		}

		if (microInstruction.rightOP ==  "not"){

			MicroNot(&alu);

		}

		if (microInstruction.rightOP == "shr"){

			MicroShr(&alu);

		}

		if (microInstruction.rightOP == "shl"){

			MicroShl(&alu);

		}



		registers[B1] = alu.B1;
		registers[B2] = alu.B2;
		registers[B3] = alu.B3;
		registers[B4] = alu.B4;
		printf("%d \n",B1);
		printf("%d \n",B2);
		printf("%d \n",B3);
		printf("%d \n",B4);

	}


	else{

		printf("MicroInstruction not recognized \"%s\"\n", microInstruction.leftOP);
		return;

		}

	
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
