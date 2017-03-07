#include <stdio.h>
#include <stdlib.h>

/**
 * Funcion que imprime en pantalla un arreglo.
 * Recibe como argumentos el arreglo y el tamaño
 * del arreglo.
 */

void printArray(int *array, int lon){
  
  for (int i = 0; i < lon; i++) {
    printf("%d|", *(array + i));
  }
  printf("\n");
}

/**
 * Función que hace Merge de las listas left y right en merged
 * leftN y rightN son el número de elementos de cada arreglo 
 */

void merge(int *merged, int *left, int leftN, int *right, int rightN){

  int i,j,k;
  i = 0; j = 0; k = 0;

  while(i < leftN && j < rightN){
    if(left[i] < right[j]){
      merged[k++] = left[i++];
    }else{
      merged[k++] = right[j++];
    }
  }
  
  while(i < leftN){
    merged[k++] = left[i++];
  }

  while(j < rightN){
    merged[k++] = right[j++];
  }
}

/**
 * Función que genera una lista de números aleatorios
 * y los arregla
 */

void ordena(int *merged, int n){
  int i, mid;
  int *left, *right;
  int *headL, *headR, *headM;
  headM = merged;
  
  if(n < 2) return;

  mid = n/2;

  left = malloc(mid * sizeof(int));
  right = malloc((n - mid) * sizeof(int));
  headL = left;
  headR = right;

  for(i = 0; i < mid; i++){
    *(left++) = *(merged++);
  }

  for(i = mid; i < n; i++){
    *(right++) = *(merged++);
  }

  ordena(headL, mid);
  ordena(headR, n - mid);

  merge(headM,headL,mid,headR,(n-mid));

  free(headL);
  free(headR);

}

int main (int argc, char const * argv[]){


  int A[] = {2,4,8,12,54,6,24,35,45,52};
  printArray(A,10);
  ordena(A,10);
  printArray(A,10);
  return 0;
}
