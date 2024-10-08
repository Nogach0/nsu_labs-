#ifndef LAB5_COMPRESSION_H
#define LAB5_COMPRESSION_H

#include "code.h"
#include "common.h"
#include "queue.h"
#include <stdio.h>

void Encode(FILE *raw, FILE *zipped);
void Decode(FILE *zipped, FILE *unzipped);

#endif // LAB5_COMPRESSION_H
