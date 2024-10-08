#include <stdio.h>
#include <stdlib.h>
#include "boyer_moore.h"

int main() {
  FILE *input;
  if ((input = fopen("in.txt", "r")) == NULL)
    return 0;

  uchar pattern[MAX_SIZE] = {'\0'};

  int c, i = 0;
  while ((c = fgetc(input)) != '\n')
    pattern[i++] = c;

  const int kpattern_length = i;

  uchar frame[MAX_SIZE] = {'\0'};
  int table[MAX_CHAR_SIZE] = {'\0'}; // Shift array.

  CreateShiftingTable(table, pattern, kpattern_length);
  BoyerMooreSearch(pattern, kpattern_length, frame, table, input);

  fclose(input);

  return EXIT_SUCCESS;
}
