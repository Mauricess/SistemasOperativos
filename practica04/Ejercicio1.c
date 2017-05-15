#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int file_exists(const char * filename) {
  FILE *file;
  if (file = fopen(filename, "r")) {
      fclose(file);
      return 1;
  }
  return 0;
}

int main(){
  char line[4096];
  char line2[4096];
  char *mod;
  char *l;
  FILE *file;
  FILE *res;
  FILE *tmp;
  int flag;
  int segundos = 10;
  
  while(1){
    file = fopen("/proc/modules", "r"); // Cargamos el archivo /proc/modules
    if(file_exists("modules.txt")){ // Checamos si hay un archivo con los modulos
      res = fopen("modules.txt", "r"); // Abrimos el archivo
      
      while(fgets(line, sizeof(line), file)){ // iteramos sobre las lineas
        flag = 0; // Ponemos la bandera en 0
        mod = strtok(line, " "); // Obtenemos los token de la cadena hasta un espacio
        rewind(res); // Nos regresamos al inicio de apuntador del flujo de res
        while(fgets(line2, sizeof(line2), res)){ // Iteramos sobre las lineas del archivo
          l = strtok(line2, "\n"); // Obtenemos los tokens de la cadena hasta un salto de linea
          //printf("%s : %s\n", mod, l);
          if(strcmp(mod, l) == 0){ // Revisamos si son iguales
          //printf("El modulo \t%s\t ya esta en el archivo\n", mod);
            flag = 1; // Cambiamos la bandera a 1
            break; // Termina este ciclo
          }
        }
        if(flag == 0){ // Revisamos la bandera
          tmp = fopen("tmp.txt", "a"); // Abrimos el archivo tmp
          fprintf(tmp, "%s\n", mod); // Escribimos el modulo
          fclose(tmp); // Cerramos el archivo
        }
      }
      fclose(res); // Cerramos el archivo 
      res = fopen("modules.txt", "a"); // Abrimos el archivo
      if(tmp = fopen("tmp.txt", "r")){ // Abrimo nuestro archivo temporal
        while(fgets(line, sizeof(line), tmp)){ // Iteramos sobre las lineas de tmp
          fprintf(res, "%s", line); // Guardamos lo que esta en tmp en res
          printf("Se agrego el modulo: %s", line); // Imprimimos el modulo que se agrego
        }
        fclose(tmp); // Cerramos tmp
        fclose(res); // Cerramos res
        remove("tmp.txt"); // Eliminamos el archivo tmp
      }else{
        printf("No se agregaron modulos.\n"); // No se agregaron modulos
      }
    }else{
      res = fopen("modules.txt", "a"); // Abrimos el archivo modules
      while(fgets(line, sizeof(line), file)){ // Iteramos sobre las lineas de /proc/modules
        mod = strtok(line, " "); // Tokenizamos hasta un espacio
        fprintf(res, "%s\n", mod); // Guadamos el modulo en el archivo modules
        printf("Se agrego el modulo: %s", mod); // Indicamos el modulo que se agrego
      }
      fclose(res); // Cerramos res
    }
    fclose(file); // Cerramos el archivo de modulos
    sleep(segundos); // Esperamos 10 segundos
  }
  exit(0); // Terminamos
}
