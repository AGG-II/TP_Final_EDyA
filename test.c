#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Parser dic = NULL;
  FILE *diccionario = fopen("diccionario.txt", "r");
  parser_cargar_archivo(&dic, diccionario);
  fclose(diccionario);
  parser_corregir_archivo("oraciones.txt", dic, "recemos.txt");
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