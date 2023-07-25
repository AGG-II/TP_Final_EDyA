#include "trie.h"
#include "queue.h"
#include <stdlib.h>

Diccionario crear_diccionario() {
  Diccionario vacio = calloc(1, sizeof(_Diccionario));
  vacio->profundidad = 0;
  vacio->letraFinal = NO_FINAL;
  vacio->tipoPrefijo = NO_FINAL;
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

int posicion_asociada(char letra) {
  return tolower(letra) - CANT_LETRAS - OFFSET;
}

Diccionario siguiente_estado(Diccionario letraActual, char letra) {
  int numeroAsociado = posicion_asociada(letra);
  return letraActual->siguientes[numeroAsociado];
}

Diccionario crear_siguiente_estado(Diccionario posicionActual, char letra) {
  Diccionario nodoSiguiente = siguiente_estado(posicionActual, letra);
  int numeroAsociado = posicion_asociada(letra);

  if (diccionario_vacio(nodoSiguiente)) { // si el estado no existe
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

  char letra;
  Diccionario recorredor = *inicio;

  for (int i = 0; palabra[i] != '\0'; i++) {
    recorredor = crear_siguiente_estado(recorredor, palabra[i]);
  }
  recorredor->letraFinal = FINAL;
}

char proxima_minuscula(FILE *fuente) { return tolower(fgetc(fuente)); }

void agregar_archivo(Diccionario *inicio, FILE *fuente) {
  Diccionario posicionActual = *inicio, nodoSiguiente;
  for (char letraActual = proxima_minuscula(fuente); letraActual != EOF;
       letraActual = proxima_minuscula(fuente)) {

    if (isalpha(letraActual)) {
      posicionActual = crear_siguiente_estado(posicionActual, letraActual);
    } else {
      posicionActual->letraFinal = FINAL;
      posicionActual = *inicio;
    }
  }
}

Queue invariantes_Aho_Corasick(Diccionario inicio) {
  inicio->prefijoMasLargo = inicio;
  Diccionario nivel;
  Queue nodosPorNivel = crear_queue();
  for (int i = 0; i < CANT_LETRAS; i++) {
    nivel = inicio->siguientes[i];
    if (!diccionario_vacio(nivel)) {
      nivel->prefijoMasLargo = inicio;
      queue_push(nodosPorNivel, (void *)nivel);
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
      queue_push(nodosPorNivel, (void *)hijo);
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
      if (prefijoAsociado->letraFinal == FINAL) hijo->tipoPrefijo = FINAL;
      seEnlazo = 1;
    } else if (padre == padre->prefijoMasLargo) { // Se alcanzó la raiz
      hijo->prefijoMasLargo = padre;
      seEnlazo = 1;
    }
  }
}

void algoritmo_Aho_Corasick(Diccionario inicio) {
  if (diccionario_vacio(inicio)) return;
  Queue nodosPorNivel = invariantes_Aho_Corasick(inicio);
  for (Diccionario nodo = queue_top(nodosPorNivel); !queue_vacia(nodosPorNivel);
       nodo = queue_top(nodosPorNivel)) {
    queue_pop(nodosPorNivel);
    encontrar_prefijos_hijos(nodo, nodosPorNivel);
  }
}