/**
 * Esta implementación de cola fue creada para los nodos de la estructura
 * "Diccionario" definida en los archivos "trie.h" y "trie.c" por lo tanto se
 * asume que se almacenaran datos de este tipo en la cola y no se libera el
 * contenido de la cola cada vez que se haga uso de la función "pop".
 * La liberación de la memoria se realizará mediante la función definida para la
 * estructura "Diccionario".
 */

#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H

typedef enum { LLENA, VACIA, CARGADA } Estado;

typedef struct _Queue {
  int inicio;
  int final; // contiene el indice del lugar libre a ocupar
  int capacidad;
  void **elementos;
  Estado estado;
} *Queue;

/**
 * Determina si la cola esta inicializada.
 */
int queue_nulo(Queue);

/**
 * Determina si la cola dada está vacía.
 */
int queue_vacia(Queue);

/**
 * Crea una cola vacia con capacidad para almenos un elemento.
 */
Queue crear_queue(unsigned int);

/**
 * Dada una cola duplica su capacidad.
 * Crea un array nuevo con el doble de espacio y coloca los elementos al
 * principio de la cola empezando por le tope.
 */
void duplicar_capacidad(Queue);

/**
 * Dada una posicion de la cola retorna la posicion siguiente.
 */
int siguiente_posicion(Queue cola, int posicion);

/**
 * Inserta un nuevo elemento en la cola.
 */
void queue_push(Queue *, void *);

/**
 * Agrega un elemento al final de una cola vacia.
 */
void agregar_vacia(Queue, void *);

/**
 * Duplica la capacidad de la cola llena dada y agrega el dato dado al final.
 */
void agregar_llena(Queue, void *);

/**
 * Agrega un elemento al final de una cola con elementos.
 */
void agregar_cargada(Queue, void *);

/**
 * Retorna el primer elemento de la cola.
 * Si la cola esta vacia retorna NULL.
 */
void *queue_top(Queue);

/**
 * Elimina el primer elemento de la cola.
 */
void queue_pop(Queue);

/**
 * Destruye la cola.
 */
void queue_destruir(Queue);

#endif