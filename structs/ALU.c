#include <stdio.h>
#include "ALU.h"

void add(registro1, registro2){
		B3 = B1 + B2;
}

void sub(){
	B3 = B1 - B2;
}

void mul(){
	B3 = B1 * B2;
}

void div(){

	B3 = B1 / B2;
	B4 = B1 % B2;
}

void and(){
	B3 =  B1 & B2;
}

void or(){
	B3 =  B1 | B2;
}

void xor(){
	B3 =  B1 ^ B2;
}

void not(){
	B3 =  B1 ! B2;
}

void shl(){
	B3 =  B1>>1;
}

void shr(){
	B3 =  B1<<1;
}