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
  agregar_palabra(&dic, "Remesurar");
  agregar_palabra(&dic, "hermesurar");
  agregar_palabra(&dic, "A");
  agregar_palabra(&dic, "La");
  agregar_palabra(&dic, "Alah");
  agregar_palabra(&dic, "Mesura");
  agregar_palabra(&dic, "Emocion");
  agregar_palabra(&dic, "Alabar");
  algoritmo_Aho_Corasick(dic);
  destruir_diccionario(dic);
  return 0;
}