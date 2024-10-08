#include <stdio.h>
#define MAX_SIZE 18
#define BUFFERSIZE 256

typedef unsigned char uchar;

int InputTemplate(char *buffer, int size, FILE *input);
void RabinKarp(char *template, int template_len, int template_hash,
               char *input_text, int input_text_len, int count);
int CalculateHash(char *input_text, int begin_index_position,
                  int input_text_len);
int RecalculateHash(int hash, uchar first, uchar last, unsigned int size);
