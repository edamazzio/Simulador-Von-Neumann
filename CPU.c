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
	int instructionCounter = 0;

	while ( fgets( row, sizeof( row ), fp ) != NULL ) {
		if(row[(strlen(row)-1)]=='\n') row[(strlen(row)-1)] = '\0';
		printf("Attemping codification of \"%s\" \n",row);
		Instruction instruction;
		instruction = codificarASM(row);
		printf("El valor de instruction.mnem es %d\n", instruction.instruction);
	  printf("El valor de instruction.arg1 es %d\n", instruction.arg1);
	  printf("El valor de instruction.arg2 es %d\n", instruction.arg2);
	  printf("El valor de instruction.cuartoDato es %d\n", instruction.cuartoDato);
	  printf("El valor de instruction.isInstruction es %d\n", instruction.isInstruction);
	}
	fclose( fp );
}


int loadAFOC() {
	char  row[255];
  FILE  *fp;
  fp = fopen( "AFOC.txt", "r" );

  int contador = 1;
	cantInstruccionesASM = 0;
	int sizeOfAFOC = sizeof(struct AFOCInstruction) + contador * sizeof(MicroInstruction);
	AFOC = calloc(1,sizeOfAFOC);

    if (AFOC){
            printf("Calloc successful AFOC  \n");
        }

    if ( fp == NULL ) {
        // error handling..
    }
    while ( fgets( row, sizeof( row ), fp ) != NULL ) {
			if(row[(strlen(row)-1)]=='\n') row[(strlen(row)-1)] = '\0';
			/*printf("row is \"%s\"\n", row);*/
			struct AFOCInstruction instruction;

	    if (row[0] == '#'){
	    	cantInstruccionesASM++;
	    	fgets( row, sizeof( row ), fp );
				if(row[(strlen(row)-1)]=='\n') row[(strlen(row)-1)] = '\0';
	    	if (!row[0]){
	    		printf("Instruction incomplete \n");
	    		break;
					return -1;
	    	}
	    	strcpy(instruction.mnemonic,row);
	    	fgets( row, sizeof( row ), fp );
				if(row[(strlen(row)-1)]=='\n') row[(strlen(row)-1)] = '\0';
	    	int ok = 1;
	    	while(row[0] != '$'){
	    		MicroInstruction micro;
	    		micro = string2StructMicroInstruction(row);

	    		if (!micro.leftOP[0]) {
	    			ok = 0;
	    			break;
	    		}
	    		instruction.micros[contador-1] = micro;

	    		contador++;
	        printf("Attemting microinstructions realloc \n");
					sizeOfAFOC *= cantInstruccionesASM;
	    		AFOC = realloc(AFOC, sizeOfAFOC);
	        printf("microinstructions realloc done\n");
	        break;

	    	ok = 1;
	    	}
	    	if (!ok){
	    		break;
					return -1;
	    	}
				strcpy(AFOC[cantInstruccionesASM-1].mnemonic, instruction.mnemonic);
				memcpy(&AFOC[cantInstruccionesASM-1].micros, &instruction.micros, sizeof(instruction.micros));

	    }

    }
    fclose( fp );
    return 0;
    }
