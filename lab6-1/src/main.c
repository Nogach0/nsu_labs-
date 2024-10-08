#include "RBTree.h"

int main() {
  int number_vertices = 0;
  if (scanf("%d", &number_vertices) != 1)
    return 0;

  if (number_vertices == 0) {
    printf("0");
    return 0;
  }

  Node *root = NULL;
  Node *arr = (Node *)malloc(sizeof(Node) * number_vertices);
  for (int i = 0; i < number_vertices; i++) {
    int value = 0;
    if (scanf("%d", &value) != 1)
      return 0;

    CreateNode(value, arr, i);
    root = InsertNode(root, value, &arr[i]);
  }
  root->color = BLACK;

  printf("%d", GetHeightTree(root) + 1);
  free(arr);
  return 0;
}
