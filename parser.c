#include "parser.h"
#include <string.h>

Parser parser_crear() {
  Parser retorno = malloc(sizeof(_Parser));
  Diccionario vacio = diccionario_crear();
  ColaP vacia = crear_cola_prioridad(CANT_LETRAS);
  retorno->palabras = vacio;
  retorno->enlacesTerminales = vacia;
  return retorno;
}

void parser_destruir(Parser destruir) {
  cola_prioridad_destruir(destruir->enlacesTerminales);
  diccionario_destruir(destruir->palabras);
  free(destruir);
}

int parser_nulo(Parser par) { return par == NULL; }

void parser_cargar_archivo(Parser *par, FILE *fuente) {
  if (parser_nulo(*par)) *par = parser_crear();
  Parser analizador = *par;
  Diccionario *trie = &(analizador->palabras);
  diccionario_agregar_archivo(trie, fuente);
  diccionario_algoritmo_Aho_Corasick(*trie);
}

int obtener_oracion(FILE *fuente, char *destino) {
  char *resultado = fgets(destino, sizeof(char) * BUFFER, fuente);
  return resultado != NULL;
}

void corregir_oracion(Parser par, char *oracion, FILE *destino) {
  int caracteresCargados = 0, caracteresLeidos = 0;
  int longitudOracion = strlen(oracion);
  char aciertos[longitudOracion], errores[longitudOracion];
  while (oracion[caracteresLeidos] != '\0') {
  }
}

void parser_corregir(FILE *oraciones, Parser par, const char *objetivo) {
  char oracion[BUFFER];
  FILE *correcciones = fopen(objetivo, "w");
  while (obtener_oracion(oraciones, oracion)) {
    corregir_oracion(par, oracion, correcciones);
  }
}