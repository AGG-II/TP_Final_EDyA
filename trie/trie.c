#include "trie.h"
#include <ctype.h>
#include <stdlib.h>

Diccionario diccionario_crear() {
  Diccionario vacio = calloc(1, sizeof(_Diccionario));
  vacio->profundidad = 0; // redundante
  vacio->letraFinal = NO_FINAL;
  vacio->enlaceTerminal = NULL;
  return vacio;
}

void diccionario_destruir(Diccionario destruir) {
  for (int i = 0; i < CANT_LETRAS; i++) {
    if (destruir->siguientes[i] != NULL)
      diccionario_destruir(destruir->siguientes[i]);
  }
  free(destruir);
}

int diccionario_vacio(Diccionario inicio) { return inicio == NULL; }

int posicion_asociada(char letra) { return tolower(letra) - OFFSET; }

Diccionario diccionario_siguiente_estado(Diccionario letraActual, char letra) {
  int numeroAsociado = posicion_asociada(letra);
  return letraActual->siguientes[numeroAsociado];
}

Diccionario crear_siguiente_estado(Diccionario posicionActual, char letra) {
  int numeroAsociado = posicion_asociada(letra);
  Diccionario nodoSiguiente = posicionActual->siguientes[numeroAsociado];

  if (nodoSiguiente == NULL) { // si el estado no existe
    int numeroAsociado = posicion_asociada(letra);
    nodoSiguiente = diccionario_crear();
    nodoSiguiente->profundidad = posicionActual->profundidad + 1;
    posicionActual->siguientes[numeroAsociado] = nodoSiguiente;
  }
  return nodoSiguiente;
}

// La funcion asume que la variable palabra solo contiene caracteres de la A
// hasta la Z tanto en minúscula como en mayúscula
void diccionario_agregar_palabra(Diccionario *inicio, char *palabra) {

  // Aseguramos que exista la posición
  if ((*inicio) == NULL) {
    *inicio = diccionario_crear();
  }

  Diccionario recorredor = *inicio;

  for (int i = 0; palabra[i] != '\0'; i++) {
    recorredor = crear_siguiente_estado(recorredor, palabra[i]);
  }
  recorredor->letraFinal = FINAL;
}

void diccionario_agregar_archivo(Diccionario *inicio, FILE *fuente) {
  Diccionario posicionActual = *inicio;
  for (char letraActual = fgetc(fuente); letraActual != EOF;
       letraActual = fgetc(fuente)) {
    if (letraActual == '\n' || letraActual == '\r') { // LLego a fin de linea
      posicionActual->letraFinal = FINAL;
      posicionActual = *inicio;
    } else { // leyo una letra
      posicionActual = crear_siguiente_estado(posicionActual, letraActual);
    }
  }
  posicionActual->letraFinal = FINAL;
}

Queue invariantes_Aho_Corasick(Diccionario raiz) {
  raiz->enlaceFallo = raiz;
  Diccionario hijo;
  Queue nodosPorNivel = queue_crear();
  for (int i = 0; i < CANT_LETRAS; i++) {
    // todos los hijos tienen como link de fallo a la raiz
    hijo = raiz->siguientes[i];
    if (hijo != NULL) {
      hijo->enlaceFallo = raiz;
      queue_push(nodosPorNivel, (void *)hijo);
    }
  }
  return nodosPorNivel;
}

void encontrar_prefijos_hijos(Diccionario padre, Diccionario raiz,
                              Queue nodosPorNivel) {
  char letraAsociada;
  Diccionario hijo;
  for (int i = 0; i < CANT_LETRAS; i++) {
    hijo = padre->siguientes[i];
    if (hijo != NULL) {
      letraAsociada = (char)LETRA_QUE_REPRESENTA(i);
      if (hijo->letraFinal == FINAL) { // invariante extra
        hijo->enlaceFallo = raiz;
      } else {
        enlazar_prefijo(padre, hijo, letraAsociada);
        enlazar_terminal(hijo);
      }
      queue_push(nodosPorNivel, (void *)hijo);
    }
  }
}

void enlazar_prefijo(Diccionario padre, Diccionario hijo, char letraHijo) {
  int seEnlazo = 0;
  Diccionario prefijoAsociado;
  while (!seEnlazo) {
    padre = padre->enlaceFallo;
    prefijoAsociado = diccionario_siguiente_estado(padre, letraHijo);

    if (prefijoAsociado != NULL) {
      hijo->enlaceFallo = prefijoAsociado;
      seEnlazo = 1;
    } else if (padre == padre->enlaceFallo) { // Se alcanzó la raiz
      hijo->enlaceFallo = padre;
      seEnlazo = 1;
    }
  }
}

void enlazar_terminal(Diccionario nodo) {
  if (nodo->letraFinal == FINAL) return; // El enlace no es necesario
  int seEnlazo = 0;
  for (Diccionario enlace = nodo->enlaceFallo;
       enlace != enlace->enlaceFallo && !seEnlazo;
       enlace = enlace->enlaceFallo) {
    // Mientras el enlace no sea la raiz y no se haya encontrado el nodo buscado
    if (enlace->letraFinal == FINAL) {
      nodo->enlaceTerminal = enlace;
      seEnlazo = 1;
    }
  }
}

void diccionario_algoritmo_Aho_Corasick(Diccionario inicio) {
  if (inicio == NULL) return;
  Queue nodosPorNivel = invariantes_Aho_Corasick(inicio);
  Diccionario nodo;
  do {
    nodo = queue_top(nodosPorNivel);
    queue_pop(nodosPorNivel);
    encontrar_prefijos_hijos(nodo, inicio, nodosPorNivel);
  } while (!queue_vacia(nodosPorNivel));
  queue_destruir(nodosPorNivel);
}