#include "parser.h"
#include <ctype.h>

char proxima_minuscula(FILE *fuente) { return tolower(fgetc(fuente)); }

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