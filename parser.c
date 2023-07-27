#include "trie.h"
#include <ctype.h>
#include <stdio.h>

void agregar_archivo(Diccionario *inicio, FILE *fuente) {
  Diccionario posicionActual = *inicio;
  for (char letraActual = proxima_minuscula(fuente); letraActual != EOF;
       letraActual = proxima_minuscula(fuente)) {

    if (isalpha(letraActual)) {
      posicionActual = crear_siguiente_estado(posicionActual, letraActual);
    } else if (letraActual == '\n') {
      posicionActual->letraFinal = FINAL;
      posicionActual = *inicio;
    }
  }
  posicionActual->letraFinal = FINAL;
}