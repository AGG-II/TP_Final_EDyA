#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Diccionario dic = crear_diccionario();
  agregar_palabra(&dic, "Remesurar");
  agregar_palabra(&dic, "A");
  agregar_palabra(&dic, "La");
  agregar_palabra(&dic, "Alah");
  agregar_palabra(&dic, "Mesura");
  agregar_palabra(&dic, "Emocion");
  agregar_palabra(&dic, "Alabar");
  algoritmo_Aho_Corasick(dic);
  destruir_diccionario(dic);
  FILE *archivo = fopen("hola.txt", "r");
  dic = crear_diccionario();
  agregar_archivo(&dic, archivo);
  algoritmo_Aho_Corasick(dic);
  destruir_diccionario(dic);
  return 0;
}