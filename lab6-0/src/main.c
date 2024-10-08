#include "avltree.h"

int main() {
  int number_vertices = 0;
  if (scanf("%d", &number_vertices) != 1)
    return 0;

  if (number_vertices == 0) {
    puts("0");
    return 0;
  }

  Tree *root = NULL;
  Tree *arr = (Tree *)malloc(sizeof(Tree) * number_vertices);
  for (int i = 0; i < number_vertices; i++) {
    int value = 0;
    if (scanf("%d", &value) != 1) {
      return 0;
    }

    InitializeNewNode(arr, i, value);
    root = Insert(&arr[i], root, value);
  }
  printf("%d", root->height);
  free(arr);

  return 0;
}
