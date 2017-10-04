//	#include "ALU.c"


struct flags {
	//La Carry Flag, la Sign Flag, la Zero Flag y la Interrupt Flag
	short CF;
	short SF;
	short ZF;
	short IF;

};

struct ALU {
	short B1;
	short B2;
	short B3;
	short B4;
};


struct RT {
   
	short registros[4];

};


struct CPU {

	short mar;
	short mbr;
	short bdd;

	short * IR;
	short * PC;
};

