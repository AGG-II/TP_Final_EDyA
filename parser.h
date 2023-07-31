
#ifndef PARSER_H
#define PARSER_H

#include "intervalo.h"
#include "slist.h"
#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 1001 // Logitud máxima de una oración

typedef Diccionario Parser;

/**
 * Crea un parser.
 */
Parser parser_crear();

/**
 * Destruye un parser.
 */
void parser_destruir(Parser);

/**
 * Determina si un parser esta vacio.
 */
int parser_vacio(Parser);

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
 * Dado un parser, una oracion y un archivo. Corrige la oracion y coloca la
 * correccion en el archivo.
 */
void corregir_oracion(Parser, char *, FILE *);

/**
 * Dado un parser cargado con un diccionario, un archivo con oraciones y el
 * nombre del archivo a crear. Crea un nuevo archivo con las oraciones
 * corregidas.
 */
void parser_corregir_archivo(const char *, Parser, const char *);

/**
 * Agrega un intervalo a la lista de intervalos eliminando los que son de menor
 * prioridad primero.
 */
void agregar_intervalo(Intervalo, SList);

/**
 * Dado un nodo con enalce terminal determina la posicion de la primera letra de
 * la palabra.
 */
int posicion_incial(Parser, int);

/**
 * Agrega un enlace de una palabra a la lista de enlaces.
 */
void agregar_enalce(int, int, SList);

/**
 * Lee la oración  y retorna una lista de intervalos en donde se encuentran las
 * palabras dentro de la oración.
 */
SList procesar_oracion(Parser, char *);

/**
 * Dado los extremos de una palabra, un string destino desde donde escribir en
 * el ddestino y de donde leer la palabra. Escribe la palabra en el destino.
 * Retorna la cantidad de caracteres escritos.
 */
int cargar_string(Intervalo, char *, int, char *);

/**
 * Carga consigue las palabras y errores de la oracion en base a los resultados
 * obatenidos del procesamiento.
 */
void cargar_resultados(SList, char *, FILE *);

/**
 * Carga las palabras y errores en el archivo
 */
void cargar_oraciones(char *, char *, FILE *);

#endif