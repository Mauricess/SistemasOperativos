#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mount.h>

void montarSistArchivos(char *fuente, char *destino);
void copiarFuente(char *fuente, char *destino);
void copiarDestino(char *fuente, char *destino);

int main(int argc, char const *argv[]) {
  char *destino = "destino";
  char *fuente = "fuente";
 
  montarSistArchivos(fuente, destino);
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
    printf("Presiona <enter> para desmontar\n");
    getchar();
    umount(destino);
  }
  else{
    printf("Error al montar.\n");
  }

}
