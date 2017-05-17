#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mount.h>
#include <dirent.h>

void montarSistArchivos(char *fuente, char *destino);
void copiarFuente(char *fuente, char *destino);
void copiarDestino(char *fuente, char *destino);
void creaTempVal();

int main(int argc, char const *argv[]) {

  FILE *f;
  char *destino = malloc(sizeof(char) * 512);
  char *fuente = malloc(sizeof(char) * 512);

  f = fopen(argv[1], "r");
  
  fscanf(f, "%s", fuente);
  fscanf(f, "%s", destino);
 
  montarSistArchivos(fuente, destino);
  copiarFuente(fuente, destino);
  creaTempVal("tmp0");
  printf("Presiona <enter> cuando hayas terminado de trabajar.");
  getchar();
  copiarDestino(fuente, destino);
  umount(destino);
  return 0;
}

void montarSistArchivos(char *fuente, char *destino){  
  struct stat st = {0};  
  if (stat(destino, &st) == -1) {
    mkdir(destino, 0777);
    printf("Carpeta destino creada con exito\n");
  }
  
  int res = mount(fuente, destino, "tmpfs", 0, "mode=0777");

  if (res == 0) {
    printf("Montado sobre RAM exitoso en la ubicacion: %s...\n", destino);
    //printf("Presiona <enter> para desmontar\n");
    //getchar();
    //umount(destino);
  }
  else{
    printf("Error al montar.\n");
  }

}

void copiarFuente(char *fuente, char *destino)
{
 DIR *f = NULL;
  char fil[512];
  char instr[512];
  struct dirent *drnt = NULL;
  f = opendir(fuente);
  if(f){
    while (drnt = readdir(f)) {
      if(!strcmp(drnt->d_name,"."))
        continue;
      if(!strcmp(drnt->d_name,".."))
        continue;
      if(drnt->d_type == 10){
        sprintf(fil,"%s/%s",fuente,drnt->d_name);
        sprintf(instr,"cp -rp %s %s",fil,destino);
        system(instr);
      }else{
        sprintf(fil,"%s/%s",fuente,drnt->d_name);
        sprintf(instr,"cp -a %s %s",fil,destino);
        system(instr);
      }
    }
    closedir(f);
  }else{
    printf("No se puede abrir el directorio %s\n", fuente);
  } 
}

void copiarDestino(char *fuente, char *destino){
    creaTempVal("tmp1");
    FILE* t1;
    FILE* t2;
    t1 = fopen("tmp0", "r");
    t2 = fopen("tmp1", "r");
    if(t1 == NULL || t2 == NULL){
        perror("Error abriendo el archivo temporal");
	umount(destino);
        exit(1);
    }
    char s1[512];
    char s2[512];
    char aux1[512];
    char aux2[512];
    *s1 = *s2 = *aux1 = *aux2 ='\0';
    //buscamos en donde hicmos los cambios
    while (fgets(aux1, sizeof(aux1)-1, t2) != NULL) {
        //nombre del archivo:
        strcpy(s1, aux1);
        //printf("nombreOLD %s\n", s1);
        //Fecha de modif:
        fgets(aux1, sizeof(aux1)-1, t2);
        //printf("fechaOLD %s\n", aux1);
        t1 = fopen("tmp0", "r");
        //buscamos el nombre y la fecha en t1(lo antiugo)
        while (fgets(aux2, sizeof(aux2)-1, t1) != NULL) {
            if(strcmp(s1, aux2) == 0){
                //si los nombrelsees encajan, obtenermos la fecha:
                fgets(s2, sizeof(s2)-1, t1);
                if(strcmp(aux1, s2) == 0){
                    //Si encajan las fechas nada cambió
                //    printf("no cambió %s\n", s1);
                    fclose(t1);
                    t1 =NULL;
                    break;
                }else{//copiamos los nuevos archivos a fuente
                //    printf("ALTER %s\n", s1);
                    fclose(t1);
                    t1 = NULL;
                    *aux2 = '\0';
                    strcpy(aux2,"cp ");
                    strcat(aux2, destino);
                    strcat(aux2, "/");
                    strcat(aux2, s1);
                    strcat(aux2, " ");
                    strcat(aux2, fuente);
                    strcat(aux2, "/");
                    char *x = strchr(aux2, '\n');
                    *(aux2+((int)(x-aux2))) =' ';
                    //printf("instruccion: %s\n",aux2 );
                    system(aux2);
                    break;
                }
            }
        }
    }
    //fclose(t1);
    fclose(t2);
    system("rm tmp0");
    system("rm tmp1");
}

void creaTempVal(char *nameArch){
    //creamos un archivo temporal donde guardaremos información de los archivos
    //así sabremos cuáles fueron modificados
    system("sudo touch archList");
    FILE *archDates;
    //abrimos el archivo temporal para escribir
    archDates = fopen("archList", "r");
    if(archDates == NULL){
        perror("Error abriendo el archivo temporal");
        exit(1);
    }
    //escribimos el nombre seguido de su fecha de modifición
    system("ls destino/ > archList");
    char *name;
    char *inf = malloc(sizeof(char)*512);
    strcat(inf,"touch ");
    strcat(inf,nameArch);
    system(inf);
    *inf = '\0';
    strcat(inf, "sudo chmod +w ");
    strcat(inf, nameArch);
    free(inf);
    FILE *tempF = fopen(nameArch, "w");
    char *instruc;
    FILE *fp;
    char *t = malloc(sizeof(char)*512);
    while (feof(archDates) == 0){
        name = malloc(sizeof(char)*512);
        *name = '\0';
        fgets(name,100,archDates);
        instruc = malloc(sizeof(char)*512);
        *instruc ='\0';
        strcat(instruc,"stat -c \%y destino/");
        strcat(instruc, name);
        strcat(instruc, " > ");
        strcat(instruc, nameArch);
        fp = popen(instruc, "r");
        *instruc ='\0';
        if (fp == NULL) {
            printf("Failed to run command\n" );
            exit(1);
        }
        strcat(name, "");
        while (fgets(instruc, sizeof(instruc)-1, fp) != NULL) {
            strcat(name, instruc);
        }
        fputs(name, tempF);
        pclose(fp);
 	}
    system("rm archList");
    free(instruc);
    free(name);
    fclose(archDates);
    fclose(tempF);
}
