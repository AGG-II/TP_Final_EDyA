#include "trie.h"
#include <stdio.h>

void print_tree_aux(Diccionario tree, int is_left, int *open_levels,
                    int num_levels, char letra) {

  for (int i = 0; i < num_levels; i++)
    printf("%s", open_levels[i] ? "│  " : "   ");
  printf("%s ", is_left ? "└─" : "│─");
  printf("%c %s\n", letra, tree->letraFinal == FINAL ? "<-" : "");

  int mas_izquierda = 0, condicion = 0;
  for (int i = 0; !condicion && i < 26; i++) {
    if (tree->siguientes[i]) {
      mas_izquierda = i;
      condicion = 1;
    }
  }
  if (!condicion) return;

  num_levels++;
  open_levels[num_levels] = 1;
  for (int i = 25; i >= 0; i--) {
    if (tree->siguientes[i]) {
      if (i != mas_izquierda)
        print_tree_aux(tree->siguientes[i], 0, open_levels, num_levels,
                       (char)97 + i);
      else {
        open_levels[num_levels] = 0;
        print_tree_aux(tree->siguientes[i], 1, open_levels, num_levels,
                       (char)97 + i);
      }
    }
  }
}

void print_tree(Diccionario tree) {
  if (!tree) {
    printf("(nil)\n");
    return;
  };

  int open_levels[50] = {1};
  int mas_izquierda = 0, condicion = 0;
  for (int i = 0; !condicion && i < 26; i++) {
    if (tree->siguientes[i]) {
      mas_izquierda = i;
      condicion = 1;
    }
  }
  if (!condicion) return;

  for (int i = 25; i >= 0; i--) {
    if (tree->siguientes[i]) {
      if (i != mas_izquierda)
        print_tree_aux(tree->siguientes[i], 0, open_levels, 0, (char)97 + i);
      else {
        open_levels[0] = 0;
        print_tree_aux(tree->siguientes[i], 1, open_levels, 0, (char)97 + i);
      }
    }
  }
}