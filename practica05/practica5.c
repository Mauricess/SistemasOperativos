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

int main(int argc, char const *argv[]) {

  FILE *f;
  char *destino = malloc(sizeof(char) * 256);
  char *fuente = malloc(sizeof(char) * 256);

  f = fopen(argv[1], "r");
  
  fscanf(f, "%s", fuente);
  fscanf(f, "%s", destino);

  printf("%s\n", fuente);
  printf("%s\n", destino);
 
  montarSistArchivos(fuente, destino);
  copiarFuente(fuente, destino);
  printf("Presiona <enter> cuando hayas terminado de trabajar.");
  getchar();
  copiarDestino(fuente, destino);
  umount(destino);
  return 0;
}

void montarSistArchivos(char *fuente, char *destino){  
  struct stat st = {0};  
  if (stat(destino, &st) == -1) {
    mkdir(destino, 0700);
    printf("Carpeta destino creada con exito\n");
  }
  
  int res = mount(fuente, destino, "tmpfs", 0, "");

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
  char fil[64];
  char instr[64];
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
        sprintf(instr,"cp -r %s %s",fil,destino);
        system(instr);
      }else{
        sprintf(fil,"%s/%s",fuente,drnt->d_name);
        sprintf(instr,"cp %s %s",fil,destino);
        system(instr);
      }
    }
    closedir(f);
  }else{
    printf("No se puede abrir el directorio %s\n", fuente);
  } 
}
