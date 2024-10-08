#ifndef LAB5_CODE_H
#define LAB5_CODE_H

#include "common.h"
#include "tree.h"

typedef struct Code {
  unsigned long long code;
  unsigned int length;
} Code;

void GetCodes(TreeNode *root, Code *codes, unsigned long long code, int length);
Code *MakeCodeTable(TreeNode *root);
void WriteSymbol(BitStream *stream, Code *codes, unsigned char symbol);

#endif // LAB5_CODE_H
