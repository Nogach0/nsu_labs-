#include "code.h"

void GetCodes(TreeNode *root, Code *codes, unsigned long long code,
              int length) {
  if (IsLeaf(root)) {
    codes[root->symbol].code = code;
    codes[root->symbol].length = length;
    return;
  }

  GetCodes(root->left, codes, (code << 1) | 0, length + 1);
  GetCodes(root->right, codes, (code << 1) | 1, length + 1);
}

Code *MakeCodeTable(TreeNode *root) {
  Code *codes = malloc(sizeof(struct Code) * ALPHABET_SIZE);
  GetCodes(root, codes, 0, 0);
  return codes;
}

void WriteSymbol(BitStream *stream, Code *codes, unsigned char symbol) {
  for (int i = codes[symbol].length - 1; i >= 0; i--) {
    int bit = (codes[symbol].code >> i) & 1;
    WriteBit(stream, bit);
  }
}
