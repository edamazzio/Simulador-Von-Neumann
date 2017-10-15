#include "CPU.h"

char *registerNames[] = {"AX","BX","CX","DX","AL","BL","CL","DL","AH","BH","CH","DH","[dir]","[BL]","[BH]","B1", "B2", "B3", "B4", "BD","PC","IR", "MAR", "MBR"};
int registers[sizeof(registerNames)/sizeof(registerNames[0])];
int registerNamesLength = sizeof(registerNames)/sizeof(registerNames[0]);
struct Instruction MBR = {0,0,0,0,0};
int cantInstruccionesASM;


struct Instruction *memory;

struct AFOCInstruction *AFOC;

int initializeMemory(){
	/*Reserva memoria para la memoria (lol)*/
	memory = calloc(MEM_SIZE, sizeof(struct Instruction));

	/*Si calloc reornó un puntero y no NULL (cero), retorna 1.*/
	if (memory){
		return 1;
	}
	return 0;
}


void loadASMProgramToMemory(char *filename){

	char  row[255];
  FILE  *fp;
  fp = fopen( filename, "r" );
	if (!fp){
		printf("Error reading from file %s\n", filename);
	}printf ("ASM file %s opened succesfully\n", filename);
	int instructionCounter = 0;

	while ( fgets( row, sizeof( row ), fp ) != NULL ) {
		if(row[(strlen(row)-1)]=='\n') row[(strlen(row)-1)] = '\0';
		printf("Attemping codification of line\"%s\" \n",row);
		Instruction instruction;
		instruction = codificarASM(row);

		printf("\nSummary of codification:\n");
		printf("Value of instruction.mnem is %d\n", instruction.instruction);
	  printf("Value of instruction.arg1 is %d\n", instruction.arg1);
	  printf("Value of instruction.arg2 is %d\n", instruction.arg2);
	  printf("Value of instruction.cuartoDato is %d\n", instruction.cuartoDato);
	  printf("Value of instruction.isInstruction is %d\n\n\n", instruction.isInstruction);
	}
	fclose( fp );
}


int loadAFOC(char* filename) {
	char  row[255];
  FILE  *fp;
  fp = fopen( filename, "r" );
	if (!fp){
		printf ("Error loading file %s\n", filename);
		return -1;
	}else{
		printf ("Loaded file %s succesfully\n", filename);
	}

  int contador = 1;
	cantInstruccionesASM = 0;
	int sizeOfAFOC = sizeof(struct AFOCInstruction) + contador * sizeof(MicroInstruction);
	AFOC = calloc(1,sizeOfAFOC);

    if (AFOC){
            printf("Calloc successful AFOC  \n");
        }else{
					printf ("AFOC allocated correctly\n");
				}

    if ( fp == NULL ) {
        // error handling..
    }
    while ( fgets( row, sizeof( row ), fp ) != NULL ) {
			if(row[(strlen(row)-1)]=='\n') row[(strlen(row)-1)] = '\0';
			struct AFOCInstruction instruction;

	    if (row[0] == '#'){
				printf("# Found. Attempting to store microinstruction\n");
	    	cantInstruccionesASM++;
	    	fgets( row, sizeof( row ), fp );
				if(row[(strlen(row)-1)]=='\n') row[(strlen(row)-1)] = '\0';
	    	if (!row[0]){
	    		printf("Instruction incomplete \n");
	    		break;
					return -1;
	    	}
				printf("MicroInstruction will have mnemonic %s\n", row);
	    	strcpy(instruction.mnemonic,row);
	    	fgets( row, sizeof( row ), fp );
				if(row[(strlen(row)-1)]=='\n') row[(strlen(row)-1)] = '\0';
	    	int ok = 1;
	    	while(row[0] != '$'){
	    		MicroInstruction micro;
	    		micro = string2StructMicroInstruction(row);
					printf ("MicroInstruction stored. leftOP = %s, op = %s, rightOP = %s\n", micro.leftOP, micro.OP, micro.rightOP);
	    		if (!micro.leftOP[0]) {
	    			ok = 0;
	    			break;
						return -1;
	    		}

	    		instruction.micros[contador-1] = micro;
	    		contador++;
					sizeOfAFOC *= cantInstruccionesASM;
	    		AFOC = realloc(AFOC, sizeOfAFOC);
					fgets( row, sizeof( row ), fp );
					if(row[(strlen(row)-1)]=='\n') row[(strlen(row)-1)] = '\0';

	    	ok = 1;
	    	}
				printf("End of microinstructions found\n");
	    	if (!ok){
	    		break;
					return -1;
	    	}
				strcpy(AFOC[cantInstruccionesASM-1].mnemonic, instruction.mnemonic);
				memcpy(&AFOC[cantInstruccionesASM-1].micros, &instruction.micros, sizeof(instruction.micros));
				printf("Instruction %s has been stored into AFOC\n", instruction.mnemonic);

	    }

    }
    fclose( fp );
		printf("Done storing AFOC\n\n");
    return 0;
    }
