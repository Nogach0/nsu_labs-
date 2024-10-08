#include "avltree.h"

int Max(int h1, int h2) { 
  return h1 > h2 ? h1 : h2; 
}

int GetHeight(Tree *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

int UpdateHeight(Tree *node) {
  node->height = 1 + Max(GetHeight(node->left), GetHeight(node->right));
  return node->height;
}

int GetBalance(Tree *node) {
  if (node == NULL)
    return 0;
  return GetHeight(node->left) - GetHeight(node->right);
}

Tree *RotateLeft(Tree *prev_node) {
  Tree *new_node = prev_node->right;
  prev_node->right = new_node->left;
  new_node->left = prev_node;

  prev_node->height =
      1 + Max(GetHeight(prev_node->left), GetHeight(prev_node->right));
  new_node->height =
      1 + Max(GetHeight(new_node->left), GetHeight(new_node->right));

  return new_node;
}

Tree *RotateRight(Tree *prev_node) {
  Tree *new_node = prev_node->left;
  prev_node->left = new_node->right;
  new_node->right = prev_node;

  prev_node->height =
      1 + Max(GetHeight(prev_node->left), GetHeight(prev_node->right));
  new_node->height =
      1 + Max(GetHeight(new_node->left), GetHeight(new_node->right));

  return new_node;
}

Tree *BalanceTree(Tree *node) {
  UpdateHeight(node);
  int balance_factor = GetBalance(node);
  if (balance_factor > 1) {
    if (GetBalance(node->left) == -1)
      node->left = RotateLeft(node->left);

    node = RotateRight(node);
  } else if (balance_factor < -1) {
    if (GetBalance(node->right) == 1)
      node->right = RotateRight(node->right);

    node = RotateLeft(node);
  }
  return node;
}

Tree *InitializeNewNode(Tree *arr, int index, int value) {
  arr[index].value = value;
  arr[index].height = 1;
  arr[index].left = NULL;
  arr[index].right = NULL;
  return &arr[index];
}

Tree *Insert(Tree *arr, Tree *node, int value) {
  if (node == NULL) {
    return InitializeNewNode(arr, 0, value);
  } else if (value <= node->value) {
    node->left = Insert(arr, node->left, value);
  } else if (value >= node->value) {
    node->right = Insert(arr, node->right, value);
  }
  node->height = UpdateHeight(node);
  return BalanceTree(node);
}
