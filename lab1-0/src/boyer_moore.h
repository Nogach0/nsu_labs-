#include <stdio.h>
#define MAX_SIZE 17
#define MAX_CHAR_SIZE 256

typedef unsigned char uchar;

void CreateShiftingTable(int *table, uchar *pattern, int pattern_length);
void BoyerMooreSearch(uchar *pattern, int pattern_length, uchar *frame,
                      int *table, FILE *input);
void PrintComparison(uchar *frame, uchar *pattern, int text_length,
                     int pattern_length);
