#ifndef PARSER_H
#define PARSER_H

#include "priority_queue.h"
#include "trie.h"
#include <stdio.h>

#define BUFFER 1001 // Logitud máxima de una oración

typedef struct {
  Diccionario palabras;
  ColaP enlacesTerminales;
} _Parser;

typedef _Parser *Parser;

/**
 * Crea un parser.
 */
Parser parser_crear();

/**
 * Destruye el parser.
 */
void parser_destruir(Parser);

/**
 * Determina si el parser dado es nulo.
 */
int parser_nulo(Parser);

/**
 * Dado un archivo con palabras las agrega al Diccionario del parser y aplica el
 * algoritmo Aho-Corasick.
 */
void parser_cargar_archivo(Parser *, FILE *);

/**
 * Dado un archivo carga toda la oración en donde se encuentra el cursor hasta
 * el final de la linea.
 * La función retorna != 0 si pudo cargar la linea.
 * En caso contrario retorna 0.
 */
int obtener_oracion(FILE *, char *);

/**
 * Dado un parser cargado con un diccionario, un archivo con oraciones y el
 * nombre del archivo a crear. Crea un nuevo archivo con las oraciones
 * corregidas.
 */
void parser_corregir(FILE *, Parser, const char *);

#endif