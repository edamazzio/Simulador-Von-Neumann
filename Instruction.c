#include "Instruction.h"

Instruction codificarASM(char *line){

  struct StringInstruction{
    char mnem[5];
    char arg1[5];
    char arg2[7];
  };

  Instruction instruction = {-1,-1,-1,-1,0};
  Instruction defaultInstruction = {-1,-1,-1,-1,-1};
  struct StringInstruction stringInstruction = {"","",""};
  int arg1Code = -1;
  int arg2COde = -1;
  int counter = 0;

  char *comma = strstr(line, ",");
  char *space = strstr (line, " ");
  char *start = line;
  char *end = line;
  while (*end)end++;

  if (!comma || !space){
    printf("Invalid instruction \"%s\"\n", line);
    return defaultInstruction;
  }
  space++;

  /*Pone el mnemonico en el struct temporal*/
  while (start != space) stringInstruction.mnem[counter++]= *start++;
  /*Finaliza el string*/
  stringInstruction.mnem[--counter] = '\0';
  counter = 0;

  /*Pone lo que está a la izquierda de la coma en el struct temporal arg1*/
  while (space != comma) stringInstruction.arg1[counter++]= *space++;

  stringInstruction.arg1[counter] = '\0';
  comma++;
  counter = 0;

  /*Pone lo que está a la derecha de la coma en el struct temporal arg2*/
  while (comma != end) stringInstruction.arg2[counter++] = *comma++;
  stringInstruction.arg2[counter++] = '\0';

  printf("Instruction %s has been separated as mnemonic = \"%s\", arg1 = \"%s\", arg2 = \"%s\"\n", line, stringInstruction.mnem, stringInstruction.arg1, stringInstruction.arg2);

  int size = cantInstruccionesASM;


  /*Revisa en la lista AFOC si el mnemonico existe*/
  int i =0;
  for (i = 0; i < size;i++){
    if (!strcmp(stringInstruction.mnem, AFOC[i].mnemonic)){
      printf("Instruction %s is defined in AFOC with code %d\n", stringInstruction.mnem,i);
      instruction.instruction = i;
      break;
    }
  }
  if (instruction.instruction == -1){
    printf ("Mnemonic \"%s\" not defined in AFOC\n", stringInstruction.mnem);
    return defaultInstruction;
  }

  /*Buscar arg1 in registerNames*/
  printf ("Looking for arg1 \"%s\" in registers...\n", stringInstruction.arg1);
  size = registerNamesLength;
  i = 0;
  for (i = 0; i < size; i++){
    if (!strcmp(stringInstruction.arg1, registerNames[i])){
      instruction.arg1 = i;
      printf("\"%s\" found in registers with code %d\n",stringInstruction.arg1, i );
      break;
    }
  }
  if (instruction.arg1 == -1){
    printf ("Arg1 \"%s\" is not valid\n", stringInstruction.arg1);
    return defaultInstruction;
  }


  /*Validar arg2*/
  printf("Validating arg2 \"%s\"\n", stringInstruction.arg2);
  /*Si es un número*/
  if (isdigit(stringInstruction.arg2[0])){
    printf("Arg 2 \"%s\" is an inmediate\nNumber will be assigned to 4th data\n", stringInstruction.arg2);

    /*Convertir inmediato a numero y ponerlo en el cuarto dato*/
    instruction.cuartoDato = strtol(stringInstruction.arg2,0,10);

    /*Poner este valor ahorita, determina si se encontró un arg2 más adelante cuando
    se pregunte si arg2 es -1 y cuartoDato fue asignado, lo cual sería correcto*/
    instruction.isInstruction = 1;

    printf("Done coding instruction %s\n", line);
    return instruction;
  }
  /*Si no es un número*/
  else{
    /*buscar en register names*/
    size = registerNamesLength;
    i = 0;
    for (i = 0; i < size; i++){
      printf("Comparing arg2 %s with %s\n", stringInstruction.arg2, registerNames[i]);
      if (!strcmp(stringInstruction.arg2, registerNames[i])){
        instruction.arg2 = i;
        printf("\"%s\" found in registers with code %d\n",stringInstruction.arg2, i );
        break;
      }
    }
  }

  /*Si no estaba en register names*/
  if (instruction.arg2 == -1){
    /*Revisar si es []*/
    if (stringInstruction.arg2[0] == '['){
      char *firstBracket = &stringInstruction.arg2[0];
      char *secondBracket = strstr(stringInstruction.arg2,"]");
      char betweenBrackets[4];
      counter = 0;
      firstBracket++;

      /*Si encontró un ]*/
      if (secondBracket){
        while(firstBracket!=secondBracket) betweenBrackets[counter++] = *firstBracket++;
        if (isdigit(betweenBrackets[0])){
          instruction.cuartoDato = strtol(betweenBrackets,0,10);
          instruction.arg2 = 12; /*Ver tabla de datos en especificación*/
        }else{
          printf ("Can't access memory from specified direction [%s]\n", betweenBrackets);
          return defaultInstruction;
        }
      }
      /*Si no encontró un ]*/
      else{
        printf("Found '[' but no ']'\n");
        return defaultInstruction;
      }
    }
    /*Si no es []*/
    else{
      printf ("Arg2 \"%s\" is not valid\n", stringInstruction.arg2);
      return defaultInstruction;
    }
  }

  /*If this line is reached, instruction is correct*/
  instruction.isInstruction = 1;
  return instruction;

}


/*Decodificary  ejecutar*//*
void decodeAndExec(Instruction instruction){

  int OPCode = instruction.instruction;
  struct AFOCInstruction ins;
  int sizeOfMicros = sizeof(ins.micros)/sizeof(ins.micros[0]);


  strcpy(ins.mnemonic, AFOC[OPCode].mnemonic);
  memcpy(&ins.micros, &AFOC[OPCode].micros, sizeof(ins.micros));
  printf("ins.micros[0].leftOP = %s\n", ins.micros[0].leftOP);
  int i = 0;
  for (i = 0; i < sizeOfMicros; i ++){
    if (!strcmp(ins.micros[i].leftOP, "X")){
      strcpy(ins.micros[i].leftOP, decodeArg(instruction, 1));
    }
    if (!strcmp(ins.micros[i].rightOP, "X")){
      strcpy(ins.micros[i].rightOP, decodeArg(instruction, 2));
    }
    if (!strcmp(ins.micros[i].leftOP, "Y")){
      strcpy(ins.micros[i].leftOP, decodeArg(instruction, 1));
    }
    if (!strcmp(ins.micros[i].rightOP, "Y")){
      strcpy(ins.micros[i].rightOP, decodeArg(instruction, 2));
    }
  }
}


void decodeArg(int arg){

}*/
