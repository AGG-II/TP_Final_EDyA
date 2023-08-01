#include "test_slist.h"
#include <stdio.h>
#include <stdlib.h>

void test_slist_push_top() {
  SList cola = slist_crear();
  int *numero1 = malloc(sizeof(int));
  (*numero1) = 1;
  int *numero2 = malloc(sizeof(int));
  (*numero2) = 2;
  int *numero3 = malloc(sizeof(int));
  (*numero3) = 3;
  int *numero4 = malloc(sizeof(int));
  (*numero3) = 4;
  assert(slist_vacio(cola));

  // metemos por arriba el 1
  slist_push_top(cola, numero1);
  assert(!slist_vacio(cola));
  assert(slist_top(cola) == numero1);
  assert(slist_bottom(cola) == numero1);

  // metemos por arriba el 2
  slist_push_top(cola, numero2);
  assert(!slist_vacio(cola));
  assert(slist_top(cola) == numero2);

  // metemos por arriba el 3
  slist_push_top(cola, numero3);
  assert(!slist_vacio(cola));
  assert(slist_top(cola) == numero3);

  // metemos por debajo el 4
  slist_push_bottom(cola, numero4);
  assert(!slist_vacio(cola));
  assert(slist_top(cola) == numero3);

  slist_destruir(cola, free);
}

void test_slist_push_bottom() {
  SList cola = slist_crear();
  int *numero1 = malloc(sizeof(int));
  (*numero1) = 1;
  int *numero2 = malloc(sizeof(int));
  (*numero2) = 2;
  int *numero3 = malloc(sizeof(int));
  (*numero3) = 3;
  int *numero4 = malloc(sizeof(int));
  (*numero3) = 4;
  assert(slist_vacio(cola));

  // metemos por debajo el 1
  slist_push_bottom(cola, numero1);
  assert(!slist_vacio(cola));
  assert(slist_bottom(cola) == numero1);
  assert(slist_top(cola) == numero1);

  // metemos por debajo el 2
  slist_push_bottom(cola, numero2);
  assert(!slist_vacio(cola));
  assert(slist_bottom(cola) == numero2);

  // metemos por debajo el 3
  slist_push_bottom(cola, numero3);
  assert(!slist_vacio(cola));
  assert(slist_bottom(cola) == numero3);

  // metemos por arriba el 4
  slist_push_top(cola, numero4);
  assert(!slist_vacio(cola));
  assert(slist_bottom(cola) == numero3);

  slist_destruir(cola, free);
}

void test_slist_pop_top() {
  SList cola = slist_crear();
  int *numero1 = malloc(sizeof(int));
  (*numero1) = 1;
  int *numero2 = malloc(sizeof(int));
  (*numero2) = 2;
  int *numero3 = malloc(sizeof(int));
  (*numero3) = 3;
  int *numero4 = malloc(sizeof(int));
  (*numero3) = 4;
  assert(slist_vacio(cola));

  slist_push_top(cola, numero1);
  slist_push_top(cola, numero2);
  slist_push_top(cola, numero3);
  slist_push_top(cola, numero4);

  assert(slist_top(cola) == numero4);
  assert(slist_bottom(cola) == numero1);
  slist_pop_top(cola, free);
  // sacamos el 4
  assert(slist_top(cola) == numero3);
  assert(slist_bottom(cola) == numero1);
  slist_pop_top(cola, free);
  // sacamos el 3
  assert(slist_top(cola) == numero2);
  assert(slist_bottom(cola) == numero1);
  slist_pop_top(cola, free);
  // sacamos el 2
  assert(slist_top(cola) == numero1);
  assert(slist_bottom(cola) == numero1);
  slist_pop_top(cola, free);
  // sacamos el 1
  assert(slist_vacio);
  slist_destruir(cola, free);
}

void test_slist_pop_bottom() {
  SList cola = slist_crear();
  int *numero1 = malloc(sizeof(int));
  (*numero1) = 1;
  int *numero2 = malloc(sizeof(int));
  (*numero2) = 2;
  int *numero3 = malloc(sizeof(int));
  (*numero3) = 3;
  int *numero4 = malloc(sizeof(int));
  (*numero3) = 4;
  assert(slist_vacio(cola));

  slist_push_top(cola, numero1);
  slist_push_top(cola, numero2);
  slist_push_top(cola, numero3);
  slist_push_top(cola, numero4);
  // sacamos el 1
  assert(slist_bottom(cola) == numero1);
  assert(slist_top(cola) == numero4);
  slist_pop_bottom(cola, free);
  // sacamos el 2
  assert(slist_bottom(cola) == numero2);
  assert(slist_top(cola) == numero4);
  slist_pop_bottom(cola, free);
  // sacamos el 3
  assert(slist_bottom(cola) == numero3);
  assert(slist_top(cola) == numero4);
  slist_pop_bottom(cola, free);
  // sacamos el 4
  assert(slist_bottom(cola) == numero4);
  assert(slist_top(cola) == numero4);
  slist_pop_bottom(cola, free);

  assert(slist_vacio);
  slist_destruir(cola, free);
}

int main() {
  test_slist_push_top();
  test_slist_push_bottom();
  test_slist_pop_top();
  printf("Yupi!");
  return 0;
}