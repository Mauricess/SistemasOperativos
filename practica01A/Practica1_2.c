#include<stdio.h>
#include <stdlib.h>

/**
* Funcion para crear el triangulo de pascal en la parte inferior izquierda
* de la matriz que recibe como argumento (en caso de que quepa).
*/
void pascal(int renglon, int **matrix){
  int i, j;
  //Inicializamos en 0 el triangulo sup. derecho.
  for(i = 0; i < renglon; i++){
    for (j = (renglon - 1); j > i; j--) {
      *(*(matrix + i) + j) = 0;
    }
  }

  **matrix = 1;
  //Calculamos el triangulo de pascal, para el triangulo inf.
  //de la matriz.
  for(i = 1; i < renglon; i++){
    for(j = 0; j < renglon; j++) {
      *(*(matrix + i) + j) = *(*(matrix + (i - 1)) + (j - 1)) + *(*(matrix + (i - 1)) + j);
      //printf("%d \t", *(*(matrix + i) + j));
    }
    //printf("\n");
  }
}

/**
* Funcion que llena el arreglo con el renglon del triangulo
* de pascal especificado.
*/
void renglonPascal(int renglon, int *array){
  int i;
  int n = renglon - 1;
  *array = 1;
  for (i = 0; i < n; i++) {
    *(array + i + 1) = *(array + i) * (n - i) / (i + 1);
  }
}

/**
* Funcion encargada de devolver la entrada de la matriz de
* Pascal dadas sus coordenadas en la matriz.
*/
int entradaPascal(int renglon, int columna){
  int resultado;
  int *array = malloc(sizeof(int) * renglon);
  renglonPascal(renglon, array);

  resultado = *(array + columna - 1);
  free(array);
  return resultado;
}

//Funcion que imprime un arreglo.
void printArray(int *array, int len){
  int i;
  for (i = 0; i < len; i++) {
    printf("%d\t", *(array + i));
  }
  printf("\n");
}

//Funcion que imprime una matriz.
void printMatrix(int **matrix, int n, int m){
  int i, j;
  for(i = 0; i < n; i++){
    for (j = 0; j < m; j++) {
      printf("%d\t", *(*(matrix + i) + j));
    }
    printf("\n");
  }
}

int main(int argc, char const *argv[]) {
  //Se inicializan las variables.
  int size, i;
  int **matrix = NULL,
      *array = NULL;

  printf("###########################################################\n");
  printf("# Programa encargado de operar con el triangulo de Pascal #\n");
  printf("###########################################################\n\n");
  //Se pide al usuario que ingrese un tamano para el arreglo.
  printf("1. Imprimir triangulo de Pascal.\n");
  printf("# Introduce el tamano de la matriz cuadrada (con un numero basta): ");

  if (scanf("%d", &size) != 1){
    printf("Favor de introducir un numero entero positivo.\n");
  }

  //Construimos una matriz, con apuntador de apuntadores.
  matrix = malloc(sizeof(int *) * size);

  for(i = 0; i < size; i++){
    //En cada una de las entradas hay que inicializar.
    *(matrix + i) = malloc(sizeof(int) * size);
  }

  pascal(size, matrix);
  printMatrix(matrix, size, size);
  free(matrix);
  matrix = NULL;

  //Se pide al usuario que ingrese un tamano para el arreglo.
  printf("\n2. Imprimir renglon n-esimo del triangulo de Pascal.\n");
  printf("# Introduce el numero de renglon del triangulo de Pascal que deseas: ");

  if (scanf("%d", &size) != 1){
    printf("Favor de introducir un numero entero positivo.\n");
  }

  //Construimos el arreglo.
  array = malloc(sizeof(int) * size);

  renglonPascal(size, array);
  printArray(array, size);
  free(array);
  array = NULL;

  //Se pide al usuario que ingrese un par (renglon, columna).
  printf("\n3. Obtener elemento en posicion (renglon, columna).\n");
  printf("# Introduce el renglon: ");
  if (scanf("%d", &size) != 1){
    printf("Favor de introducir un numero entero positivo.\n");
  }
  printf("# Introduce la columna: ");
  if (scanf("%d", &i) != 1){
    printf("Favor de introducir un numero entero positivo.\n");
  }

  printf("Valor en la entrada (%d, %d): %d\n", size, i, entradaPascal(size, i));

  return 0;
}
