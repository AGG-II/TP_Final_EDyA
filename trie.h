#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
// No se realizará distinción entre mayúsculas y minúsculas
#define CANT_LETRAS 26
// Numero ascii de la letra minúscula "a"
#define OFFSET 61
// Dado un numero entre 0 y 25 retorna el ascii de la letra en dicha posicion
#define LETRA_QUE_REPRESENTA(x) x + OFFSET

typedef enum {
  FINAL,   // Letra final de una palabra
  NO_FINAL // Letra no terminal de una palabra
} tipoEstado;

// Esta estructura será la que permita determinar las palabras válidas de
// nuestro diccionario
typedef struct AEFND {
  int profundidad;
  tipoEstado letraFinal;
  struct AEFND *siguientes[CANT_LETRAS];
  struct AEFND *prefijoMasLargo;
  tipoEstado tipoPrefijo;
} _Diccionario;

typedef _Diccionario *Diccionario;

/**
 * Retorna un diccionario vacio
 */
Diccionario crear_diccionario();

/**
 * Destruye el diccionario
 */
void destruir_diccionario(Diccionario);

/**
 * Indíca si el diccionario está vacio
 */
int diccionario_vacio(Diccionario);

/**
 * Retorna un numero entre 0 y 25 que representa en que posción debe ir la letra
 * para poder encontrar el nodo asociado a esa letra
 */
int posicion_asociada(char);

/**
 * Dada una letra y un nodo del diccionario, retorna un puntero al nodo a las
 * siguientes letras posibles si existen. Si no retorna NULL.
 */
Diccionario siguiente_estado(Diccionario, char);

/**
 *Dado un nodo de un diccionario y una letra avanza en el diccionario si existe
 *un nodo siguiente, si no lo crea
 */
Diccionario crear_siguiente_estado(Diccionario, char);

/**
 * Dada una string y un diccionario, agrega la palabra al diccionario
 */
void agregar_palabra(Diccionario *, char *);
// TODO: Cambiar de char* a FILE*

/**
 * Dado un archivo lee el caracter en el que se encuentra el cursor y si este es
 * una mayúscula retorna su equivalente en minúscula
 */
char proxima_minuscula(FILE *);

/**
 * Dado un archivo con palabras y un diccionario, agrega todas las palabras al
 * diccionario
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
Queue invariantes_Aho_Corasick(Diccionario);

/**
 * Dado un nodo padre y una lista de nodos, enlaza mediante el algoritmo
 * Aho-Corasick a todos los hijos del nodo y los agrega a la lista.
 *
 */
void encontrar_prefijos_hijos(Diccionario padre, Queue nodosPorNivel);

/**
 * Dado un nodo padre, uno de sus hijos y la letra asociada al hijo, enlaza al
 * hijo al prefijo más largo al que pertenece (exeptuando a la palabra a la que
 * pertenece el hijo).
 * En caso de no existir dicho prefijo, enlaza al hijo a la raiz del diccionario
 * al que pertenecen.
 */
void enlazar_prefijo(Diccionario padre, Diccionario hijo, char letraHijo);

/**
 * Dado un diccionario aplica el algoritmo Aho-Corasick para arboles trie
 */
void algoritmo_Aho_Corasick(Diccionario);

#endif