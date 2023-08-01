#include "test_intervalo.h"
#include <stdio.h>
#include <stdlib.h>

void test_intervalo_crear() {
  Intervalo inter1 = intervalo_crear(1, 2);
  assert(inter1->inicio == 1);
  assert(inter1->final == 2);
  Intervalo inter2 = intervalo_crear(7, 8);
  assert(inter2->inicio == 7);
  assert(inter2->final == 8);
  Intervalo inter3 = intervalo_crear(1255, 1326);
  assert(inter3->inicio == 1255);
  assert(inter3->final == 1326);
  intervalo_destruir(inter1);
  intervalo_destruir(inter2);
  intervalo_destruir(inter3);
}
void test_intervalo_comparar() {
  Intervalo inter1 = intervalo_crear(1, 2);
  Intervalo inter2 = intervalo_crear(7, 8);
  Intervalo inter3 = intervalo_crear(1255, 1326);
  Intervalo inter4 = intervalo_crear(1, 300);

  assert(intervalo_comparar(inter1, inter1) == 0);
  assert(intervalo_comparar(inter1, inter2) > 0);
  assert(intervalo_comparar(inter1, inter3) > 0);
  assert(intervalo_comparar(inter1, inter4) < 0);

  assert(intervalo_comparar(inter2, inter3) > 0);
  assert(intervalo_comparar(inter2, inter4) < 0);

  assert(intervalo_comparar(inter3, inter4) < 0);
}

int main() {
  test_intervalo_crear();
  test_intervalo_comparar();
  printf("Yupi!");
  return 0;
}