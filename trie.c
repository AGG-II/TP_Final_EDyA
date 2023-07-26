#include "trie.h"
#include "queue.h"
#include <ctype.h>
#include <stdlib.h>

Diccionario crear_diccionario() {
  Diccionario vacio = calloc(1, sizeof(_Diccionario));
  vacio->profundidad = 0; // redundante
  vacio->letraFinal = NO_FINAL;
  /*vacio->prefijoMasLargo = NULL;
  vacio->terminalMasLargo = NULL;
  for (int i = 0; i < CANT_LETRAS; i++)
    vacio->siguientes[i] = NULL;
  */
  return vacio;
}

void destruir_diccionario(Diccionario destruir) {
  if (destruir == NULL) return;
  for (int i = 0; i < CANT_LETRAS; i++) {
    destruir_diccionario(destruir->siguientes[i]);
  }
  free(destruir);
}

int diccionario_vacio(Diccionario inicio) { return inicio == NULL; }

int posicion_asociada(char letra) { return tolower(letra) - OFFSET; }

Diccionario siguiente_estado(Diccionario letraActual, char letra) {
  int numeroAsociado = posicion_asociada(letra);
  return letraActual->siguientes[numeroAsociado];
}

Diccionario crear_siguiente_estado(Diccionario posicionActual, char letra) {
  Diccionario nodoSiguiente = siguiente_estado(posicionActual, letra);

  if (diccionario_vacio(nodoSiguiente)) { // si el estado no existe
    int numeroAsociado = posicion_asociada(letra);
    nodoSiguiente = crear_diccionario();
    nodoSiguiente->profundidad = posicionActual->profundidad + 1;
    posicionActual->siguientes[numeroAsociado] = nodoSiguiente;
  }
  return nodoSiguiente;
}

// La funcion asume que la variable palabra solo contiene caracteres de la A
// hasta la Z tanto en minúscula como en mayúscula
void agregar_palabra(Diccionario *inicio, char *palabra) {

  // Aseguramos que exista la posición
  if (diccionario_vacio(*inicio)) {
    *inicio = crear_diccionario();
  }

  Diccionario recorredor = *inicio;

  for (int i = 0; palabra[i] != '\0'; i++) {
    recorredor = crear_siguiente_estado(recorredor, palabra[i]);
  }
  recorredor->letraFinal = FINAL;
}

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

Queue invariantes_Aho_Corasick(Diccionario raiz) {
  raiz->prefijoMasLargo = raiz;
  Diccionario hijo;
  Queue nodosPorNivel = crear_queue();
  for (int i = 0; i < CANT_LETRAS; i++) {
    hijo = raiz->siguientes[i];
    if (!diccionario_vacio(hijo)) {
      hijo->prefijoMasLargo = raiz;
      queue_push(&nodosPorNivel, (void *)hijo);
    }
  }
  return nodosPorNivel;
}

void encontrar_prefijos_hijos(Diccionario padre, Queue nodosPorNivel) {
  char letraAsociada;
  Diccionario hijo;
  for (int i = 0; i < CANT_LETRAS; i++) {
    hijo = padre->siguientes[i];
    if (!diccionario_vacio(hijo)) {
      letraAsociada = (char)LETRA_QUE_REPRESENTA(i);
      enlazar_prefijo(padre, hijo, letraAsociada);
      enlazar_terminal(hijo);
      queue_push(&nodosPorNivel, (void *)hijo);
    }
  }
}

void enlazar_prefijo(Diccionario padre, Diccionario hijo, char letraHijo) {
  int seEnlazo = 0;
  Diccionario prefijoAsociado;
  while (!seEnlazo) {
    padre = padre->prefijoMasLargo;
    prefijoAsociado = siguiente_estado(padre, letraHijo);

    if (!diccionario_vacio(prefijoAsociado)) {
      hijo->prefijoMasLargo = prefijoAsociado;
      seEnlazo = 1;
    } else if (padre == padre->prefijoMasLargo) { // Se alcanzó la raiz
      hijo->prefijoMasLargo = padre;
      seEnlazo = 1;
    }
  }
}

void enlazar_terminal(Diccionario nodo) {
  int seEnlazo = 0;
  for (Diccionario enlace = nodo->prefijoMasLargo;
       enlace != enlace->prefijoMasLargo && !seEnlazo;
       enlace = enlace->prefijoMasLargo) {
    // Mientras el enlace no sea la raiz y no se haya encontrado el nodo buscado
    if (enlace->letraFinal == FINAL) {
      nodo->terminalMasLargo = enlace;
      seEnlazo = 1;
    }
  }
}

void algoritmo_Aho_Corasick(Diccionario inicio) {
  if (diccionario_vacio(inicio)) return;
  Queue nodosPorNivel = invariantes_Aho_Corasick(inicio);
  Diccionario nodo;
  do {
    nodo = queue_top(nodosPorNivel);
    queue_pop(nodosPorNivel);
    encontrar_prefijos_hijos(nodo, nodosPorNivel);
  } while (!queue_vacia(nodosPorNivel));
}