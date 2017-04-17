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
  file = fopen("/proc/modules", "r");
  if(file_exists("modules.txt")){
    res = fopen("modules.txt", "r");
    while(fgets(line, sizeof(line), file)){
      flag = 0;
      mod = strtok(line, " ");
      rewind(res);
      while(fgets(line2, sizeof(line2), res)){
        l = strtok(line2, "\n");
        //printf("%s : %s\n", mod, l);
        if(strcmp(mod, l) == 0){
          //printf("El modulo \t%s\t ya esta en el archivo\n", mod);
          flag = 1;
          break;
        }
      }
      if(flag == 0){
        tmp = fopen("tmp.txt", "a");
        fprintf(tmp, "%s\n", mod);
        fclose(tmp);
      }
    }
    fclose(res);
    res = fopen("modules.txt", "a");
    if(tmp = fopen("tmp.txt", "r")){
      while(fgets(line, sizeof(line), tmp)){
        fprintf(res, "%s", line);
        printf("Se agrego el modulo: %s", line);
      }
    fclose(tmp);
    fclose(res);
    remove("tmp.txt");
    }
    else{
      printf("No se agregaron modulos.\n");
    }
  }
  else{
  res = fopen("modules.txt", "a");
  while(fgets(line, sizeof(line), file)){
    mod = strtok(line, " ");
    fprintf(res, "%s\n", mod);
    printf("Se agrego el modulo: %s", mod);
  }
  fclose(res);
  }
  fclose(file);
sleep(segundos);
}
  exit(0);
}
