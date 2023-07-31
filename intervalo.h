#ifndef INTERVALO_H
#define INTERVALO_H

typedef struct {
  int inicio;
  int final;
} _Intervalo;

typedef _Intervalo *Intervalo;

/**
 * Crea un intervalo.
 * Se asume que el primer elemento es menor o igual al segundo.
 */
Intervalo intervalo_crear(int, int);

/**
 * Destruye un intervalo.
 */
void intervalo_destruir(Intervalo);

/**
 * Determina cual intervalo de letras es prioritario.
 * La prioridad esta definida de la siguiente forma:
 * -El intervalo que comienza antes es mas prioritario.
 * -Si los dos intervalos comienzan en el mismo punto entones el mas largo es
 * prioritario.
 * Retorna >0 si el primer intervalo es prioritario.
 * Retorna <0 si el segundo intervalo es prioritario.
 * Retorna 0 si los intervalos son iguales.
 */
int intervalo_comparar(Intervalo, Intervalo);

#endif