#include "priority_queue.h"
#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void terminales_aux(Diccionario dic, ColaP cola) {
  if (dic->enlaceTerminal != NULL) cola_prioridad_push(cola, dic);
  for (int i = 0; i < CANT_LETRAS; i++) {
    if (dic->siguientes[i] != NULL) terminales_aux(dic->siguientes[i], cola);
  }
}

ColaP todos_links_terminales(Diccionario dic) {
  ColaP cola = crear_cola_prioridad(1);
  terminales_aux(dic, cola);
  return cola;
}

int main() {
  Diccionario dic = crear_diccionario();
  FILE *monstruo = fopen("diccionario.txt", "r");
  clock_t start_time = clock();
  agregar_archivo(&dic, monstruo);
  /* agregar_palabra(&dic, "Remesurar");
  agregar_palabra(&dic, "hermesurar");
  agregar_palabra(&dic, "A");
  agregar_palabra(&dic, "La");
  agregar_palabra(&dic, "Alah");
  agregar_palabra(&dic, "Mesura");
  agregar_palabra(&dic, "Emocion");
  agregar_palabra(&dic, "Alabar");*/

  clock_t end_time = clock();
  double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("Execution Time: %f seconds\n", execution_time);
  start_time = clock();
  algoritmo_Aho_Corasick(dic);
  end_time = clock();
  execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("Execution Time: %f seconds\n", execution_time);
  start_time = clock();
  destruir_diccionario(dic);
  end_time = clock();
  execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("Execution Time: %f seconds\n", execution_time);
  fclose(monstruo);
  return 0;
}