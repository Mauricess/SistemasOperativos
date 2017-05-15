#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Se declaran las funciones principales
void *avg_func(void *ptr);
void *min_func(void *ptr);
void *max_func(void *ptr);
void *med_func(void *ptr);

//Se declaran funciones auxiliares
int getArrayFile(int n, int *array_ptr, FILE *file);
void ordena(int *array, int size);
void merge(int *array, int *izq, int *der, int izqSize, int derSize);

//Los valores de interes se declaran como variables globales
double avg;
int min;
int max;
double median;

int main(int argc, char const *argv[]) {
  int t1, t2, t3, t4;
/*
  Se declaran apuntadores distintos para iterar sobre el archivo sin
  que se mezcle el recorrido que hacen los threads.
  Para un arreglo esto no hace falta pues se cuenta con indices,
  Sin embargo, como en el archivo no sabemos cuantos numeros hay,
  hay que recorrerlo a ciegas.
  */
  FILE* f1 = fopen ("ejercicio1.txt", "r");
  FILE* f2 = fopen ("ejercicio1.txt", "r");
  FILE* f3 = fopen ("ejercicio1.txt", "r");
  FILE* f4 = fopen ("ejercicio1.txt", "r");

  //Se declaran los threads, cada uno por operacion a realiza.
  pthread_t thread1, thread2, thread3, thread4;

  //Se crean threads independientes, donde cada uno realizara una operacion espcifica.
  t1 = pthread_create(&thread1, NULL, (void *) avg_func, (void *) f1);
  //En caso de error (el valor regresado por pthread_create es distinto de 0), se
  //imprime y se sale del programa.
  if(t1){
      fprintf(stderr,"Error - codigo de retorno de pthread_create(): %d\n", t1);
      exit(EXIT_FAILURE);
  }

  t2 = pthread_create(&thread2, NULL, (void *) min_func, (void *) f2);
  if(t2){
      fprintf(stderr,"Error - codigo de retorno de pthread_create(): %d\n",t2);
      exit(EXIT_FAILURE);
  }

  t3 = pthread_create(&thread3, NULL, (void *) max_func, (void *) f3);
  if(t2){
      fprintf(stderr,"Error - codigo de retorno de pthread_create(): %d\n",t3);
      exit(EXIT_FAILURE);
  }

  t4 = pthread_create(&thread4, NULL, (void *) med_func, (void *) f4);
  if(t2){
      fprintf(stderr,"Error - codigo de retorno de pthread_create(): %d\n",t4);
      exit(EXIT_FAILURE);
  }

  //Se espera a que los threads terminen de ejecutarse antes de continuar
  //con el main.
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);

  //Se imprimen los valores deseados.
  printf("El promedio:  %g\n", avg);
  printf("El minimo:  %d\n", min);
  printf("El maximo:  %d\n", max);
  printf("La mediana:  %g\n", median);

  return 0;
}

/*
Funcion encargada de calcular el promedio de numeros leidos de
un archivo cuyo apuntador recibe como parametro.
*/
void *avg_func(void *ptr){
  FILE* file;
  file = (FILE *) ptr;

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
void *min_func(void *ptr){

  FILE* file;
  file = (FILE *) ptr;

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
void *max_func(void *ptr){

  FILE* file;
  file = (FILE *) ptr;

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
void *med_func(void *ptr){

  FILE* file;
  file = (FILE *) ptr;

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
