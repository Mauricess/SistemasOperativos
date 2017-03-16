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

// Inserta el elemento al final de la listas
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

/************************Punto Extra: order & insert_ordered*******************/


//devuelve un arreglo con dos sublistas: izq y der de la lista dada
struct list **parte(struct list *lst){
  struct list **arrLst = malloc(sizeof(struct list*)* 2);
  int i;
  struct list *left = createList();
  struct list *right = createList();
  struct node *e;
  int tam = size(lst);
  for(i = 0; i < tam; i++){//Crea dos sublistas
    if(i < tam/2){
      e = lst->head;
      addToEnd(e->val, left); //se añade el elemento en la pos 0
      delete(lst, 0);//se borra el elemento de la lista
    }else{
      e = lst->head;
      addToEnd(e->val, right);
      delete(lst, 0);
    }
  }
  free(lst);
    //se asignan las listas al arreglo
    *(arrLst) = left;
    *(arrLst+1) = right;
    return arrLst;

}

struct list* mezclaAux(struct list *l1, struct list *l2){
    struct list *ordered = createList();
    while(l1->head != NULL && l2->head != NULL){
        if(l1->head->val <= l2->head->val){
            addToEnd(l1->head->val, ordered);
            delete(l1, 0);
        }else{
          addToEnd(l2->head->val, ordered);
          delete(l2, 0);
        }
    }
    if(l1->head == NULL){
        if (l2->head == NULL){
            return ordered;
        }else{
          while (l2->head != NULL) {
            addToEnd(l2->head->val, ordered);
            delete(l2, 0);
          }
          return ordered;
        }
    }else{
      while (l1->head != NULL) {
        addToEnd(l1->head->val, ordered);
        delete(l1, 0);
      }
      free(l1);
      free(l2);
      return ordered;
    }
}

//función que dada una lista, la devuelve ordenada
//La complejidad en tiempo del algoritmo es O(n*log(n))
struct list* order(struct list *lst){
  if(size(lst) == 1){
    return lst;
  }else{
    struct list **arr = parte(lst);
    return mezclaAux(order(arr[0]), order(arr[1]));
  }
}

//La complejidad es O(n), inserta aunque la lista no esté ordenada
//Es preferible primero ordenar y luego insertar.
void insert_ordered(struct list *lst, int elem){
  int added = 0;
  if(lst-> head != NULL){
    int i = 0;
    struct node *e = lst->head;
    while(e != NULL && added == 0){
      if(e->val >=  elem){
        add(elem, lst, i);
        added = 1;
      }else{
        e = e->next;
        i++;
      }
    }
  }else{
    add(elem, lst, 0);
    added = 1;
  }
  if(added == 0){
    addToEnd(elem, lst);
    added = 1;
  }
}
