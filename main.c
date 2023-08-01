#include "parser/parser.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Arbre el archivo, en el modo especificado con el nombre del
 */
FILE *abrir_archivo(FILE **, int, char **, char *);

int main(int argc, char **argv) {
  FILE *diccionario, *oraciones, *destino;
  if (argc != 4) {
    printf("No se pasaron todos los archivos!");
    return 1;
  }
  if (!abrir_archivo(&diccionario, 1, argv, "r")) {
    printf("No se pudo abrir el diccionario!");
    return 1;
  }
  if (!abrir_archivo(&oraciones, 2, argv, "r")) {
    printf("No se pudieron abrir las oraciones!");
    fclose(diccionario);
    return 1;
  }
  if (!abrir_archivo(&destino, 3, argv, "w")) {
    printf("No se pudo abrir el archivo destino!");
    fclose(diccionario);
    fclose(oraciones);
    return 1;
  }
  parser_espaciar(diccionario, oraciones, destino);
  fclose(diccionario);
  fclose(oraciones);
  fclose(destino);
  return 0;
}

FILE *abrir_archivo(FILE **destino, int pos, char **nombre, char *modo) {
  (*destino) = fopen(nombre[pos], modo);
  return (*destino);
}