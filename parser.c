#include "parser.h"
#include <string.h>

Parser parser_crear() {
  Parser retorno = diccionario_crear();
  return retorno;
}

void parser_destruir(Parser destruir) { diccionario_destruir(destruir); }

int parser_vacio(Parser par) { return diccionario_vacio(par); }

void parser_cargar_archivo(Parser *par, FILE *fuente) {
  if (parser_vacio(*par)) *par = parser_crear();
  diccionario_agregar_archivo(par, fuente);
  diccionario_algoritmo_Aho_Corasick(*par);
}

int obtener_oracion(FILE *fuente, char *destino) {
  char *resultado = fgets(destino, sizeof(char) * BUFFER, fuente);
  int i = 0;
  if (resultado != NULL) {
    for (; resultado[i] != '\r' && resultado[i] != '\0'; i++)
      ;
    if (resultado[i] == '\r') resultado[i] = '\0';
  }
  return resultado != NULL;
}

void corregir_oracion(Parser par, char *oracion, FILE *destino) {
  SList intervalos = procesar_oracion(par, oracion);
  cargar_resultados(intervalos, oracion, destino);
}

void parser_corregir_archivo(const char *fuente, Parser par,
                             const char *objetivo) {
  char oracion[BUFFER];
  FILE *oraciones = fopen(fuente, "r");
  if (oraciones == NULL) {
    printf("No se pudo abrir el archivo \"%s\"", fuente);
    return;
  }
  FILE *correcciones = fopen(objetivo, "w");
  if (correcciones == NULL) {
    fclose(oraciones);
    printf("No se pudo crear el archivo \"%s\"", objetivo);
    return;
  }
  while (obtener_oracion(oraciones, oracion)) {
    corregir_oracion(par, oracion, correcciones);
  }
  fclose(oraciones);
  fclose(correcciones);
}

void agregar_intervalo(Intervalo nuevo, SList enlaces) {
  Intervalo ultimoAgregado = slist_top(enlaces);
  // Mientras haya en la lista elementos de menor prioridad que el enlace que se
  // quiere agregar
  while (!slist_vacio(enlaces) &&
         intervalo_comparar(nuevo, ultimoAgregado) > 0) {
    slist_pop_top(enlaces, (FuncionDestructora)intervalo_destruir);
    ultimoAgregado = slist_top(enlaces);
  }
  slist_push_top(enlaces, nuevo);
}

int posicion_inicial(Parser terminal, int posicionFinal) {
  int profFinal = terminal->enlaceTerminal->profundidad;
  return posicionFinal - profFinal + 1;
}

void agregar_enlace(int inicio, int final, SList intervalos) {
  Intervalo enlace = intervalo_crear(inicio, final);
  agregar_intervalo(enlace, intervalos);
}

SList procesar_oracion(Parser raiz, char *oracion) {
  SList retorno = slist_crear();
  Parser siguiente;
  int inicioPalabra;
  for (int i = 0; oracion[i] != '\0'; i++) {
    siguiente = diccionario_siguiente_estado(raiz, oracion[i]);
    if (diccionario_vacio(siguiente)) {
      if (raiz->profundidad == 0) {
        siguiente = raiz;
      } else {
        siguiente = raiz->enlaceFallo;
        i--;
      }
    } else if (siguiente->enlaceTerminal != NULL) { // Si posee enlace terminal.
      inicioPalabra = posicion_inicial(siguiente, i);
      agregar_enlace(inicioPalabra, i, retorno);
    } else if (siguiente->letraFinal == FINAL) {
      // Si es el final de una palabra
      inicioPalabra = i - siguiente->profundidad + 1;
      agregar_enlace(inicioPalabra, i, retorno);
    }
    raiz = siguiente;
  }
  return retorno;
}

int cargar_string(Intervalo extremos, char *fuente, int offset, char *destino) {
  int inicio = extremos->inicio;
  int final = extremos->final;
  int longIntervalo = final - inicio;
  int i;
  for (i = 0; i <= longIntervalo; i++) {
    destino[offset + i] = fuente[inicio + i];
  }
  destino[offset + i] = ' ';
  return i;
}

void cargar_resultados(SList intervalosValidos, char *oracion, FILE *destino) {
  int ultPosLeida = 0, posErrores = 0, posAciertos = 0;
  int longitudOracion = strlen(oracion);
  char *aciertos = malloc(sizeof(char) * 2 * longitudOracion);
  char *errores = malloc(sizeof(char) * 2 * longitudOracion);
  Intervalo error = intervalo_crear(0, -1);
  while (!slist_vacio(intervalosValidos)) {
    Intervalo palabra = slist_bottom(intervalosValidos);
    error->inicio = ultPosLeida;
    error->final = palabra->inicio - 1;

    if (error->final >= error->inicio) // si hay un error para cargar
      posErrores += cargar_string(error, oracion, posErrores, errores) + 1;
    posAciertos += cargar_string(palabra, oracion, posAciertos, aciertos) + 1;
    ultPosLeida = palabra->final + 1;
    slist_pop_bottom(intervalosValidos, (FuncionDestructora)intervalo_destruir);
  }

  // cargamos el resto como error
  error->inicio = ultPosLeida;
  error->final = longitudOracion;
  // Cargamos el resto de la oracion como error
  if (error->inicio < error->final)
    posErrores += cargar_string(error, oracion, posErrores, errores) + 1;
  colocar_terminador(aciertos, posAciertos);
  colocar_terminador(errores, posErrores);
  cargar_oraciones(aciertos, errores, destino);
  slist_destruir(intervalosValidos, (FuncionDestructora)intervalo_destruir);
  free(aciertos);
  free(errores);
}

void colocar_terminador(char *cadena, int longitud) {
  // Reemplazamos el ultimo espacio puesto con un terminador.
  longitud = POSICION_TERMINADOR(longitud);
  cadena[longitud] = '\0';
}

void cargar_oraciones(char *aciertos, char *errores, FILE *destino) {
  if (aciertos[0] != '\0') // Hay palabras correctas
    fprintf(destino, "La oracion es: \"%s\". ", aciertos);
  else
    fprintf(destino, "No hay palabras correctas. ");
  if (errores[0] == '\0') // no hay errores
    fprintf(destino, "No se necesito recuperar de errores.\n");
  else
    fprintf(destino, "Los errores fueron: \"%s\".\n", errores);
}
