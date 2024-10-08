#include "rabin_karp.h"
#include <stdio.h>

const int DegreesOf3[MAX_SIZE] = {
    1,    3,     9,     27,     81,     243,     729,     2187,
    6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907};

int InputTemplate(char *buffer, int size, FILE *input) {
  if (fgets(buffer, size, input) == NULL)
    return 0;
  return 1;
}

void RabinKarp(char *template, int template_len, int template_hash,
               char *input_text, int input_text_len, int count) {
  int input_text_hash = CalculateHash(input_text, 0, template_len);
  int index_of_position = 0;

  while (index_of_position < input_text_len - template_len + 1) {
    if (template_hash == input_text_hash) {
      int i = 0;
      // Runs until the end of the pattern or text is reached
      // and the characters match.
      while ((i < template_len) && (i + index_of_position < input_text_len) &&
             ((uchar) template[i] == (uchar)input_text[i + index_of_position]))
        printf("%d ", index_of_position + count + 1 + i++);
      // Checking for mismatch at the end of the pattern
      if (i < template_len)
        printf("%d ", index_of_position + count + 1 + i);
    }
    // Hash recalculation and position increase.
    input_text_hash = RecalculateHash(
        input_text_hash, input_text[index_of_position],
        input_text[index_of_position + template_len], template_len);
    index_of_position++;
  }
}

int CalculateHash(char *input_text, int begin_index_position,
                  int input_text_len) {
  int res = 0;

  for (int i = begin_index_position; i < input_text_len; i++)
    res += ((unsigned char)input_text[i] % 3) *
           DegreesOf3[i - begin_index_position];

  return res;
}
// Recalculates the hash when moving one character.
int RecalculateHash(int hash, uchar first, uchar last, unsigned int size) {
  hash -= first % 3;
  hash /= 3;
  hash += (last % 3) * DegreesOf3[size - 1];

  return hash;
}
