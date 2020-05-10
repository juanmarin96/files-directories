#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

char *convertTime(time_t time);

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Número de argumentos inválido\n");
        return 1;
    }   

    struct stat stat_struct;


    if(stat(argv[1],&stat_struct) < 0){
        printf("Ha ocurrido un error obteniendo la información del archivo.\n");
        return 1;
    }    
 
    printf("---- INFORMACIÓN DEL ARCHIVO: ----\n");
    printf("Nombre: %s\n", argv[1]);
    printf("Tamaño: %d bytes\n",stat_struct.st_size);
    printf("# de bloques: %d\n",stat_struct.st_blocks);
    printf("Tamaño por bloque: %d\n",stat_struct.st_blksize);
    printf("# de links: %d\n",stat_struct.st_nlink);
    printf("Usuario (ID): %d\n",stat_struct.st_uid);
    printf("Grupo (ID): %d\n",stat_struct.st_gid);
    printf("Último acceso: \t\t\t\t%s", convertTime(stat_struct.st_atime));
    printf("Última modificación: \t\t\t%s", convertTime(stat_struct.st_atime));
 
    printf("Permisos del archivo:");
    printf( (S_ISDIR(stat_struct.st_mode)) ? "d" : "-");
    printf( (stat_struct.st_mode & S_IRUSR) ? "r" : "-");
    printf( (stat_struct.st_mode & S_IWUSR) ? "w" : "-");
    printf( (stat_struct.st_mode & S_IXUSR) ? "x" : "-");
    printf( (stat_struct.st_mode & S_IRGRP) ? "r" : "-");
    printf( (stat_struct.st_mode & S_IWGRP) ? "w" : "-");
    printf( (stat_struct.st_mode & S_IXGRP) ? "x" : "-");
    printf( (stat_struct.st_mode & S_IROTH) ? "r" : "-");
    printf( (stat_struct.st_mode & S_IWOTH) ? "w" : "-");
    printf( (stat_struct.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
 
    printf("¿Es un link simbólico? -> %s \n", (S_ISLNK(stat_struct.st_mode)) ? "True" : "False");
 
    return 0;
}

char *convertTime(time_t time)
{
    char *c_time_string;
    c_time_string = ctime(&time);
    return c_time_string;
}