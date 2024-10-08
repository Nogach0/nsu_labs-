#ifndef LAB5_BIT_STREAM_H
#define LAB5_BIT_STREAM_H

#include "common.h"
#include <stdio.h>

typedef struct BitStream {
  FILE *file;
  unsigned char data;
  int position;
} BitStream;

BitStream *CreateBitStream(FILE *file);
void WriteBit(BitStream *stream, int bit);
void WriteByte(BitStream *stream, unsigned char byte);
int ReadBit(BitStream *stream, int *bit);
int ReadByte(BitStream *stream, unsigned char *byte);
void FlushBitStream(BitStream *stream);

#endif // LAB5_BIT_STREAM_H
