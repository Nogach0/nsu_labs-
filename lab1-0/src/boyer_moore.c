#include "boyer_moore.h"
#include <stdio.h>

void CreateShiftingTable(int *table, uchar *pattern, int pattern_length) {
  for (int i = 0; i <= MAX_CHAR_SIZE - 1; i++)
    table[i] = pattern_length;
  for (int i = 0; i < pattern_length - 1; i++)
    table[(int)pattern[i]] = pattern_length - i - 1;
}

void BoyerMooreSearch(uchar *pattern, int pattern_length, uchar *frame,
                      int *table, FILE *input) {
  int c;
  int text_length = 0;

  while (text_length < pattern_length) {
    if ((c = fgetc(input)) == EOF)
      return;
    frame[text_length++] = c;
  }
  // Comparisons for the first fragment.
  PrintComparison(frame, pattern, text_length, pattern_length);

  while (!feof(input)) { // Until the end of the file is reached.
    int shift = table[(int)frame[pattern_length - 1]];

    for (int i = 0; i < pattern_length - shift; i++)
      frame[i] = frame[i + shift];

    // Filling the rest of the fragment with new characters
    for (int i = pattern_length - shift; i < pattern_length; i++) {
      if ((c = fgetc(input)) == EOF)
        return;
      frame[i] = c;
    }
    // Update text length and compare output
    text_length += shift;
    PrintComparison(frame, pattern, text_length, pattern_length);
  }
}

void PrintComparison(uchar *frame, uchar *pattern, int text_length,
                     int pattern_length) {
  for (int i = 0; i < pattern_length; i++) {
    printf("%d ", text_length - i);
    if (pattern[pattern_length - i - 1] != frame[pattern_length - i - 1])
      return;
  }
}
