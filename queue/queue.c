#include "queue.h"
#include <stdlib.h>

int queue_nulo(Queue cola) { return cola == NULL; }

int queue_vacia(Queue cola) {
  return cola->final == NULL || cola->inicio == NULL;
}

Queue queue_crear() {
  Queue vacio = malloc(sizeof(struct _Queue));
  vacio->inicio = NULL;
  vacio->final = NULL;
  return vacio;
}

NodoCola crear_nodo(void *dato) {
  NodoCola vacio = malloc(sizeof(_Cola));
  vacio->dato = dato;
  vacio->siguiente = NULL;
  return vacio;
}

void queue_push(Queue *cola, void *dato) {
  NodoCola nuevoNodo = crear_nodo(dato);
  if (queue_nulo(*cola)) {
    (*cola) = queue_crear();
  }

  if (queue_vacia(*cola)) {
    (*cola)->inicio = nuevoNodo;
  } else {
    (*cola)->final->siguiente = nuevoNodo;
  }

  (*cola)->final = nuevoNodo;
}

void *queue_top(Queue cola) { return cola->inicio->dato; }

void queue_pop(Queue cola) {
  if (queue_nulo(cola) || queue_vacia(cola)) return;

  NodoCola nodoEliminar = cola->inicio;
  if (nodoEliminar == cola->final) cola->final = NULL;
  cola->inicio = nodoEliminar->siguiente;
  free(nodoEliminar);
}

void queue_destruir(Queue cola) {
  while (!queue_vacia(cola)) {
    queue_pop(cola);
  }
  free(cola);
}