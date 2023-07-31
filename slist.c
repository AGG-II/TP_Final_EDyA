#include "slist.h"
#include <stdlib.h>

int slist_vacio(SList lista) { return lista->inicio == NULL; }

SList slist_crear() {
  SList vacio = malloc(sizeof(Lista));
  vacio->inicio = NULL;
  vacio->final = NULL;
  return vacio;
}

void agregar_lista_vacia(SList lista, Nodo nuevoNodo) {
  nuevoNodo->previo = NULL;
  nuevoNodo->siguiente = NULL;
  lista->inicio = nuevoNodo;
  lista->final = nuevoNodo;
}

void slist_push_top(SList lista, void *dato) {
  Nodo nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->dato = dato;
  if (slist_vacio(lista)) agregar_lista_vacia(lista, nuevoNodo);

  nuevoNodo->siguiente = lista->inicio;
  lista->inicio->previo = nuevoNodo;
  lista->inicio = nuevoNodo;
}

void slist_push_bottom(SList lista, void *dato) {
  Nodo nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->dato = dato;
  if (slist_vacio(lista)) agregar_lista_vacia(lista, nuevoNodo);
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
  if (nodoEliminar == lista->final) lista->final = NULL;
  destroy(nodoEliminar->dato);
  free(nodoEliminar);
}

void slist_pop_bottom(SList lista, FuncionDestructora destroy) {
  if (slist_vacio(lista)) return;
  Nodo nodoEliminar = lista->final;
  lista->final = nodoEliminar->previo;
  if (nodoEliminar == lista->inicio) lista->inicio = NULL;
  destroy(nodoEliminar->dato);
  free(nodoEliminar);
}

void slist_destruir(SList lista, FuncionDestructora destroy) {
  while (!slist_vacio(lista)) {
    slist_pop_top(lista, destroy);
  }
  free(lista);
}