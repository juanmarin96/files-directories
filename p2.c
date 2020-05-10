#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define PATH_MAX 4096

int main(int argc, char* argv[]){

    if(argc > 4){
        printf("Número de parámetros inválido.\n");
        return 1;
    }

    DIR *directorio;
    struct dirent *archivo;
    struct stat mystat;

    /*  Se debe analizar todas las posibles opciones de parámetros que pueden aparecer
        1) Cuando no hay parámetros. > ./p2.out 
        2) Cuando el único parámetro es -l > ./p2.out -l
        3) Cuando el parámetro es el directorio. > ./p2.out ../DIRECTORIO
        4) Cuando el parámetro es el directorio y -l. > ./p2.out -l ../DIRECTORIO
    */

    // CASO 1)
    if(argc == 1){
        directorio = opendir(".");
        while((archivo = readdir(directorio)) != NULL){
            printf("%s\t", archivo->d_name);
        }    
        printf("\n");
        closedir(directorio);
        return 0;
    }

    // CASO 2) Para este caso particular podemos hacer uso del punto anteriormente resulto.
    if(argc == 2 && strcmp(argv[1],"-l") == 0) {

        directorio = opendir(".");
        char buffer[PATH_MAX];

        while((archivo = readdir(directorio)) != NULL){
            sprintf(buffer, "%s/%s", argv[1], archivo->d_name);    
            char file[100];
            strcpy(file, "./p1.out ");
            strcat(file, archivo->d_name);
            int status = system(&file);
        }
        printf("\n");
        closedir(directorio);
        return 0;
    }

    // CASO 3)
    if(argc == 2 && strcmp(argv[1],"-l") != 0) {
        directorio = opendir(argv[1]);
        while((archivo = readdir(directorio)) != NULL){
            printf("%s\n", archivo->d_name);
        }    
        printf("\n");
        closedir(directorio);
        return 0;
    }

    // CASO 4) Para este caso particular podemos hacer uso del punto anteriormente resulto.
    if(argc == 3 && strcmp(argv[1],"-l") == 0){
        directorio = opendir(argv[2]);
        char buffer[PATH_MAX];

        while((archivo = readdir(directorio)) != NULL){
            sprintf(buffer, "%s/%s", argv[1], archivo->d_name);
            char file[100];
            strcpy(file, "./p1.out ");
            strcat(file, argv[2]);
            strcat(file, "/");
            strcat(file, archivo->d_name);
            int status = system(&file);
        }   
        closedir(directorio);
        return 0;
    }
}