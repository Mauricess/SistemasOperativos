#include<stdlib.h>
#include<stdio.h>
#include<time.h>

//Funcion encargada del "merge"; es decir, la union de dos arreglos ordenados.
void merge(int *array, int *izq, int *der, int izqSize, int derSize){
  int i = 0,
      j = 0;

//Mientras los tamanos de ambos arreglos (izq y der) sean iguales, vamos agregando en orden.
  while(i < izqSize && j < derSize){
    if(*izq < *der){
      *(array++) = *(izq++);
      i++;
    }else{
      *(array++) = *(der++);
      j++;
    }
  }
//Se vacian los que quedaron en el arreglo izquierdo.
  while(i < izqSize){
    *(array++) = *(izq++);
    i++;
  }
//Se vacian los que quedaron en el arreglo derecho.
  while(j < derSize){
    *(array++) = *(der++);
    j++;
  }
}

//Funcion recursiva para ordenar implementando el algoritmo de MergeSort.
void ordena(int *array, int size){
  int m = 0,
      i = 0,
      *izq = NULL,
      *headIzq = NULL,
      *der = NULL,
      *headDer = NULL,
      *headArray = array;

//Caso base.
  if (size < 2) {
    return;
  }

  m = size/2;

//Se definen los arreglos que albergaran las mitades izquierda y derecha.
  izq = malloc(m * sizeof(int));
  der = malloc((size - m) * sizeof(int));
  headIzq = izq;
  headDer = der;

//Se llena la mitad izquierda.
  for (i = 0; i < m; i++) {
    *(izq++) = *(array++);
  }

//Se llena la mitad derecha.
  for (i = m; i < size; i++) {
    *(der++) = *(array++);
  }

  //Se ordena el arreglo izquierdo.
  ordena(headIzq, m);
  //Se ordena el arreglo derecho.
  ordena(headDer, size - m);
  //Se hace la union de los arreglos ordenados.
  merge(headArray, headIzq, headDer, m, size - m);
  //Se libera la memoria alocada a los subarreglos.
  free(headIzq);
  free(headDer);
}

//Funcion que imprime un arreglo.
void printArray(int *array, int len){
  int i;
  for (i = 0; i < len; i++) {
    printf("%d\t", *(array + i));
  }
  printf("\n");
}

int main(int argc, char const *argv[]) {
//Se inicializan las variables.
  int size, i;
  int *array = NULL;
  int *headArray = NULL;
  srand(time(NULL));

  printf("#########################################################################################\n");
  printf("# Programa encargado de ordenar un arreglo generado aleatoriamente, mediante MergeSort. #\n");
  printf("#########################################################################################\n\n");
  //Se pide al usuario que ingrese un tamano para el arreglo.
  printf("Introduce el tamano del arreglo a ordenar: ");

  if (scanf("%d", &size) != 1){
    printf("Favor de introducir un numero entero positivo.\n");
  }
  array = malloc(sizeof(int) * size);
  headArray = array;

  //Se llena el arreglo de enteros aleatorios entre 0 y 1000.
  for (i = 0; i < size; i++) {
    *array = rand() % 10000;
    array++;
  }

  printf("\nArreglo generado aleatoriamente: \n");
  printArray(headArray, size);
  printf("\n");
  ordena(headArray, size);
  printf("Arreglo ordenado: \n");
  printArray(headArray, size);
  //Se libera el bloque de memoria del arreglo.
  free(headArray);
  return 0;
}
