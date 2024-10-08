#include "rabin_karp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char template[MAX_SIZE] = {'\0'};
  char text[BUFFERSIZE] = {'\0'};

  InputTemplate(template, MAX_SIZE, stdin);
  int template_len = strlen(template) - 1;
  int template_hash = CalculateHash(template, 0, template_len);
  printf("%d\n", template_hash);

  int count = 0;

  while (fgets(text, BUFFERSIZE, stdin)) {
    int text_len = strlen(text);
    if (text[text_len - 1] == '\n')
      text_len--;

    RabinKarp(template, template_len, template_hash, text, text_len, count);
    count = count + text_len + 1;
  }

  return EXIT_SUCCESS;
}
