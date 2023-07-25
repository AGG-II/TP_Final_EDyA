#include "stack.h"
#include <stdlib.h>

int stack_vacio(Stack pila) { return pila == NULL; }

Stack crear_stack() {
  Stack vacio = malloc(sizeof(_Pila));
  vacio->siguiente = NULL;
  vacio->dato = NULL;
  return vacio;
}

void stack_push(Stack *pila, void *dato) {
  Stack nuevoNodo = crear_stack();
  nuevoNodo->dato = dato;
  if (!stack_vacio(*pila)) nuevoNodo->siguiente = *pila;
  *pila = nuevoNodo;
}

void *stack_top(Stack pila) { return pila->dato; }

void stack_pop(Stack *pila) {
  if (stack_vacio(*pila)) return;
  Stack nodoEliminar = *pila;
  *pila = nodoEliminar->siguiente;
  free(nodoEliminar);
}