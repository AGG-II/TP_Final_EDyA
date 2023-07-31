#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Diccionario dic = diccionario_crear();
  // clock_t start_time = clock();
  diccionario_agregar_palabra(&dic, "Remesurar");
  diccionario_agregar_palabra(&dic, "hermesurar");
  diccionario_agregar_palabra(&dic, "A");
  diccionario_agregar_palabra(&dic, "La");
  diccionario_agregar_palabra(&dic, "Alah");
  diccionario_agregar_palabra(&dic, "Mesura");
  diccionario_agregar_palabra(&dic, "Emocion");
  diccionario_agregar_palabra(&dic, "Alabar");
  FILE *archivo = fopen("recemos.txt", "w");
  Parser miParser = dic;
  diccionario_agregar_palabra(&dic, "deposito");
  diccionario_agregar_palabra(&dic, "dolar");
  diccionario_agregar_palabra(&dic, "dolares");
  diccionario_agregar_palabra(&dic, "es");
  diccionario_agregar_palabra(&dic, "quien");
  diccionario_agregar_palabra(&dic, "recibira");
  diccionario_algoritmo_Aho_Corasick(dic);
  corregir_oracion(miParser, "qAAlahAlabarRemesuraqwerty", archivo);
  corregir_oracion(miParser, "qAAlahAlabarRemesura", archivo);
  corregir_oracion(miParser, "quiendepositodolaresrecibiradolares", archivo);
  corregir_oracion(miParser, "quienwdepositodolareszxrecibiradolaress",
                   archivo);
  fclose(archivo);
  diccionario_destruir(dic);
  /*clock_t end_time = clock();
double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
printf("Execution Time: %f seconds\n", execution_time);
start_time = clock();
diccionario_algoritmo_Aho_Corasick(dic);
end_time = clock();
execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
printf("Execution Time: %f seconds\n", execution_time);
start_time = clock();
diccionario_destruir(dic);
end_time = clock();
execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
printf("Execution Time: %f seconds\n", execution_time);*/
  return 0;
}