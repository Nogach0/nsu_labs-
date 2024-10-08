#ifndef LAB5_TREE_H
#define LAB5_TREE_H

#include "bit_stream.h"
#include "common.h"

struct Queue;

typedef struct TreeNode {
  unsigned char symbol;
  int frequency;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

int IsLeaf(TreeNode *node);
TreeNode *CreateTreeNode(unsigned char symbol, int frequency, TreeNode *left,
                         TreeNode *right);
TreeNode *CreateTree(struct Queue *queue);
void WriteTree(TreeNode *root, BitStream *stream);
TreeNode *ReadTree(BitStream *stream);
int ReadSymbol(TreeNode *root, BitStream *stream, unsigned char *symbol);
void FreeTree(TreeNode *root);

#endif // LAB5_TREE_H
