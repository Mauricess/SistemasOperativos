#include <sys/types.h>
#include <unistd.h>
#include "stdio.h"
#include <stdlib.h>

//Se declaran las funciones principales
void *avg_func(FILE *file);
void *min_func(FILE *file);
void *max_func(FILE *file);
void *med_func(FILE *file);

//Se declaran funciones auxiliares
int getArrayFile(int n, int *array_ptr, FILE *file);
void ordena(int *array, int size);
void merge(int *array, int *izq, int *der, int izqSize, int derSize);

//Los valores de interes se declaran como variables globales
double avg;
int min;
int max;
double median;

/*
  En el caso de PROCESOS, se tiene que cada uno hace una copia del estado de las variables de proceso padre,
  de manera que si se altera una variable en un proceso nada tiene que ver con la misma variable en otro proceso,
  pues se trata de copias. De esta manera, la presente implementacion consta de 4 procesos hijos del proceso padre
  que es aquel que se ejecuta al iniciar el main. En cada hijo se ejecuta una de las funciones de interes; es decir,
  avg, min, max y median; y es en cada hijo en donde se imprime el valor, ya que como se dijo antes, el valor
  correspondiente fue actualizado en ese proceso unicamente.
  Seria interesante revisar lo que se puede hacer con comunicacion entre procesos, pero ese no es el objetivo de la practica.
*/
int main(int argc, char const *argv[]) {

  FILE* f1 = fopen ("ejercicio1.txt", "r");
  FILE* f2 = fopen ("ejercicio1.txt", "r");
  FILE* f3 = fopen ("ejercicio1.txt", "r");
  FILE* f4 = fopen ("ejercicio1.txt", "r");

  //Se definen los procesos hijos a crear.
  pid_t child_prom, child_min, child_max, child_med;

  //Se crea el primer hijo, encargado de la funcion PROMEDIO
  child_prom = fork();

  if (child_prom == 0) {
    avg_func(f1);
    printf("El promedio:  %g\n", avg);
    exit(EXIT_SUCCESS);
  } else {
    //Se crea el segundo hijo, encargado de la funcion MINIMO
    child_min = fork();

    if (child_min == 0) {
        min_func(f2);
        printf("El minimo:  %d\n", min);
        exit(EXIT_SUCCESS);
    } else {
      //Se crea el tercer hijo, encargado de la funcion MAXIMO
      child_max = fork();

      if (child_max == 0) {
        max_func(f3);
        printf("El maximo:  %d\n", max);
        exit(EXIT_SUCCESS);
      }else{
        //Se crea el cuarto hijo, encargado de la funcion MEDIANA
        child_med = fork();

        if (child_med == 0) {
          med_func(f4);
          printf("La mediana:  %g\n", median);
          exit(EXIT_SUCCESS);
        }else{
          /*Parent code*/
        }
      }
    }
  }

  return 0;
}

/*
Funcion encargada de calcular el promedio de numeros leidos de
un archivo cuyo apuntador recibe como parametro.
*/
void *avg_func(FILE *file){
  int sum = 0;
  int num,
      i = 0;
  while (fscanf(file, "%d", &num) == 1) {
    sum = sum + num;
    i++;
  }
  avg = (double)sum / i;
}

/*
Funcion encargada de calcular el minimo de numeros leidos de
un archivo cuyo apuntador recibe como parametro.
*/
void *min_func(FILE *file){
  int num;

  if (fscanf(file, "%d", &num) == 1) {
    min = num;
  }else{
    printf("Error");
  }

  while (fscanf(file, "%d", &num) == 1) {
    if (min > num) {
      min = num;
    }
  }
}

/*
Funcion encargada de calcular el maximo de numeros leidos de
un archivo cuyo apuntador recibe como parametro.
*/
void *max_func(FILE *file){
  int num;

  if (fscanf(file, "%d", &num) == 1) {
    max = num;
  }else{
    printf("Error");
  }

  while (fscanf(file, "%d", &num) == 1) {
    if (max < num) {
      max = num;
    }
  }
}

/*
Funcion encargada de calcular la mediana de numeros leidos de
un archivo cuyo apuntador recibe como parametro.
*/
void *med_func(FILE *file){
  //Tamano inicial del arreglo y numero de elementos en el.
  int n = 1, numElementos = 0;
  //Se inicializa el arreglo con tamano para un entero.
	int *array_ptr = malloc(n * sizeof(int));
  //Se realiza la insercion dinamica de elementos del archivo al arreglo.
	numElementos = getArrayFile(n, array_ptr, file);
  //Se ordena el arreglo con la implementacion de MergeSort de la Practica1.
  ordena(array_ptr, numElementos);
  //Se obtiene la mediana dependiendo de si el numero de elementos es par o impar.
  if(numElementos % 2 == 0) {
    //Si hay un numero impar de elementos, la mediana es la media de los dos elementos del medio.
    median = (*(array_ptr + numElementos/2) + *(array_ptr + (numElementos/2 -1))) / 2.0;
    } else {
      // La mediana es el elemento del medio.
      median = *(array_ptr + numElementos/2);
    }
    //Se libera la memoria ocupada por el arreglo.
    free(array_ptr);
}

/*
  Este metodo modifica el tamano de un arreglo dinamicamente al leer
  numeros de un archivo.
  Recibe el tamano del arreglo inicial, asi como el apuntador a dicho
  arreglo (basicamente serian un arreglo de tamano 1) y el apuntador al
  archivo del cual leera los numeros.
  Devuelve el tamano del arreglo.
*/
int getArrayFile(int n, int *array_ptr, FILE *file){

	int num;
	int numElementos = 0;

  while (fscanf(file, "%d", &num) == 1) {
    if (numElementos == n){
      n += 1;
      //Se hace espacio para el siguiente elemnto
      array_ptr = realloc(array_ptr, n * sizeof(int));
    }
    //Se guarda el numero actual en el arreglo
    array_ptr[numElementos++] = num;
  }

return numElementos;
}

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
