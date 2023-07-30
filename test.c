#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  Diccionario dic = diccionario_crear();
  clock_t start_time = clock();
  diccionario_agregar_palabra(&dic, "Remesurar");
  diccionario_agregar_palabra(&dic, "hermesurar");
  diccionario_agregar_palabra(&dic, "A");
  diccionario_agregar_palabra(&dic, "La");
  diccionario_agregar_palabra(&dic, "Alah");
  diccionario_agregar_palabra(&dic, "Mesura");
  diccionario_agregar_palabra(&dic, "Emocion");
  diccionario_agregar_palabra(&dic, "Alabar");

  clock_t end_time = clock();
  double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("Execution Time: %f seconds\n", execution_time);
  start_time = clock();
  diccionario_algoritmo_Aho_Corasick(dic);
  end_time = clock();
  execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("Execution Time: %f seconds\n", execution_time);
  start_time = clock();
  diccionario_destruir(dic);
  end_time = clock();
  execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("Execution Time: %f seconds\n", execution_time);
  return 0;
}