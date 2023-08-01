#include "test_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_posicion_incial() {
  Parser par = parser_crear();
  diccionario_agregar_palabra(&par, "a");
  diccionario_agregar_palabra(&par, "al");
  diccionario_agregar_palabra(&par, "palabra");
  diccionario_algoritmo_Aho_Corasick(par);
  // obtenemos los nodos asociados a la "a" y "l" de "palabra"
  Parser aPalabra = par->siguientes[15]->siguientes[0];
  Parser lPlabra = aPalabra->siguientes[11];

  // se lee la primera "a" de "palabra" en la posicion 15
  assert(posicion_inicial(aPalabra, 15) == 15);
  // se lee la "l" de "palabra" en la posicion 37
  assert(posicion_inicial(lPlabra, 37) == 36);
  diccionario_destruir(par);
}

void test_agregar_intervalo() {
  Intervalo inter1 = intervalo_crear(1, 2);
  Intervalo inter2 = intervalo_crear(3, 4);
  Intervalo inter3 = intervalo_crear(3, 5);
  Intervalo inter4 = intervalo_crear(6, 7);
  Intervalo inter5 = intervalo_crear(1, 8);
  SList lista = slist_crear();
  // agregamos el primer intervalo
  agregar_intervalo(inter1, lista);
  assert(slist_top(lista) == inter1);

  // agregamos el segundo intervalo
  agregar_intervalo(inter2, lista);
  assert(slist_top(lista) == inter2);

  // agregamos un nuevo intervalo con mayor prioridad que el ultimo
  agregar_intervalo(inter3, lista);
  assert(slist_top(lista) == inter3);
  Intervalo penultimo = lista->inicio->siguiente->dato;
  assert(penultimo == inter1);

  // agregamos un nuevo intervalo de prioridad menor
  agregar_intervalo(inter4, lista);
  assert(slist_top(lista) == inter4);
  penultimo = lista->inicio->siguiente->dato;
  assert(inter3 == penultimo);

  // agregamos un intervalo de mayor prioridad que todos los demas
  agregar_intervalo(inter5, lista);
  assert(lista->inicio == lista->final);

  slist_destruir(lista, (FuncionDestructora)intervalo_destruir);
}

void test_procesar_oracion() {
  Parser par = parser_crear();
  diccionario_agregar_palabra(&par, "hola");
  diccionario_agregar_palabra(&par, "mundo");
  diccionario_agregar_palabra(&par, "como");
  diccionario_agregar_palabra(&par, "estas");
  diccionario_algoritmo_Aho_Corasick(par);
  SList resultado = procesar_oracion(par, "HoLaMunDoCOmorEstaSSSSS");
  Intervalo palabra1 = intervalo_crear(0, 3);
  Intervalo palabra2 = intervalo_crear(4, 8);
  Intervalo palabra3 = intervalo_crear(9, 12);
  Intervalo palabra4 = intervalo_crear(14, 18);
  assert(intervalo_comparar(palabra1, slist_bottom(resultado)) == 0);
  slist_pop_bottom(resultado, (FuncionDestructora)intervalo_destruir);

  assert(intervalo_comparar(palabra2, slist_bottom(resultado)) == 0);
  slist_pop_bottom(resultado, (FuncionDestructora)intervalo_destruir);

  assert(intervalo_comparar(palabra3, slist_bottom(resultado)) == 0);
  slist_pop_bottom(resultado, (FuncionDestructora)intervalo_destruir);

  assert(intervalo_comparar(palabra4, slist_bottom(resultado)) == 0);
  slist_pop_bottom(resultado, (FuncionDestructora)intervalo_destruir);

  assert(slist_vacio(resultado));
  diccionario_destruir(par);
  free(resultado);
}

void test_cargar_string() {
  char oracion[] = "Hola mundo!";
  char mundo[10];
  char hola[10];
  char soloMundo[] = "mundo";
  char soloHola[] = "Hola";
  Intervalo extremosMundo = intervalo_crear(5, 9);
  Intervalo extremosHola = intervalo_crear(0, 3);
  int resultado = cargar_string(extremosHola, oracion, 0, hola);
  hola[4] = '\0';
  assert(resultado == 4);
  assert(strcmp(hola, soloHola) == 0);

  resultado = cargar_string(extremosMundo, oracion, 0, mundo);
  mundo[5] = '\0';
  assert(resultado == 5);
  assert(strcmp(mundo, soloMundo) == 0);
  intervalo_destruir(extremosHola);
  intervalo_destruir(extremosMundo);
}

void test_colocar_terminador() {}

void test_parser_espaciar() {
  FILE *diccionario = fopen("../ejemplos/diccionario.txt", "r");
  FILE *oraciones = fopen("../ejemplos/oraciones.txt", "r");
  FILE *destino = fopen("../ejemplos/resultado_correccion.txt", "w");
  parser_espaciar(diccionario, oraciones, destino);
}

int main() {
  test_posicion_incial();
  test_agregar_intervalo();
  test_procesar_oracion();
  test_cargar_string();
  test_parser_espaciar();
  printf("Yupi!");
  return 0;
}