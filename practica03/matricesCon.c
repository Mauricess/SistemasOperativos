#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#ifdef numProc
#define numProc = 4
#endif

int **matrizA;
int **matrizB;
int **matrizR;

int randNumGen(){
  int random_value = rand()%100;
  return random_value;
}


void *multiplicacionM(void *argc){
  //renglon columna a resiver
  int reng = (int)*(argc);
  //operzciones
  
  
  

}


int main(int argc, char *argv[]){

  
  int tam = 8;
  int i,j;
  **matrizA = malloc(sizeof(int *) * tam);
  **matrizB = malloc(sizeof(int *) * tam);
  pthread_t threads[numProc];

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



  free(matrizA);
  free(matrizB);
  

}
