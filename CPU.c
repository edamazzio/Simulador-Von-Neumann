#include "CPU.h"

char *registerNames[] = {"AX","BX","CX","DX","AL","BL","CL","DL","AH","BH","CH","DH","[dir]","[BL]","[BH]","B1", "B2", "B3", "B4", "BD","PC","IR", "MAR", "MBR"};
int registers[sizeof(registerNames)/sizeof(registerNames[0])];
int registerNamesLength = sizeof(registerNames)/sizeof(registerNames[0]);
struct Instruction MBR = {0,0,0,0,0};


struct Instruction *memory;

int initializeMemory(){
	/*Reserva memoria para la memoria (lol)*/
	memory = calloc(MEM_SIZE, sizeof(struct Instruction));

	/*Si calloc reornó un puntero y no NULL (cero), retorna 1.*/
	if (memory){
		return 1;
	}
	return 0;
}
