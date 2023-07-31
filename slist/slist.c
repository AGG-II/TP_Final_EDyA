#include "slist.h"
#include <stdlib.h>

int slist_vacio(SList lista) {
  return lista->inicio == NULL && lista->final == NULL;
}

SList slist_crear() {
  SList vacio = malloc(sizeof(Lista));
  vacio->inicio = NULL;
  vacio->final = NULL;
  return vacio;
}

void agregar_lista_vacia(SList lista, Nodo nuevoNodo) {
  lista->inicio = nuevoNodo;
  lista->final = nuevoNodo;
}

void slist_push_top(SList lista, void *dato) {
  Nodo nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->dato = dato;
  nuevoNodo->previo = NULL;
  nuevoNodo->siguiente = NULL;
  if (slist_vacio(lista)) {
    agregar_lista_vacia(lista, nuevoNodo);
    return;
  }

  nuevoNodo->siguiente = lista->inicio;
  lista->inicio->previo = nuevoNodo;
  lista->inicio = nuevoNodo;
}

void slist_push_bottom(SList lista, void *dato) {
  Nodo nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->dato = dato;
  nuevoNodo->previo = NULL;
  nuevoNodo->siguiente = NULL;
  if (slist_vacio(lista)) {
    agregar_lista_vacia(lista, nuevoNodo);
    return;
  }

  nuevoNodo->previo = lista->final;
  lista->final->siguiente = nuevoNodo;
  lista->final = nuevoNodo;
}

void *slist_top(SList lista) {
  if (slist_vacio(lista)) return NULL;
  return lista->inicio->dato;
}

void *slist_bottom(SList lista) {
  if (slist_vacio(lista)) return NULL;
  return lista->final->dato;
}

void slist_pop_top(SList lista, FuncionDestructora destroy) {
  if (slist_vacio(lista)) return;
  Nodo nodoEliminar = lista->inicio;
  lista->inicio = nodoEliminar->siguiente;
  if (nodoEliminar == lista->final)
    lista->final = NULL;
  else
    lista->inicio->previo = NULL;
  destroy(nodoEliminar->dato);
  free(nodoEliminar);
}

void slist_pop_bottom(SList lista, FuncionDestructora destroy) {
  if (slist_vacio(lista)) return;
  Nodo nodoEliminar = lista->final;
  lista->final = nodoEliminar->previo;
  if (nodoEliminar == lista->inicio) // La lista tenia un solo elemento
    lista->inicio = NULL;
  else
    lista->final->siguiente = NULL;
  destroy(nodoEliminar->dato);
  free(nodoEliminar);
}

void slist_destruir(SList lista, FuncionDestructora destroy) {
  while (!slist_vacio(lista)) {
    slist_pop_top(lista, destroy);
  }
  free(lista);
}