#include <stdio.h>
#include <stdlib.h>

void HeapSort(int num_char[], int size);
void MaxHeapify(int num_char[], int size, int buffer);
void Swap(int *swap_first, int *swap_second);

int main() {
  int size = 0;

  if (scanf("%d", &size) != 1) {
    printf("Bad input");
    return 0;
  }

  int num_char[size + 1];
  int number = 0;

  for (int i = 0; i < size; i++) {
    if (scanf("%d", &number) != 1) {
      printf("Bad input");
      return 0;
    }
    num_char[i] = number;
  }

  HeapSort(num_char, size);

  for (int i = 0; i < size; i++) {
    printf("%d ", num_char[i]);
  }

  return EXIT_SUCCESS;
}

void HeapSort(int num_char[], int size) {
  for (int buffer = size / 2 - 1; buffer >= 0; buffer--) {
    MaxHeapify(num_char, size, buffer);
  }

  for (int buffer = size - 1; buffer > 0; buffer--) {
    Swap(&num_char[0], &num_char[buffer]);
    MaxHeapify(num_char, buffer, 0);
  }
}

void MaxHeapify(int num_char[], int size, int buffer) {
  int largest = buffer;
  int left_child = 2 * buffer + 1;
  int right_child = 2 * buffer + 2;

  if (left_child < size && num_char[left_child] > num_char[largest]) {
    largest = left_child;
  }

  if (right_child < size && num_char[right_child] > num_char[largest]) {
    largest = right_child;
  }

  if (largest != buffer) {
    Swap(&num_char[buffer], &num_char[largest]);
    MaxHeapify(num_char, size, largest);
  }
}

void Swap(int *swap_first, int *swap_second) {
  int variable = *swap_first;
  *swap_first = *swap_second;
  *swap_second = variable;
}
