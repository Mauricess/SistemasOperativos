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
/*
#ifdef numProc
#define numProc 4
#endif
*/
int **matrizA;
int **matrizB;
int **matrizR;
int tam;

/*
 * Estructura para guardar el rango de cada thread
 */

struct v{
  int inferior;
  int superior; 
};

/*
 * Función que regresa un número random
 */
int randNumGen(){
  int random_value = rand()%10;
  return random_value;
}


/*
 * Funcion que llena una matriz
 *
 */

void llenaMatriz(int **matrix, int size){
  int i,j;
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      *(*(matrix + i) + j) = randNumGen();
    }
  }
}


/*
 * Funcion que imprime una matriz
 *
 */

void printMatrix(int **matrix, int n, int m){
  int i, j;
  for(i = 0; i < n; i++){
    for (j = 0; j < m; j++) {
      printf("%d\t", *(*(matrix + i) + j));
    }
    printf("\n");
  }
  printf("\n");
}


/*
 * Función que multipica dos matrices
 */

void *multiplicacionM(void *argc){

  struct v *data = argc;
  int i = 0;
  int j = 0;
  int k = 0;
  int res = 0;
  for(i = data->inferior; i < data->superior; i++){
    for(j = 0; j < tam; j++){
      res = 0;
      for (k = 0; k < tam; k++) {
        res += *(*(matrizA + i)+k) * *(*(matrizB + k) + j);
      } 
      *(*(matrizR + i)+j)= res;
    }
  }
  pthread_exit(0);
}

/*
 * Main del programa
 */

int main(int argc, char *argv[]){


  int i,j,rc,gran,proc;
  tam = 4;
  proc = 4;
  gran = tam / proc;
  pthread_t threads[proc];
  matrizA = malloc(sizeof(int *) * tam);
  matrizB = malloc(sizeof(int *) * tam);
  matrizR = malloc(sizeof(int *) * tam);
  for(i = 0; i < tam; i++){
    *(matrizA + i) = malloc(sizeof(int) * tam);
    *(matrizB + i) = malloc(sizeof(int) * tam);
    *(matrizR + i) = malloc(sizeof(int) * tam);
  }

  llenaMatriz(matrizA, tam);
  llenaMatriz(matrizB, tam);

  printMatrix(matrizA, tam, tam);
  printMatrix(matrizB, tam, tam);
  
  

  for (i = 0; i < proc; i++) {
    struct v *data = (struct v *) malloc(sizeof(struct v));
    data->inferior = i * gran;
    data->superior = i * gran + gran;
    rc = pthread_create(&threads[i], NULL, multiplicacionM, data);
    if (rc){
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  for(i = 0; i < proc; i++){
    pthread_join(threads[i], NULL);
  }
  
  printMatrix(matrizR, tam, tam);
  
  free(matrizA);
  free(matrizB);
  free(matrizR);


  pthread_exit(0);

  return 0;

}
