//cc -o malloc malloc.c && ./malloc

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MEM_SIZE 256
#define REGISTER_SIZE 2 //In Bytes



short * memory;


int initializeMemory(){
	

	/*Deberíamos usar short ints para que nos quepa un numero en un registro. 
	Ya que nuestros registros van a ser de 2 bytes*/
	printf ("The size of a short int is: %ld\n", sizeof(short));


	//Calloc usa malloc y asigna ceros en un solo paso. 
	//Retorna un puntero a un bloque de memoria donde caben MEM_SIZE ints
	memory = calloc (MEM_SIZE, REGISTER_SIZE);


	//Si el puntero que retorna es nulo, retorno 0
	if (!memory){
		printf ("Main memory calloc failed");
		return 0;
	}
	return 1;
}


void printHigh(short  numero){
	short shortie = numero>>8;
	if(numero < 0){
		shortie-=0xff00;
	}
	printf("%02hx\n", shortie);
}

void printLow(short  numero){
	short shortie = numero % 0x100;
	if(numero < 0){
		shortie-=0xff00;
	}
	printf("%02hx\n", shortie);
}

void printNum(short int numero){
	printf("%04hx\n", memory[0]);
}

/*int main() {
	if(!initializeMemory()) return 1;
	memory[0] = -3;
	printNum(memory[0]);
	printHigh(memory[0]);
	printLow(memory[0]);
	
	return 0;
}*/

struct instruction {
	short codigo;
	short arg1;
	short arg2;
	short cuartoDato;
} instruction;

/*int main ()
{
  char str[] ="This is:as string";
  char * location;
  location = strstr (str,":");
  char *str2 = calloc(3, sizeof(char));

  str2[0] = location[-2];
  str2[1] = location[-1];
  str[2] = '\0';

  printf("%s", str2);
  if (!strcmp(str2, "isa")){
  	printf ("IT IS IS");
  }

	printf("sizeof(instruction): %lu\n", sizeof(instruction));

  return 0;
}*/








