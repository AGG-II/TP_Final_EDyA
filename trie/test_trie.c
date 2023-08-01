#include "test_trie.h"
#include <stdio.h>
#include <stdlib.h>

void test_posicion_asociada() {

  assert(posicion_asociada('a') == 0);
  assert(posicion_asociada('b') == 1);
  assert(posicion_asociada('c') == 2);
  assert(posicion_asociada('d') == 3);
  assert(posicion_asociada('e') == 4);
  assert(posicion_asociada('f') == 5);
  assert(posicion_asociada('g') == 6);
  assert(posicion_asociada('h') == 7);
  assert(posicion_asociada('i') == 8);
  assert(posicion_asociada('j') == 9);
  assert(posicion_asociada('k') == 10);
  assert(posicion_asociada('l') == 11);
  assert(posicion_asociada('m') == 12);
  assert(posicion_asociada('n') == 13);
  assert(posicion_asociada('o') == 14);
  assert(posicion_asociada('p') == 15);
  assert(posicion_asociada('q') == 16);
  assert(posicion_asociada('r') == 17);
  assert(posicion_asociada('s') == 18);
  assert(posicion_asociada('t') == 19);
  assert(posicion_asociada('u') == 20);
  assert(posicion_asociada('v') == 21);
  assert(posicion_asociada('w') == 22);
  assert(posicion_asociada('x') == 23);
  assert(posicion_asociada('y') == 24);
  assert(posicion_asociada('z') == 25);
}

void test_diccionario_siguiente_estado() {
  Diccionario raiz = diccionario_crear();
  // creamos una posicion para la h
  Diccionario primeraPos = diccionario_crear();
  raiz->siguientes[7] = primeraPos;
  // creamos una posicion para la o
  Diccionario segundaPos = diccionario_crear();
  primeraPos->siguientes[14] = segundaPos;
  // creamos una posicion para la l
  Diccionario terceraPos = diccionario_crear();
  segundaPos->siguientes[11] = terceraPos;
  // creamos una posicion para la a
  Diccionario cuartaPos = diccionario_crear();
  terceraPos->siguientes[0] = cuartaPos;

  assert(diccionario_siguiente_estado(raiz, 'a') == NULL);
  assert(diccionario_siguiente_estado(raiz, 'h') == primeraPos);

  assert(diccionario_siguiente_estado(primeraPos, 'b') == NULL);
  assert(diccionario_siguiente_estado(primeraPos, 'o') == segundaPos);

  assert(diccionario_siguiente_estado(segundaPos, 'c') == NULL);
  assert(diccionario_siguiente_estado(segundaPos, 'l') == terceraPos);

  assert(diccionario_siguiente_estado(terceraPos, 'd') == NULL);
  assert(diccionario_siguiente_estado(terceraPos, 'a') == cuartaPos);
  diccionario_destruir(raiz);
}

void test_crear_siguiente_estado() {
  Diccionario raiz = diccionario_crear();
  // creamos lugar para la h
  assert(diccionario_vacio(raiz->siguientes[7]));
  Diccionario primeraPos = crear_siguiente_estado(raiz, 'h');
  assert(primeraPos == raiz->siguientes[7]);

  // creamos lugar para la o
  assert(diccionario_vacio(primeraPos->siguientes[14]));
  Diccionario segundaPos = crear_siguiente_estado(primeraPos, 'o');
  assert(segundaPos == primeraPos->siguientes[14]);

  // creamos lugar para la l
  assert(diccionario_vacio(primeraPos->siguientes[11]));
  Diccionario terceraPos = crear_siguiente_estado(segundaPos, 'l');
  assert(terceraPos == segundaPos->siguientes[11]);

  // creamos lugar para la a
  assert(diccionario_vacio(primeraPos->siguientes[0]));
  Diccionario cuartaPos = crear_siguiente_estado(terceraPos, 'a');
  assert(cuartaPos == terceraPos->siguientes[0]);

  diccionario_destruir(raiz);
}

