#include "compression.h"

int *CreateFrequencyTable(FILE *input) {
  int *frequency = calloc(ALPHABET_SIZE, sizeof(int));

  while (!feof(input)) {
    unsigned char current_symbol = fgetc(input);
    // To avoid reading the empty EOF character.
    if (feof(input)) {
      break;
    }

    frequency[current_symbol]++;
  }

  return frequency;
}

void Encode(FILE *raw, FILE *zipped) {
  if (fgetc(raw) == EOF)
    return;

  fseek(raw, 1, SEEK_SET);

  int *frequency = CreateFrequencyTable(raw);
  Queue *queue = CreateQueue();

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (frequency[i] != 0) {
      TreeNode *new_node = CreateTreeNode(i, frequency[i], NULL, NULL);
      Push(queue, new_node);
    }
  }

  TreeNode *root = CreateTree(queue);
  Code *codes = MakeCodeTable(root);

  fwrite(&root->frequency, sizeof(int), 1, zipped);
  BitStream *stream = CreateBitStream(zipped);
  WriteTree(root, stream);

  fseek(raw, 1, SEEK_SET);

  while (!feof(raw)) {
    unsigned char symbol = fgetc(raw);
    if (feof(raw)) {
      break;
    }
    WriteSymbol(stream, codes, symbol);
  }
  // Remaining bits;
  FlushBitStream(stream);

  FreeTree(root);
  free(codes);
  free(frequency);
  DestroyQueue(queue);
  free(stream);
}

void Decode(FILE *zipped, FILE *unzipped) {
  if (fgetc(zipped) == EOF)
    return;

  fseek(zipped, 1, SEEK_SET);

  BitStream *stream = CreateBitStream(zipped);
  int length = 0;
  if (fread(&length, sizeof(int), 1, zipped) != 1)
    return;

  TreeNode *root = ReadTree(stream);

  for (int i = 0; i < length; i++) {
    unsigned char symbol;
    ReadSymbol(root, stream, &symbol);
    fwrite(&symbol, sizeof(char), 1, unzipped);
  }

  FreeTree(root);
  free(stream);
}
