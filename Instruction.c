#include "Instruction.h"

Instruction codificar(char *line){

  struct StringInstruction{
    char mnem[5];
    char arg1[5];
    char arg2[5];
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

  if (!comma || !space){
    printf("Invalid instruction \"%s\"\n", line);
    return defaultInstruction;
  }
  space++;

  /*Pone el mnemonico en el struct temporal*/
  while (start != space) stringInstruction.mnem[counter++]= *start++;
  /*Finaliza el string*/
  stringInstruction.mnem[counter] = '\0';
  counter = 0;

  /*Pone lo que está a la izquierda de la coma en el struct temporal arg1*/
  while (space != comma) stringInstruction.arg1[counter++]= *space++;

  stringInstruction.arg1[counter] = '\0';
  comma++;
  counter = 0;
  /*Pone lo que está a la derecha de la coma en el struct temporal arg2*/
  while (comma[counter]!='\0') stringInstruction.arg2[counter++] = *comma++;
  stringInstruction.arg2[counter++] = '\0';


  struct AFOCInstruction *AFOC;
  int size = sizeof(AFOC)/sizeof(AFOC[0]);

  /*Revisa en la lista AFOC si el mnemonico existe*/
  int i =0;
  for (i = 0; i < size;i++){
    if (!strcmp(stringInstruction.mnem, AFOC[i].mnemonic)){
      instruction.instruction = i;
    }
  }
  if (instruction.instruction == -1){
    printf ("Mnemonic \"%s\" not defined in AFOC\n", stringInstruction.mnem);
    return defaultInstruction;
  }

  /*Buscar arg1 in registerNames*/
  size = registerNamesLength;
  i = 0;
  for (i = 0; i < size; i++){
    if (!strcmp(stringInstruction.arg1, registerNames[i])){
      instruction.arg1 = i;
    }
  }
  if (instruction.arg1 == -1){
    printf ("Arg1 \"%s\" is not valid\n", stringInstruction.arg1);
    return defaultInstruction;
  }


  /*Validar arg2*/

  /*Si es un número*/
  if (isdigit(stringInstruction.arg2[0])){

    printf("It is an inmediate\n");

    /*Convertir inmediato a numero y ponerlo en el cuarto dato*/
    instruction.cuartoDato = strtol(stringInstruction.arg2,0,10);

    /*Poner este valor ahorita, determina si se encontró un arg2 más adelante cuando
    se pregunte si arg2 es -1 y cuartoDato fue asignado, lo cual sería correcto*/
    instruction.isInstruction = 1;
  }
  /*Si no es un número*/
  else{
    /*buscar en register names*/
    size = registerNamesLength;
    i = 0;
    for (i = 0; i < size; i++){
      if (!strcmp(stringInstruction.arg2, registerNames[i])){
        instruction.arg2 = i;
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
          printf ("Can't access memory from specified direction [%s]\n", stringInstruction.arg2);
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
      printf ("Arg2 \"%s\" is not valid\n", stringInstruction.arg1);
      return defaultInstruction;
    }
  }

  /*If this line is reached, instruction is correct*/
  instruction.isInstruction = 1;
  printf("El valor de instruction.mnem es %d\n", instruction.instruction);
  printf("El valor de instruction.arg1 es %d\n", instruction.arg1);
  printf("El valor de instruction.arg2 es %d\n", instruction.arg2);
  printf("El valor de instruction.cuartoDato es %d\n", instruction.cuartoDato);
  printf("El valor de instruction.isInstruction es %d\n", instruction.isInstruction);


  return instruction;



  /*
  printf ("Arg1 \"%s\" not defined in AFOC\n", stringInstruction.arg1);
  return;*/


}
