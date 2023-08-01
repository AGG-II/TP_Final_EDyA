#include "intervalo.h"
#include <stdlib.h>

Intervalo intervalo_crear(int inicio, int final) {
  Intervalo retorno = malloc(sizeof(_Intervalo));
  retorno->inicio = inicio;
  retorno->final = final;
  return retorno;
}

void intervalo_destruir(Intervalo rango) { free(rango); }

int intervalo_comparar(Intervalo izq, Intervalo der) {
  if (izq->inicio == der->inicio) return izq->final - der->final;
  return der->inicio - izq->inicio;
}