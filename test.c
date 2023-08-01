#include "parser/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  FILE *diccionario = fopen("diccionario.txt", "r");
  FILE *oraciones = fopen("oraciones.txt", "r");
  FILE *destino = fopen("pucha.txt", "w");
  clock_t start_time = clock();
  parser_espaciar(diccionario, oraciones, destino);
  clock_t end_time = clock();
  double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("Execution Time: %f seconds\n", execution_time);
  return 0;
}