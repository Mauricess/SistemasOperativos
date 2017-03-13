#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "List.h"

int main (void){
  int i;
  struct list *list;
  srand(time(NULL));
  printf("Se crea una lista ligada mediante \"createList()\"\n");
  list = createList();
  printf("Se insertan 5 elementos aleatorios al final mediante \"addToEnd()\"\n");
  for (i = 0; i < 5; i++) {
    addToEnd(rand() % 100, list);
  }
  printf("Se imprime la lista.\n");
  print(list);
  printf("Se agrega el valor 3 a la lista en la posicion 0; es decir, la cabeza, mediante \"add()\"\n");
  add(3, list, 0);
  print(list);
  printf("Ahora se elimina el valor en la posicion 3 mediante \"delete()\"\n");
  delete(list, 3);
  print(list);
  printf("Tamano de la lista: %d\n", size(list));
  printf("Es vacia?: %d\n", isEmpty(list));

  return 0;
}
