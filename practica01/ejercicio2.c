#include <stdio.h>
#include <stdlib.h>

/**
 * Funcion que imprime en pantalla una matrix.
 * Recibe como argumentos la matriz a imprimir
 * y el número de renglones y columnas
 */

void printMatrix(int **matrix, int m, int n){
  int i,j;
  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){
      printf("%d|",*(*(matrix+i)+j));
    }
    printf("\n");
  }
}


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
 * Funcion que genera un triangulo de Pascal.
 * Recibe como argumentos el número de renglones
 * que se desea generar y la matriz donde se guardara.
 */

void pascal(int renglon, int **matrix){
  int i, j;
  **matrix = 1;
  for (i = 1; i < renglon; i++){
    for (j = 0; j < renglon; j++){
      *(*(matrix + i) + j) = *(*(matrix + (i-1)) + (j-1)) + *(*(matrix + (i-1)) + j);
    }
  }
}

/**
 * Funcion que genera un renglon del triangulo de Pascal.
 * Recibe como argumentos el número del renglon que se desea
 * generar y el arreglo donde se guardara.
 */

void renglonPascal(int renglon, int *array){

  *array = 1;
  for(int i = 0; i < renglon; i++){
    *(array + i + 1) = *(array + i) * (renglon - 1 - i) / (i + 1);
  }

}

/**
 * Funcion que obtiene un elemento del triangulo de Pascal.
 * Recibe como argumentos las coordenadas del 
 * elemento que se desea obtener.
 */

int entradaPascal(int renglon, int columna){

  int res;
  int *array = malloc(sizeof(int) * renglon);
  renglonPascal(renglon,array);
  res = *(array+columna-1);
  //free(array);
  return res;
}

int main(int argc, char const *argv()){

  int tam, ren, x, y, res = 0;
  int *a0, *a1, *a2, *a3, *a4;
  a0 = &tam;
  a1 = &ren;
  a2 = &x;
  a3 = &y;
  a4 = &res;
  printf("Ingresa el tamaño de la matriz:\n");
  scanf(" %d", a0);
  int **matrix = malloc(sizeof(int *) * tam);
  int *array = malloc(sizeof(int) * tam);

  for(int j = 0; j < tam; j++){
    *(matrix + j) =  malloc(sizeof(int) * tam);
      for (int m = 0; m < tam; m++){
        *(*(matrix + j) + m) = 0;
      }
  }

  pascal(tam,matrix);
  printMatrix(matrix,tam,tam);
  free(matrix);
  //matrix = NULL;

  printf("Ingresa el renglon que deseas obtener:\n");
  scanf(" %d", a1);
  renglonPascal(ren,array);
  printArray(array,ren);


  printf("Ingresa las coordenas del elemento que deseas obtener.\n");
  printf("Ingresa la primera:\n");
  scanf(" %d", a2);
  printf("Ingresa la segunda:\n");
  scanf(" %d", a3);
  res = entradaPascal(x,y);
  printf("El elemnto es %d\n", res);
  
  return 0;
}
