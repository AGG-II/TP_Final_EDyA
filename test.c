#include "parser/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  Parser dic = parser_crear();
  FILE *diccionario = fopen("diccionario.txt", "r");
  FILE *oraciones = fopen("oraciones.txt", "r");
  FILE *destino = fopen("pucha.txt", "w");
  clock_t start_time = clock();
  parser_cargar_archivo(&dic, diccionario);
  parser_corregir_archivo(oraciones, dic, destino);
  parser_destruir(dic);
  clock_t end_time = clock();
  fclose(destino);
  fclose(oraciones);
  fclose(diccionario);
  double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("Execution Time: %f seconds\n", execution_time);
  return 0;
}