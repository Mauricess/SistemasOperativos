#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *distro;
char paquete[150];
FILE *paquetes;
char *archivo = "PacksAInstalar.txt";

/*
*Función que recibe una cadena con un paquetes
*Si está instalado devuelve 0 y lo omite
*Si no está instalado devuelve 1 y lo instala
*/
int instalador(char *pack){
    //Verificamos si el paquete está instalado
    //Creamos un archivo temporal
    FILE *installed;
    system("touch tempFile.txt");
    installed = fopen("tempFile.txt", "r");
    if(installed == NULL){
        perror("Error abriendo el archivo temporal");
        exit(1);
    }
    //Generamos la instrucción para verificar si está instalado el paquete
    char *cmd = malloc(sizeof(char)*150);
    strcpy(cmd, "rpm -qa | grep ");
    strcat(cmd, pack);
    strcat(cmd, " > tempFile.txt");
    //printf("ejecutando: %s\n", cmd);
    //ejecutamos la instruccion
    system(cmd);

    //verificamos si la salida no es NULL
    if (fgets( paquete, sizeof( paquete ), paquetes ) != NULL){
        printf("%s ya instalado o no existente\n", pack);
    }else{
        //Generamos la instrucción para intentar instalar
        char *instruc = malloc(sizeof(char)*170);
        strcpy(instruc, "sudo ");
        strcat(instruc, distro);
        strcat(instruc, " install ");
        strcat(instruc, pack);
        printf("ejecutando: %s\n",instruc );
        system(instruc);
    }
    //borramos el archivo temporal que Generamos
    fclose(installed);
    system("rm tempFile.txt");
}

int main(){
    int d;
    printf("El uso del instalador es para paquetes RPM usando DNF de RedHat\n");
    //printf("¿Qué distribución de linux usas? \n 0 - RedHat \t X- Debian\n");
    //scanf("%d", &d);
    //if(d == 0){
        printf("Usando RedHat... \n");
        distro = "dnf";
        printf("usando: %s\n", distro );
    /*}else{
        printf("Usando Debian... \n");
        distro = "apt-get";
        printf("usando: %s\n", distro);
    }*/
    //Se abre el archivo en modo leer
    paquetes = fopen(archivo,"r");

    if(paquetes == NULL){
        perror("Error abriendo el archivo");
        exit(1);
    }
    //Leemos línea a línea el archivo (paquete por paquete)
    //Verificamos si está instalado y en caso de no estarlo, lo instalamos
    while ( fgets( paquete, sizeof( paquete ), paquetes ) != NULL ){
        char *tempStr = malloc(sizeof(char)*(strlen(paquete)-2));
        strncpy(tempStr, paquete, strlen(paquete)-1);
        instalador(tempStr);
    }
    fclose( paquetes );
    return 0;
}
