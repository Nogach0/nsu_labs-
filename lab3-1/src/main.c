#include <stdio.h>
#include <stdlib.h>

void Swap(int *a, int *b);
void QuickSort(int *num_char, int start, int end);

int main() {
    int size = 0;

    if (scanf("%d", &size) != 1) {
        printf("Bad input");
        return 0;
    }

    int *num_char = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        if (scanf("%d", &num_char[i]) != 1) {
            printf("Bad input");
            return 0;
        }
    }

    QuickSort(num_char, 0, size - 1);

    for (int i = 0; i < size; i++) {
        printf("%d ", num_char[i]);
    }

    free(num_char);

    return EXIT_SUCCESS;
}

void QuickSort(int *num_char, int start, int end) {
    if (end <= start) {
        return;
    }
    int i = start;
    int j = end;
    int pivot = num_char[(start + end) / 2];

    while (i <= j) {
        while (num_char[i] < pivot) {
            i++;
        }
        while (pivot < num_char[j]) {
            j--;
        }
        if (i <= j) {
            Swap(&num_char[i], &num_char[j]);
            i++;
            j--;
        }
    }

    QuickSort(num_char, start, j);
    QuickSort(num_char, i, end);
}

void Swap(int *a, int *b) {
    if (*a != *b) {
        int value = *a;
        *a = *b;
        *b = value;
    }
}
