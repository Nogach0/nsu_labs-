#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define max_size 11

void Permutation(char *input_number, int p_count);
int FindIndexMinElement(const char *number, int perm_idx);
int CharCountInString(char *input_number, char character);
bool CheckForErrors(char *input_number);
void Swap(char *a, char *b);
void ReverseString(char *str, int idx);

int main() {
  char input_number[100];
  int permutations_count = 0;

  if (fgets(input_number, sizeof(input_number), stdin) == NULL)
    return 0;

  input_number[(int)strlen(input_number) - 1] = '\0';

  if (scanf("%d", &permutations_count) != 1)
    return -1;

  if (CheckForErrors(input_number)) { // If it returns true, then continue.
    Permutation(input_number, permutations_count);
  } else {
    printf("bad input");
  }

  return 0;
}

void Permutation(char *input_number, int p_count) {
  int number_length = strlen(input_number);

  for (int idx = number_length - 2; idx >= 0 && p_count != 0; idx--) {
    // Find a pair of numbers whose right
    // number is greater than left.
    if (input_number[idx] < input_number[idx + 1]) {
      // Look for the index of the minimum element that
      // greater than the left number of the pair.
      int min_idx = FindIndexMinElement(input_number, idx);

      Swap(&input_number[idx], &input_number[min_idx]);
      ReverseString(input_number, idx);

      printf("%s\n", input_number);
      idx = number_length - 1;
      p_count--;
    }
  }
}

int FindIndexMinElement(const char *number, int perm_idx) {
  int perm_val = number[perm_idx] + '0';
  int number_len = (int)strlen(number);
  int min = TMP_MAX;
  int idx = 0;

  for (int i = perm_idx + 1; i < number_len; i++) {
    // Find a number that is greater than perm_val
    // and, moreover, minimal.
    if (number[i] + '0' > perm_val && number[i] + '0' < min) {
      min = number[i] + '0';
      idx = i;
    }
  }

  return idx;
}

int CharCountInString(char *input_number, char character) {
  int count = 0;
  int number_length = strlen(input_number);

  for (int i = 0; i < number_length; i++) {
    if (input_number[i] == character)
      count++;
  }
  return count;
}

bool CheckForErrors(char *input_number) {
  for (int i = 0; i < max_size - 1; ++i) {
    if (CharCountInString(input_number, i + '0') > 1)
      return false;
  }

  int len = (int)strlen(input_number);

  for (int i = 0; i < len; ++i) {
    if (input_number[i] < '0' || input_number[i] > '9')
      return false;
  }
  return true;
}

void Swap(char *a, char *b) {
  char value = *a;
  *a = *b;
  *b = value;
}

void ReverseString(char *str, int idx) {
  int len = strlen(str);
  int j = 0;
  for (int i = idx + 1; j < (len - idx - 1) / 2; i++) {
    Swap(&str[i], &str[len - j - 1]);
    j++;
  }
}
