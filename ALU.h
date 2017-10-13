#include <stdlib.h>
#include "CPU.h"

struct ALU {
	int B1;
	int B2;
	int B3;
	int B4;
};

struct AFOCInstruction {
	char mnemonic[6];
	struct MicroInstruction * microInstructions;
};


void MicroAdd(struct ALU *alu);
void MicroSub(struct ALU *alu);
void MicroMul(struct ALU *alu);
void MicroDiv(struct ALU *alu);
void MicroAnd(struct ALU *alu);
void MicroOr(struct ALU *alu);
void MicroXor(struct ALU *alu);
void MicroNot(struct ALU *alu);
void MicroShl(struct ALU *alu);
void MicroShr(struct ALU *alu);
