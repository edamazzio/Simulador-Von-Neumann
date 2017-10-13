/*
gcc -o archivos archivos.c
./archivos

gcc -o prueba /home/isaac/Documents/Progra3/prueba.c `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0`
./prueba
*/

#include <stdio.h>

int LeerArchivo() {



	FILE *fp;
    char buff[255];


	fp = fopen("AFOC.txt", "w+");
    fprintf(fp, "Linea numero 1\n");
    fputs("Linea numero 2\n", fp);
    fclose(fp);

    fp = fopen("AFOC.txt", "r");

    int c;

    while (fscanf(fp, "%s", buff) == 1)
    {
        /*
        ** Do something with c, such as check against '\n'
        ** and increment a line counter.
        */
   	fgets(buff, 255, (FILE*)fp);
    printf("%s", buff );

		/*Si buff tiene #,
			creo el struct de AFOCInstruction
			hago calloc del struct de microinstructions con 1
			contador = 1
			WIHLEY (buff != "$")
				llamo a string2StructMicroInstruction con buff
				si me retornó algo
				 	guardo la microInstruction
					contador++
					realloc del puntero de microInstructions del struct AFOCInstruction. con contador
				else, detengo la vara
			go to WHILEY
*/
    }


   fclose(fp);

   return 0;
}
