#include "bit_stream.h"

BitStream *CreateBitStream(FILE *file) {
  BitStream *stream = malloc(sizeof(struct BitStream));
  stream->file = file;
  stream->data = 0;
  stream->position = 0;
  return stream;
}

void WriteBit(BitStream *stream, int bit) {
  stream->data = (stream->data << 1) | bit;
  stream->position++;
  // Reached a byte.
  if (stream->position == SIZE_OF_BYTE) {
    fwrite(&stream->data, sizeof(char), 1, stream->file);
    stream->data = 0;
    stream->position = 0;
  }
}

void WriteByte(BitStream *stream, unsigned char byte) {
  for (int i = SIZE_OF_BYTE - 1; i >= 0; i--) {
    // Get bit 0 or 1.
    int bit = (byte >> i) & 1;
    WriteBit(stream, bit);
  }
}

int ReadBit(BitStream *stream, int *bit) {
  if (stream->position == 0) {
    if (fread(&stream->data, sizeof(char), 1, stream->file) != 1) {
      // Error or EOF.
      return 1;
    }
    stream->position = SIZE_OF_BYTE;
  }

  stream->position--;
  *bit = (stream->data >> stream->position) & 1;
  return 0;
}

int ReadByte(BitStream *stream, unsigned char *byte) {
  *byte = 0;
  for (int i = 0; i < SIZE_OF_BYTE; i++) {
    *byte = *byte << 1;
    int bit = 0;
    if (ReadBit(stream, &bit) != 0) {
      // Error or EOF.
      return 1;
    }
    *byte |= bit;
  }
  return 0;
}

void FlushBitStream(BitStream *stream) {
  if (stream->position > 0) {
    stream->data = stream->data << (SIZE_OF_BYTE - stream->position);
    fwrite(&stream->data, sizeof(char), 1, stream->file);
    stream->data = 0;
    stream->position = 0;
  }
}
