#include "queue.h"
#include "tree.h"

int IsLeaf(TreeNode *node) { return !node->left; }

TreeNode *CreateTreeNode(unsigned char symbol, int frequency, TreeNode *left,
                         TreeNode *right) {
  TreeNode *new_node = malloc(sizeof(TreeNode));

  new_node->symbol = symbol;
  new_node->frequency = frequency;
  new_node->left = left;
  new_node->right = right;

  return new_node;
}

TreeNode *CreateTree(Queue *queue) {
  while (queue->front->next != NULL) {
    TreeNode *left = Delete(queue);
    TreeNode *right = Delete(queue);

    TreeNode *new_node =
        CreateTreeNode(0, left->frequency + right->frequency, left, right);

    Push(queue, new_node);
  }

  return Delete(queue);
}

void WriteTree(TreeNode *root, BitStream *stream) {
  if (IsLeaf(root)) {
    // 1 bit for leaf node.
    WriteBit(stream, 1);
    // Leaf symbol.
    WriteByte(stream, root->symbol);
    return;
  }
  // Write bit 0 for the internal node.
  WriteBit(stream, 0);
  WriteTree(root->left, stream);
  WriteTree(root->right, stream);
}

TreeNode *ReadTree(BitStream *stream) {
  int bit = 0;
  ReadBit(stream, &bit);

  if (bit == 1) {
    unsigned char byte = 0;
    ReadByte(stream, &byte);

    return CreateTreeNode(byte, 0, NULL, NULL);
  }
  TreeNode *left = ReadTree(stream);
  TreeNode *right = ReadTree(stream);
  return CreateTreeNode(0, 0, left, right);
}

int ReadSymbol(TreeNode *root, BitStream *stream, unsigned char *symbol) {
  TreeNode *current_node = root;
  while (!IsLeaf(current_node)) {
    int bit = 0;
    ReadBit(stream, &bit);

    if (bit == 0) {
      current_node = current_node->left;
    } else {
      current_node = current_node->right;
    }
  }

  *symbol = current_node->symbol;
  return 0;
}

void FreeTree(TreeNode *root) {
  if (root == NULL) {
    return;
  }

  FreeTree(root->left);
  FreeTree(root->right);
  free(root);
}
