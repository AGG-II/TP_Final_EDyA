#include "test_queue.h"
#include <stdio.h>
#include <stdlib.h>

void test_queue_nulo() {
  Queue colaNula = NULL;
  Queue colaInicializada = crear_queue(2);
  assert(queue_nulo(colaNula));
  assert(!queue_nulo(colaInicializada));
  queue_destruir(colaInicializada);
}

void test_queue_push() {
  Queue cola = crear_queue(1);
  assert(queue_vacia(cola));
  assert(queue_top(cola) == NULL);
  int numeros[3] = {1, 2, 3};

  queue_push(&cola, numeros);
  assert(cola->estado == LLENA);
  assert(queue_top(cola) == numeros);

  queue_push(&cola, numeros + 1);
  assert(cola->estado == LLENA);
  assert(queue_top(cola) == numeros);

  queue_push(&cola, numeros + 2);
  assert(cola->estado == CARGADA);
  assert(queue_top(cola) == numeros);
  queue_destruir(cola);
}

void test_duplicar_capacidad() {
  Queue cola = crear_queue(1);
  assert(cola->capacidad == 1);

  duplicar_capacidad(cola);
  assert(cola->capacidad == 2);

  duplicar_capacidad(cola);
  assert(cola->capacidad == 4);
  queue_destruir(cola);
}

void test_siguiente_posicion() {
  Queue cola = crear_queue(1);
  int numeros[3] = {1, 2, 3};
  assert(siguiente_posicion(cola, cola->final) == 0);

  queue_push(&cola, numeros);
  assert(siguiente_posicion(cola, cola->final) == 0);

  queue_push(&cola, numeros + 1);
  assert(siguiente_posicion(cola, cola->final) == 1);

  queue_push(&cola, numeros + 2);
  assert(siguiente_posicion(cola, cola->final) == 0);
  queue_destruir(cola);
}
void test_queue_pop() {
  Queue cola = crear_queue(0);
  int numeros[4] = {1, 2, 3, 4};
  queue_push(&cola, (void *)1);
  queue_pop(cola);
  assert(queue_top(cola) == NULL);

  queue_push(&cola, numeros);
  queue_push(&cola, numeros + 1);
  queue_pop(cola);
  assert(queue_top(cola) == numeros + 1);
  queue_pop(cola);
  assert(queue_top(cola) == NULL);

  queue_push(&cola, numeros);
  queue_push(&cola, numeros + 1);
  queue_push(&cola, numeros + 2);
  queue_push(&cola, numeros + 3);
  queue_pop(cola);
  assert(queue_top(cola) == numeros + 1);
  queue_pop(cola);
  assert(queue_top(cola) == numeros + 2);
  queue_pop(cola);
  assert(queue_top(cola) == numeros + 3);
  queue_pop(cola);
  assert(queue_top(cola) == NULL);

  queue_destruir(cola);
}

int main() {
  test_queue_nulo();
  test_queue_push();
  test_duplicar_capacidad();
  test_queue_pop();
  test_siguiente_posicion();
  printf("Yupi!");
  return 0;
}