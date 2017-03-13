#include <stdio.h>
#include <stdlib.h>

#define Error(Str) FatalError(Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

typedef int bool;
#define true 1
#define false 0


// Estructura de lista ligada
struct list{
  struct node *head;
};

//Estructura de nodo para usarse en la lista ligada
struct node{
  int val;
  struct node *next;
};

//Crea una lista vacia
struct list *createList(void){
  struct list *l = (struct list*)malloc(sizeof (struct list));
  l -> head = NULL;
  return l;
}

// Regresa el tamaño de la lista
int size(struct list *list){
  int size = 0;
  if (list->head == NULL){
    return size;
  }
  struct node *e;
  for (e = list-> head; e != NULL; e = e-> next){
	   size = size + 1;
   }
  return size;
}

// Inserta el elemento al final de la lista
void addToEnd(int value, struct list *list){
  struct node *e = malloc(sizeof(struct node));
  e -> val = value;       //Se asigna d al miembro "val" de la estructura "node"
  e -> next = NULL;       //Se apunta a null pues se trata del ultimo elemento de la lista

  if(list->head == NULL){
        list->head = e;
  }
  else{
    struct node *ptr = list->head;
    //Se recorre la lista hasta llegar al final
    while(true){
      if(ptr->next == NULL){
        ptr->next = e;
        break;
      }
      ptr = ptr->next;
    }
  }
}

// Inserta el elmento en la posición deseada
void add(int value, struct list *list, int position){
  if ((size(list) -1) < position) {
    addToEnd(value, list);
    return;
  }
  int i;
  struct node *e = malloc(sizeof(struct node));
  e -> val = value;
  struct node *ptr = list->head;
  struct node *tmp = NULL;

  if (position == 0) {
    list -> head = e;
    e -> next = ptr;
  }
  else{
    for (i = 0; i < position; i++){
      tmp = ptr;
  	  ptr = ptr -> next;
    }
    tmp -> next = e;
    e -> next = ptr;
  }
}

// Elimina el elemento de la posición selecionada
bool delete(struct list *list, int position){
  if ((size(list) -1) < position || position < 0) {
    return false;
  }
  int i;
  struct node *del = list->head;
  struct node *tmp = NULL;

  if (position == 0) {
    list -> head = del -> next;
  }
  else{
    for (i = 0; i < position; i++){
      tmp = del;
  	  del = del -> next;
    }
    tmp -> next = del -> next;
  }
  free(del);
  del = NULL;
  return true;
}

// Decide si la lista esta vacia
bool isEmpty(struct list *list){
  if (list->head == NULL){
    return true;
  }
  return false;
}

//Imprime todos los valores de la lista
void print(struct list *list){
  if (list->head == NULL){
    printf("Lista vacia\n");
    return;
  }
  struct node *e;
  for (e = list-> head; e != NULL; e = e-> next){
	   printf ("%d -> ", e-> val);
  }
  printf("NULL\n");
}
