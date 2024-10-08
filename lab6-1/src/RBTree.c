#include "RBTree.h"

Node *CreateNode(int value, Node *arr, int counter) {
  arr[counter].value = value;
  arr[counter].color = RED;
  arr[counter].left = NULL;
  arr[counter].right = NULL;

  return &arr[counter];
}

void SwapColor(Node *node) {
  node->color = (node->color == RED) ? BLACK : RED;
  node->left->color = BLACK;
  node->right->color = BLACK;
}

Node *RotateLeft(Node *node) {
  Node *right_child = node->right;
  node->right = right_child->left;
  right_child->left = node;
  right_child->color = node->color;
  node->color = RED;
  return right_child;
}

Node *RotateRight(Node *node) {
  Node *left_child = node->left;
  node->left = left_child->right;
  left_child->right = node;
  left_child->color = node->color;
  node->color = RED;
  return left_child;
}

int IsRed(Node *node) {
  if (node == NULL)
    return 0;

  return node->color == RED;
}

Node *BalanceInsertion(Node *node) {
  if (IsRed(node->left) && IsRed(node->right) &&
      (IsRed(node->left->left) || IsRed(node->left->right) ||
       IsRed(node->right->left) || IsRed(node->right->right))) {
    SwapColor(node);
  }

  if (IsRed(node->right)) {
    node = RotateLeft(node);
  }

  if (IsRed(node->left) && IsRed(node->left->left)) {
    node = RotateRight(node);
  }

  return node;
}

Node *InsertNode(Node *root, int value, Node *arr) {
  if (root == NULL)
    return CreateNode(value, arr, 0);

  if (value < root->value) {
    root->left = InsertNode(root->left, value, arr);
  } else if (value > root->value) {
    root->right = InsertNode(root->right, value, arr);
  }

  return BalanceInsertion(root);
}

int GetHeightTree(Node *root) {
  int count = 0;
  Node *tmp = root;
  while (tmp) {
    if (tmp->color == BLACK) {
      count++;
    }
    tmp = tmp->right;
  }
  return count;
}
