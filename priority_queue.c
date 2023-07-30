#include "priority_queue.h"
#include <stdlib.h>

ColaP cola_prioridad_crear(unsigned int cantidad) {
  if (cantidad == 0) cantidad = 1;
  ColaP retorno = malloc(sizeof(_Priority));
  retorno->elementos = malloc(sizeof(Diccionario) * (cantidad + 1));
  retorno->elementos[0] = NULL;
  retorno->capacidad = cantidad;
  retorno->cantidadElementos = 0;
  return retorno;
}

int cola_prioridad_vacia(ColaP heap) { return heap->cantidadElementos == 0; }

void cola_prioridad_destruir(ColaP heap) {
  free(heap->elementos);
  free(heap);
}

int comparar_prioridades(Diccionario izquierda, Diccionario derecha) {
  int letraIzq = posicion_primera_letra(izquierda);
  int letraDer = posicion_primera_letra(derecha);
  if (letraDer == letraIzq) // si las dos palabras comienzan en el mismo nodo
    return izquierda->profundidad - derecha->profundidad;
  return letraDer - letraIzq;
}

int posicion_primera_letra(Diccionario nodo) {
  Diccionario ultLetraTerminal = nodo->enlaceTerminal;
  int longPalTerminal = ultLetraTerminal->profundidad;
  int profSubcadena = nodo->profundidad;
  return profSubcadena - longPalTerminal + 1;
}

Diccionario cola_prioridad_top(ColaP heap) { return heap->elementos[1]; }

void cola_prioridad_pop(ColaP heap) {
  if (cola_prioridad_vacia(heap)) return;
  int esMayor = 1;
  int ultElem = --heap->cantidadElementos; // posicion del ultimo elemento
  heap->elementos[1] = heap->elementos[ultElem];
  heap->elementos[ultElem] = NULL;
  int j = 1, k;
  Diccionario *a = heap->elementos, t;
  while (2 * j <= ultElem && esMayor) {
    k = 2 * j;
    if (k + 1 <= ultElem && comparar_prioridades(a[k + 1], a[k]) > 0) k = k + 1;
    if (comparar_prioridades(a[j], a[k]) > 0)
      esMayor = 0;
    else {
      t = a[j];
      a[j] = a[k];
      a[k] = t;
      j = k;
    }
  }
}

void cola_prioridad_aumentar_capacidad(ColaP heap, int nuevaCapacidad) {
  Diccionario *elems = heap->elementos;
  heap->capacidad = nuevaCapacidad;
  heap->elementos = realloc(elems, sizeof(Diccionario) * (nuevaCapacidad + 1));
}

void cola_prioridad_push(ColaP heap, Diccionario nodo) {
  int cantElem = heap->cantidadElementos;
  int capacidad = heap->capacidad;
  if (cantElem == capacidad) { // si el heap esta lleno
    capacidad *= 2;
    cola_prioridad_aumentar_capacidad(heap, capacidad);
  }
  Diccionario *elems = heap->elementos, t;
  elems[++cantElem] = nodo;
  for (int j = cantElem;
       j > 1 && comparar_prioridades(elems[j], elems[j / 2]) > 0; j /= 2) {
    t = elems[j];
    elems[j] = elems[j / 2];
    elems[j / 2] = t;
  }
  heap->cantidadElementos++;
}

void cola_prioridad_vaciar(ColaP heap) {
  int cantidadElem = heap->cantidadElementos;
  heap->cantidadElementos = 0;
  for (int i = 1; i < cantidadElem; i++) {
    heap->elementos[i] = NULL;
  }
}