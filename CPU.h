//	#include "ALU.c"




struct flags {
	//La Carry Flag, la Sign Flag, la Zero Flag y la Interrupt Flag
	short CF;
	short SF;
	short ZF;
	short IF;

};

struct ALU {
	signed short B1;
	signed short B2;
	signed short B3;
	signed short B4;
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
