#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void install();

int main(){

  int os;
  int *aux;
  aux = &os;
  printf("Programa que configura y compila el kernel de linux 4-10.10\n");
  printf("Elige tu SO.\n");
  printf("1. Debian\n");
  printf("2. Fedora\n");
  scanf(" %d", aux);
  switch(os){
  case 1:
    printf("Instalando paquetes necesarios\n");
    system("sudo apt-get update");
    system("sudo apt-get install curl openssl");
    printf("Termino!\n");
    install();
    break;
  case 2:
    printf("Instalando paquetes necesarios\n");
    system("sudo dnf install curl openssl");
    printf("Termino!\n");
    install();
    break;
  default:
    printf("Opcion no valida. Terminando\n");
    break;
  }
  

  return 0;

}


void install(){
  int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
  char jmake[32];
  numCPU++;
  sprintf(jmake,"cd linux-4.10.10/ && make -j%d", numCPU);
  printf("Numero de procesadores: %d\n", numCPU-1);
  printf("Descargando la versión de kernel 4.10.10...\n");
  system("curl https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.10.10.tar.xz > linux-4.10.10.tar.xz");
  printf("Termino de descargar!\n");
  printf("Descomprimiendo...\n");
  system("tar xf linux-4.10.10.tar.xz");
  printf("Termino!\n");
  printf("Creando el archivo .config\n");
  system("cd linux-4.10.10/ && make olddefconfig");   // localmodconfig
  printf("Termino!\n");
  printf("Iniciando la configuracion...\n");
  system("cd linux-4.10.10/ && make menuconfig");
  printf("Termino!\n");
  printf("Compilando el kernel...\n");
  system(jmake);


}
