#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFFER 10000
#define MAX_FINALE_LINES 30

int main(int argc, char* argv[]){

	FILE * fd;
    char buff[MAX_BUFFER];

	if(argc != 3) {
        printf("Número de argumentos inválidos\n");
        return 1;
    }

	if((fd = fopen(argv[2], "r")) == NULL) {//r: read
		printf("Erro abriendo el archivo.\n");
        return 1;
	}

	if((fseek(fd, 0, SEEK_END) == -1) || (fseek(fd, -1, SEEK_CUR) == -1)) {
		printf("Erro ejecutando el comando SEEK");
		return 1;
	}

    char lineas[MAX_FINALE_LINES];
    strcpy(lineas, argv[1]);
    int idxToDel = 0; 
    memmove(&lineas[idxToDel], &lineas[idxToDel + 1], strlen(lineas) - idxToDel);
	int tam = strlen(lineas);
    for(int i = 0; i < tam; i++){
        if(!isdigit(lineas[i])){
            printf ("Argumento inválido: debe ser un dígito.\n");
            exit(1);
        }
    }
	
    /*	Sabiendo que el argumento de líneas es un número podemos continuar.
    	El método para movernos a traves del archivo y así imprimir las líneas que
    	necesitamos es el siguiente.
    	Mientras que no encuentre el final del archivo o que no llegue a la ultima
    	línea por leer, avanzo de línea.
    */
	int n = atoi(lineas);
	int linea = 0;
	int caracter;

	while(1){
		if((caracter = fgetc(fd)) == '\n'){
			linea = linea + 1;
		}
		if(caracter == EOF){
			break;
		}
		if(n <= linea){
			break;
		}
		if(ungetc(caracter, fd) == EOF){
			printf("Error invocando la función UNGETC");
			return 1;
		}
		fseek(fd, -1, SEEK_CUR);
	}

	/*	Si logro salir del anterior ciclo sin presentar ningún error, quiere decir
		que estoy listo para imprimir.
	*/
	while(fgets(buff, MAX_BUFFER, fd) != NULL){
		printf("%s", buff);
	}
	printf("\n");
}