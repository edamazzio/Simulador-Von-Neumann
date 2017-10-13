#include "CPU.h"

char *registerNames[] = {"AX","BX","CX","DX","AL","BL","CL","DL","AH","BH","CH","DH","[dir]","[BL]","[BH]","B1", "B2", "B3", "B4", "BD","PC","IR", "MAR", "MBR"};
int registers[sizeof(registerNames)/sizeof(registerNames[0])];
int registerNamesLength = sizeof(registerNames)/sizeof(registerNames[0]);
struct Instruction MBR = {0,0,0,0,0};


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

int loadAFOC() {

	int cantInstruccionesASM = 0;
	AFOC = calloc(1,sizeof(struct AFOCInstruction));

    char  row[255];
    FILE  *fp;
    int contador = 1;

    fp = fopen( "AFOC.txt", "r" );

    if ( fp == NULL ) {
        // error handling..
    }

    while ( fgets( row, sizeof( row ), fp ) != NULL ) {
    
    if (row[0] == '#'){
    	cantInstruccionesASM++;
    	struct AFOCInstruction instruction;
    	instruction.microInstructions = calloc(contador, sizeof(struct MicroInstruction));
    	fgets( row, sizeof( row ), fp );
    	if (!row){
    		printf("Instruction incomplete \n");
    		break;
    	}
    	strcpy(instruction.mnemonic,row);
    	fgets( row, sizeof( row ), fp );
    	int ok = 1;
    	while(row[0] != '$'){   		
    		struct MicroInstruction micro;
    		micro = string2StructMicroInstruction(row);
    		if (!micro) {
    			ok = 0;
    			break;
    		}
    		instruction.microInstructions[contador] = micro;
    		contador++;
    		instruction.microInstructions = realloc(contador, sizeof(struct MicroInstruction));
    		

    	ok = 1;
    	}
    	if (!ok){
    		break;
    	}


    }
    else{
    	printf("Error \n");
    	return -1;
    }
    AFOC = realloc(1,sizeof(struct AFOCInstruction));
    AFOC[0] = instruction;
   
    /*
    puts( row );
    */
    }

    fclose( fp ); 


		/*Si buff tiene #, -
			creo el struct de AFOCInstruction -
			hago calloc del struct de microinstructions con 1 -
			contador = 1 -
			WIHLEY (buff != "$") -
				llamo a string2StructMicroInstruction con buff
				si me retornó algo
				 	guardo la microInstruction
					contador++
					realloc del puntero de microInstructions del struct AFOCInstruction. con contador
				else, detengo la vara
			go to WHILEY
            */

    return 0;
    }