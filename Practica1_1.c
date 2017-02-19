#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFSIZE
#define BUFFSIZE 1024
#endif

/**
 * Funcion que implementa funcionalidad basica de printf.
 * Toma dos cadenas de caracteres donde, por cada %s en la
 * primer cadena, se sustituye la segunda.
 */
void mi_printf(char *str1, char *str2){
  //Se inicializan variables.
  int i, j;
  //Se usa la biblioteca string.h para utilizar la funcion strlen que nos da la longitud de la cadena.
  int lenStr1 = strlen(str1);
  int lenStr2 = strlen(str2);
  //Se reserva memoria para la cadena resultado de la sustitucion.
  char *str3 = malloc(sizeof(char) * 2 * BUFFSIZE);
  char *head = str3;

  //Se hace la sustitucion.
  for (i = 0; i < lenStr1; i++) {
    if(*str1 == '%' && *(str1+1) == 's'){
      for(j = 0; j < lenStr2; j++){
        //Se van "insertando" los caracteres de str2 en la cadena resultado.
        *(str3++) = *(str2++);
      }
      //Se saltan las dos posiciones ocupadas por los caracteres '%' y 's'.
      str1 = str1 + 2;
      //Se incrementa el contador en 1, contemplando que para la sig. iteracion se hara otro +1.
      i++;
    }
    //Se van "insertando" los caracteres de str1 en la cadena resultado.
    *(str3++) = *(str1++);
  }
  //Se imprime la cadena resultado mediante la funcion "write()".
  //STDOUT_FILENO es un descriptor de archivo del sistema LINUX, el cual se
  //usa para hacer una llamada al sistema.
  write(STDOUT_FILENO, head, strlen(head));

  //Se libera la memoria reservada.
  free(head);
}

int main(int argc, char const *argv[]) {
  //Se inicializan variables.
  char *str1 = NULL,
        *str2 = NULL,
        *headStr1 = NULL,
        *headStr2 = NULL;

  //Se crean los arreglos de caracteres que representan cadenas de texto.
  //Se impone un maximo de 1024 caracteres por cadena.
  str1 = malloc(sizeof(char) * BUFFSIZE);
  str2 = malloc(sizeof(char) * BUFFSIZE);
  headStr1 = str1;
  headStr2 = str2;

  //Se definen las cadenas a imprimir.
  str1 = "Mi numero de cuenta es %s\n";
  str2 = "412005220";

  //Se hace la llamada a nuestra funcion print.
  mi_printf(str1, str2);

  //Se liberan los bloques de memoria antes alocados.
  free(headStr1);
  free(headStr2);

  return 0;
}
