/**
 * La estructura que se define a continuación tiene el objetivo de ser utilizada
 * para guardar nodos de la estructura "Diccionario" que poseean un enlace
 * terminal.
 */

#ifndef P_QUEUE_H
#define P_QUEUE_H

#include "trie.h"

typedef struct {
  int capacidad;
  int cantidadElementos;
  Diccionario *elementos;
} _Priority;

typedef _Priority *ColaP;

/**
 * Crea una cola de prioridad de la longitud dada.
 */
ColaP cola_prioridad_crear(unsigned int);

/**
 * Determina si la cola de prioridad esta vacia
 */
int cola_prioridad_vacia(ColaP);

/**
 * Detruye la cola de prioridad.
 */
void cola_prioridad_destruir(ColaP);

/**
 * Retorna >0 si el primer operando es más prioritario que el segundo.
 * Retorna <0 si el segundo operando es más prioritario que el primero.
 * Retorna 0 si los dos operandos tienen la misma prioridad (nunca debería darse
 * este caso).
 * La palabra de mayor prioridad es la que posee la primera letra en la
 * profundidad más baja (aparece antes en la cadena que se esta analizando). En
 * caso de comenzar las dos palabras en el mismo nodo, se considera prioritaria
 * la más larga.
 */
int comparar_prioridades(Diccionario, Diccionario);

/**
 * Dado un nodo con enlace terminal, retorna la profundidad del nodo asociado a
 * la primera letra de la palabra Ejemplo: Supongamos tenemos un diccionario con
 * estas palabras:
 * -palabras
 * -la
 * Por lo tanto el nodo asociado a la segunda "a" de "palabra" (llamemoslo z)
 * tendrá un enlace terminal al nodo asociado a la "a" de "la".
 * Entonces: posicion_primera_letra(z) = 3 pues la "l" de la
 * subcadena "la" en "palabras" está en esa profundidad.
 */
int posicion_primera_letra(Diccionario);

/**
 * Retorna el elemento de mayor prioridad de la cola.
 * En caso de estar vacio retorna NULL.
 */
Diccionario cola_prioridad_top(ColaP);

/**
 * Elimina el primer elemento de mayor prioridad de la cola.
 */
void cola_prioridad_pop(ColaP);

/**
 * Dada una cola de prioridad la redimensiona al tamaño dado.
 * En caso de reducirse el tamaño se eliminaran los elementos de menor prioridad
 * si fuera necesario.
 */
void cola_prioridad_aumentar_capacidad(ColaP, int);

/**
 * Dada una cola de prioridad inicializada y un nodo lo inserta. En caso de no
 * tener espacio suficiente duplica la capacidad.
 */
void cola_prioridad_push(ColaP, Diccionario);

/**
 * Vacia la cola de prioridad.
 */
void cola_prioridad_vaciar(ColaP);

#endif