void test_diccionario_agregar_palabra() {
  Diccionario trie = diccionario_crear();
  diccionario_agregar_palabra(&trie, "hola");
  // checkeamos la h
  assert(!diccionario_vacio(trie->siguientes[7]));
  Diccionario letraSiguiente = trie->siguientes[7];
  assert(letraSiguiente->letraFinal == NO_FINAL);
  // checkeamos la o
  assert(!diccionario_vacio(letraSiguiente->siguientes[14]));
  letraSiguiente = letraSiguiente->siguientes[14];
  assert(letraSiguiente->letraFinal == NO_FINAL);
  // checkeamos la l
  assert(!diccionario_vacio(letraSiguiente->siguientes[11]));
  letraSiguiente = letraSiguiente->siguientes[11];
  assert(letraSiguiente->letraFinal == NO_FINAL);
  // checkeamos la a
  assert(!diccionario_vacio(letraSiguiente->siguientes[0]));
  letraSiguiente = letraSiguiente->siguientes[0];
  assert(letraSiguiente->letraFinal == FINAL);

  // convertimos la h en final de palabra
  diccionario_agregar_palabra(&trie, "h");
  assert(!diccionario_vacio(trie->siguientes[7]));
  letraSiguiente = trie->siguientes[7];
  assert(letraSiguiente->letraFinal == FINAL);

  // convertimos la o en final de palabra
  diccionario_agregar_palabra(&trie, "ho");
  assert(!diccionario_vacio(letraSiguiente->siguientes[14]));
  letraSiguiente = letraSiguiente->siguientes[14];
  assert(letraSiguiente->letraFinal == FINAL);

  diccionario_destruir(trie);
}

void test_diccionario_algoritmo_Aho_Corasick() {
  Diccionario raiz = diccionario_crear();
  Diccionario primeraPosH, segundaPosO, terceraPosL, cuartaPosA;
  Diccionario primeraPosO, segundaPosL, terceraPosA;
  diccionario_agregar_palabra(&raiz, "hola");
  diccionario_agregar_palabra(&raiz, "ol");
  diccionario_agregar_palabra(&raiz, "ola");
  diccionario_algoritmo_Aho_Corasick(raiz);

  primeraPosH = raiz->siguientes[7];
  segundaPosO = primeraPosH->siguientes[14];
  terceraPosL = segundaPosO->siguientes[11];
  cuartaPosA = terceraPosL->siguientes[0];

  primeraPosO = raiz->siguientes[14];
  segundaPosL = primeraPosO->siguientes[11];
  terceraPosA = segundaPosL->siguientes[0];

  // ckeckeamos los enlaces de fallo
  assert(raiz->enlaceFallo == raiz);
  assert(primeraPosH->enlaceFallo == raiz);
  assert(segundaPosO->enlaceFallo == primeraPosO);
  assert(terceraPosL->enlaceFallo == segundaPosL);
  assert(cuartaPosA->enlaceFallo == raiz);
  assert(primeraPosO->enlaceFallo == raiz);
  assert(segundaPosL->enlaceFallo == raiz);
  assert(terceraPosA->enlaceFallo == raiz);

  // checkeamos los enlaces terminales
  assert(raiz->enlaceTerminal == NULL);
  assert(primeraPosH->enlaceTerminal == NULL);
  assert(segundaPosO->enlaceTerminal == NULL);
  assert(terceraPosL->enlaceTerminal == segundaPosL);
  assert(cuartaPosA->enlaceTerminal == NULL);
  assert(primeraPosO->enlaceTerminal == NULL);
  assert(segundaPosL->enlaceTerminal == NULL);
  assert(terceraPosA->enlaceTerminal == NULL);

  diccionario_destruir(raiz);
}

int main() {
  test_posicion_asociada();
  test_diccionario_siguiente_estado();
  test_crear_siguiente_estado();
  test_diccionario_agregar_palabra();
  test_diccionario_algoritmo_Aho_Corasick();
  printf("Yupi!");
  return 0;
}