#ifndef SLIST_H
#define SLIST_H

typedef void (*FuncionDestructora)(void *dato);

typedef struct GSList {
  void *dato;
  struct GSList *previo;
  struct GSList *siguiente;
} *Nodo;

typedef struct {
  Nodo inicio;
  Nodo final;

} Lista;

typedef Lista *SList;

/**
 * Determina si la lista dada está vacía.
 */
int slist_vacio(SList);

/**
 * Crea una lista vacia.
 */
SList slist_crear();

/**
 * Agrega un nodo a una lista vacia
 */
void agregar_lista_vacia(SList, Nodo);

/**
 * Inserta un nuevo elemento al principio de la lista.
 */
void slist_push_top(SList, void *);

/**
 * Inserta un nuevo elemento al final de la lista.
 */
void slist_push_bottom(SList, void *);

/**
 * Retorna el primer elemento de la lista.
 * Si la lista esta vacia retorna NULL.
 */
void *slist_top(SList);

/**
 * Retorna el último elemento de la lista.
 * Si la lista esta vacia retorna NULL.
 */
void *slist_bottom(SList);

/**
 * Elimina el primer elemento de la lista.
 */
void slist_pop_top(SList, FuncionDestructora);

/**
 * Elimina el último elemento de la lista.
 */
void slist_pop_bottom(SList, FuncionDestructora);

/**
 * Destruye la lista.
 */
void slist_destruir(SList, FuncionDestructora);

#endif