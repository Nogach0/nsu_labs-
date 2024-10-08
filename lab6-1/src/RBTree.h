#ifndef RBTREE_H
#define RBTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum Color {
  RED,
  BLACK,
} Color;

typedef struct Node {
  int value;
  Color color;
  struct Node *left;
  struct Node *right;
} Node;

Node *CreateNode(int value, Node *arr, int counter);
Node *InsertNode(Node *root, int value, Node *arr);
int GetHeightTree(Node *root);

#endif /* RBTREE_H */
