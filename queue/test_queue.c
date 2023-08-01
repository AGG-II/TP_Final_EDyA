#include "test_queue.h"
#include <stdio.h>
#include <stdlib.h>

void test_queue_push() {
  Queue cola = queue_crear();
  int numeros[] = {0, 1, 2};
  assert(queue_vacia(cola));
  // metemos el 0
  queue_push(cola, numeros);
  assert(!queue_vacia(cola));
  assert(queue_top(cola) == numeros);
  // metemos el 1
  queue_push(cola, numeros + 1);
  assert(!queue_vacia(cola));
  assert(queue_top(cola) == numeros);
  // metemos el 2
  queue_push(cola, numeros + 2);
  assert(!queue_vacia(cola));
  assert(queue_top(cola) == numeros);
  queue_destruir(cola);
}

void test_queue_pop() {
  Queue cola = queue_crear();
  int numeros[] = {0, 1, 2};
  assert(queue_vacia(cola));
  queue_push(cola, numeros);
  queue_push(cola, numeros + 1);
  queue_push(cola, numeros + 2);
  // sacamos el 0
  queue_pop(cola);
  assert(queue_top(cola) == numeros + 1);
  // sacamos el 1
  queue_pop(cola);
  assert(queue_top(cola) == numeros + 2);
  // sacamos el 2
  queue_pop(cola);
  assert(queue_vacia(cola));
  queue_destruir(cola);
}

int main() {
  test_queue_push();
  test_queue_pop();
  printf("Yupi!");
  return 0;
}