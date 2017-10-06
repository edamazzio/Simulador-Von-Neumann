#include "CPU.h"

void microadd(struct ALU *alu){
		alu->B3 = alu->B1 + alu->B2;
}

void microsub(struct ALU *alu){
	alu->B3 = alu->B1 - alu->B2;
} 

void micromul(struct ALU *alu){
	alu->B3 = alu->B1 * alu->B2;
}

void microdiv(struct ALU *alu){

	alu->B3 = alu->B1 / alu->B2;
	alu->B4 = alu->B1 % alu->B2;
}

void microand(struct ALU *alu){
	alu->B3 =  alu->B1 & alu->B2;
}

void microor(struct ALU *alu){
	alu->B3 =  alu->B1 | alu->B2;
}

void microxor(struct ALU *alu){
	alu->B3 =  alu->B1 ^ alu->B2;
}

void micronot(struct ALU *alu){
	alu->B3 =  ~ alu->B1;
}

void microshl(struct ALU *alu){
	alu->B3 =  alu->B1>>1;
}

void microshr(struct ALU *alu){
	alu->B3 =  alu->B1<<1;
}