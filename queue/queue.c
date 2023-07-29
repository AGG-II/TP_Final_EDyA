#include "queue.h"
#include <stdlib.h>

int queue_nulo(Queue cola) { return cola == NULL; }

int queue_vacia(Queue cola) { return cola->estado == VACIA; }

Queue crear_queue(unsigned int capacidad) {
  if (capacidad < 1) capacidad = 1;
  Queue cola = malloc(sizeof(struct _Queue));
  cola->inicio = 0;
  cola->final = 0;
  cola->capacidad = capacidad;
  cola->elementos = malloc(sizeof(void *) * capacidad);
  cola->estado = VACIA;
  return cola;
}

void duplicar_capacidad(Queue cola) {
  int capacidad = cola->capacidad;
  int inicio = cola->inicio;
  int final = cola->final;
  int nuevaPos = 0, i = inicio;
  void **elementos = cola->elementos;
  // creamos un array con el doble de espacio
  void **nuevosElementos = malloc(sizeof(void *) * (capacidad * 2));
  do {
    nuevosElementos[nuevaPos] = elementos[i];
    nuevaPos++;
    i = siguiente_posicion(cola, i);
  } while (i != final);
  cola->capacidad *= 2;
  cola->elementos = nuevosElementos;
  cola->final = nuevaPos;
  cola->inicio = 0;
  free(elementos);
}

int siguiente_posicion(Queue cola, int posicion) {
  return (posicion + 1) % cola->capacidad;
}

void queue_push(Queue *cola, void *dato) {
  if (queue_nulo(*cola)) *cola = crear_queue(2);
  switch ((*cola)->estado) {
  case VACIA:
    agregar_vacia(*cola, dato);
    return;
  case LLENA:
    agregar_llena(*cola, dato);
    return;
  default:
    agregar_cargada(*cola, dato);
  }
}

void agregar_vacia(Queue cola, void *dato) {
  int inicio = cola->inicio;
  int final = cola->final;
  int sigPos = siguiente_posicion(cola, final);
  cola->elementos[inicio] = dato;
  cola->final = sigPos;
  if (cola->capacidad == 1)
    cola->estado = LLENA;
  else
    cola->estado = CARGADA;
}

void agregar_llena(Queue cola, void *dato) {
  duplicar_capacidad(cola);
  cola->estado = CARGADA;
  agregar_cargada(cola, dato);
}

void agregar_cargada(Queue cola, void *dato) {
  int final = cola->final;
  int inicio = cola->inicio;
  cola->elementos[final] = dato;
  final = siguiente_posicion(cola, final);
  // Caso de llenar la cola
  if (final == inicio) cola->estado = LLENA;
  cola->final = final;
}

void *queue_top(Queue cola) {
  if (queue_vacia(cola)) return NULL;
  int inicio = cola->inicio;
  return cola->elementos[inicio];
}

void queue_pop(Queue cola) {
  if (queue_vacia(cola)) return;
  int inicio = cola->inicio;
  inicio = siguiente_posicion(cola, inicio);
  if (inicio == cola->final) cola->estado = VACIA;
  cola->inicio = inicio;
}

void queue_destruir(Queue cola) {
  free(cola->elementos);
  free(cola);
}