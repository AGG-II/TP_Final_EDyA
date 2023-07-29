#ifndef PARSER_H
#define PARSER_H

#include "trie.h"
#include <stdio.h>

typedef struct {
  Diccionario palabras;
} _Parser;

/**
 * Dado un archivo lee el caracter en el que se encuentra el cursor y si
 * este es una mayúscula retorna su equivalente en minúscula.
 */
char proxima_minuscula(FILE *);

/**
 * Dado un archivo con palabras y un diccionario, agrega todas las palabras al
 * diccionario.
 */
void agregar_archivo(Diccionario *, FILE *);

/**
 * Dado un diccionario establece las invariantes del algoritmo Aho-Corasick
 * Invariantes:
 *  -La raiz del trie se apunta a si mismo
 *  -Los hijos inmediatos de la raiz apuntan a la raiz
 * La función retorna una cola con todos los hijos de la raiz para poder seguir
 * aplicando el algoritmo.
 */

#endif