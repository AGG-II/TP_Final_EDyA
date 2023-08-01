
#ifndef PARSER_H
#define PARSER_H

#include "../intervalo/intervalo.h"
#include "../slist/slist.h"
#include "../trie/trie.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 1001 // Logitud máxima de una oración
// Si no se ingresaron palabras entonces la posicion inicial es la final
#define POSICION_TERMINADOR(x) x == 0 ? 0 : x - 1

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
 * archivo destino. Corrige las oraciones y las coloca en elarchivo destino.
 */
void parser_corregir_archivo(FILE *, Parser, FILE *);

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
 * Dada una string con un espacio al final o una string vacia coloca el fin de
 * caracter sobre el espacio.
 */
void colocar_terminador(char *, int);

/**
 * Carga las palabras y errores en el archivo
 */
void cargar_oraciones(char *, char *, FILE *);

#endif