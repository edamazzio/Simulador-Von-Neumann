#include "CPU.h"

void MicroAdd(struct ALU *alu){
		alu->B3 = alu->B1 + alu->B2;
}

void MicroSub(struct ALU *alu){
	alu->B3 = alu->B1 - alu->B2;
} 

void MicroMul(struct ALU *alu){
	alu->B3 = alu->B1 * alu->B2;
}

void MicroDiv(struct ALU *alu){

	alu->B3 = alu->B1 / alu->B2;
	alu->B4 = alu->B1 % alu->B2;
}

void MicroAnd(struct ALU *alu){
	alu->B3 =  alu->B1 & alu->B2;
}

void MicroOr(struct ALU *alu){
	alu->B3 =  alu->B1 | alu->B2;
}

void MicroXor(struct ALU *alu){
	alu->B3 =  alu->B1 ^ alu->B2;
}

void MicroNot(struct ALU *alu){
	alu->B3 =  ~ alu->B1;
}

void MicroShl(struct ALU *alu){
	alu->B3 =  alu->B1>>1;
}

void MicroShr(struct ALU *alu){
	alu->B3 =  alu->B1<<1;
}