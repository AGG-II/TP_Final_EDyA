/**
 * Esta implementación de pila fue creada para los nodos de la estructura
 * "Diccionario" definida en los archivos "trie.h" y "trie.c" por lo tanto se
 * asume que se almacenaran datos de este tipo en la pila y no se libera el
 * contenido de la pila cada vez que se haga uso de la función "pop".
 * La liberación de la memoria se realizará mediante la función definida para la
 * estructura "Diccionario".
 */

#ifndef STACK_H
#define STACK_H

typedef struct GSList {
  void *dato;
  struct GSList *siguiente;
} _Pila;

typedef _Pila *Stack;

/**
 * Determina si la pila dada está vacía
 */
int stack_vacio(Stack);

/**
 * Crea una pila vacia
 */
Stack crear_stack();

/**
 * Inserta un nuevo elemento en la pila
 */
void stack_push(Stack *, void *);

/**
 * Retorna el primer elemento de la pila
 */
void *stack_top(Stack);

/**
 * Elimina el primer elemento de la pila
 */
void stack_pop(Stack *);

#endif