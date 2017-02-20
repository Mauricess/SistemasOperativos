#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFSIZE
#define BUFFSIZE 1024
#endif

/**
 * Funcion que imprime en pantalla una cadena.
 * Recibe como argumentos dos cadenas donde la segunda sera
 * sustituida en la primera en los indicadores %s
 */
void mi_printf(char *s0, char *s1){


  int lstr0, lstr1, i, j;
  lstr0 = strlen(s0);
  lstr1 = strlen(s1);
  char *s2 = malloc(sizeof(char) * 2 * BUFFSIZE);
  char *head = s2;

  for(i = 0; i < lstr0; i++){
    if(*s0 == '%' && *(s0+1) == 's'){
      for(j = 0; j < lstr1; j++){
        *(s2) = *(s1);
        s1++;s2++;
      }
      s0 = s0+2;
      i++;
    }
    *(s2) = *(s0);
    s0++;s2++;
  }

  write(STDOUT_FILENO, head, strlen(head));

  free(head);
}


int main(int argc, char const *argv[]) {

  char *s0 = NULL, *s1 = NULL, *h0 = NULL, *h1 = NULL;
  s0 = malloc(sizeof(char) * BUFFSIZE);
  s1 = malloc(sizeof(char) * BUFFSIZE);
  h0 = s0;
  h1 = s1;

  s0 = "Mi número de cuenta es %s\n";
  s1 = "309049795";

  mi_printf(s0,s1);

  free(h0);
  free(h1);

  return 0;

}
