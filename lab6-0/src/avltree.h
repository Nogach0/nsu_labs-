#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
  int value;
  int height;
  struct Tree *left;
  struct Tree *right;
} Tree;

Tree *RotateLeft(Tree *prev_node);
Tree *RotateRight(Tree *prev_node);
Tree *BalanceTree(Tree *node);
Tree *InitializeNewNode(Tree *arr, int index, int value);
Tree *Insert(Tree *arr, Tree *node, int value);

#endif /* AVLTREE_H */
