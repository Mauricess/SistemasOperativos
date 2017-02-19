#include <stdio.h>
#include <stdlib.h>

int tam = 0;
int *aux;

void printMatrix(int **matrix, int m, int n){
  int i,j;
  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){
      printf("%d|",*(*(matrix+i)+j));
    }
    printf("\n");
  }
}


void pascal(int renglon, int **matrix){
  int i, j;
  for (i = 0; i < renglon; i++){
    for (j = 0; j < renglon; j++){
      if (i == 0 && j == 0){
        *(*(matrix + i) + j) = 1;
      } else if (i != 0 && j == 0){
        *(*(matrix + i) + j) = *(*(matrix + (i-1)) + j);
      } else if (i != 0 && j != 0){
        *(*(matrix + i) + j) = *(*(matrix + (i-1)) + (j-1)) + *(*(matrix + (i-1)) + j);
      }
    }
  }
}

void renglonPascal(int renglon, int **matrix){

  for(int i = 0; i < tam; i++){
    printf("%d|", *(*(matrix+(renglon-1))+i));
  }
  printf("\n");

}

int main(int argc, char const *argv()){


  aux = &tam;
  printf("Ingresa el tamaño de la matriz:\n");
  scanf(" %d", aux);
  int **matrix = malloc(sizeof(int *) * tam);

  for(int j = 0; j < tam; j++){
    *(matrix + j) =  malloc(sizeof(int) * tam);
      for (int m = 0; m < tam; m++){
        *(*(matrix + j) + m) = 0;
      }
  }

  pascal(tam,matrix);
  printMatrix(matrix,tam,tam);
  
  renglonPascal(4,matrix);


  
  free(matrix);
  return 0;
}
