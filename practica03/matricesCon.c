/*
 * Ejercicio del día 6 de Marzo
 * Equipo confirmado por:
 * Andrés López Martínez.
 * Mauricio Esquivel Reyes.
 * Ulises Manuel Cárdenas.
 * 
 * Programa que multiplica dos matrices de forma concurrente.
 * 
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Constantes
 */

#ifdef numProc
#define numProc = 4
#endif

int **matrizA;
int **matrizB;
int **matrizR;
int n;

/*
 * Estructura para guardar el rango de cada thread
 */

struct v{
  int iR;
  int jR;
  int iC;
  int jC;

}

/*
 * Función que regresa un número random
 */

int randNumGen(){
  int random_value = rand()%100;
  return random_value;
}

/*
 * Función que multipica dos matrices
 */


void *multiplicacionM(void *argc){
  // Renglon y columna a revisar
  int reng = (int)*(argc);
  int  col = (int)*(argc +1);

  int i = 0;
  int res = 0;
  for(i = 0; i < n; i++){
    res += *(*(matrizA + reng)+i) * *(*(matrizB + i) + col);
  }
  *(*(matrizR + reng)+col)= res;
}

/*
 * Main del programa
 */

int main(int argc, char *argv[]){

  
  int tam = 8;
  n = tam;
  int i,j,rc,gran;
  int *array;
  array = malloc(sizeof(int) * 2);
  matrizA = malloc(sizeof(int *) * tam);
  matrizB = malloc(sizeof(int *) * tam);
  pthread_t threads[numProc];
  gran = tam * tam / numProc;

  for(i = 0; i < tam; i++){
    *(matrizA + i) = malloc(sizeof(int) * tam);
    *(matrizB + i) = malloc(sizeof(int) * tam);
  }

  
  for(i = 0; i < tam; i++){
    for(j = 0; j < tam; j++){
      *(*matrizA + i) + j) = randNumGen();
      *(*matrizB + i) + j) = randNumGen();
    }
  }

for (i = 0; i < numProc; i++) {
  for()
  rc = pthread_create(&threads[i], NULL, multiplicacionM, (void *) )
    }


  free(matrizA);
  free(matrizB);

}
