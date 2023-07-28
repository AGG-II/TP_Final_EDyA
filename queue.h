/**
 * Esta implementación de cola fue creada para los nodos de la estructura
 * "Diccionario" definida en los archivos "trie.h" y "trie.c" por lo tanto se
 * asume que se almacenaran datos de este tipo en la cola y no se libera el
 * contenido de la cola cada vez que se haga uso de la función "pop".
 * La liberación de la memoria se realizará mediante la función definida para la
 * estructura "Diccionario".
 */

#ifndef QUEUE_H
#define QUEUE_H

typedef struct GSList {
  void *dato;
  struct GSList *siguiente;
} _Cola;

typedef _Cola *NodoCola;

typedef struct _Queue {
  NodoCola inicio;
  NodoCola final;
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
 * Crea un nodo de la cola.
 */
NodoCola crear_nodo(void *);

/**
 * Crea una cola vacia.
 */
Queue crear_queue();

/**
 * Inserta un nuevo elemento en la cola.
 */
void queue_push(Queue *, void *);

/**
 * Retorna el primer elemento de la cola.
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