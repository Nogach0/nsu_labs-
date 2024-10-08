#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int Calculator(char *input, int input_length);
void Calculate(stack_t *numbers, char operation);
int CountNumberFromDigits(char *input, int input_length, int *index);
int Priority(char c);
bool IsGoodSymbol(char c);
bool IsNumber(char c);
bool IsOperation(char c);

int main() {
    char input[MAX_INPUT_LENGTH + 1];
    int input_length = 0;

    for (int i = 0; i < MAX_INPUT_LENGTH; i++) {
        char temp;
        if (scanf("%c", &temp) != 1)
            return 0;
        if (temp == '\n')
            break;
        if (!IsGoodSymbol(temp))
            SyntaxError();

        input[i] = temp;
        input_length++;
    }

    printf("%i", Calculator(input, input_length));

    return EXIT_SUCCESS;
}

int Calculator(char *input, int input_length) {
    stack_t numbers;
    stack_t operations;
    numbers.top = -1;
    operations.top = -1;

    for (int i = 0; i < input_length; i++) {
        if (input[i] == '(') {
            Push(&operations, (int)input[i]);
        } else if (input[i] == ')') {
            if (i == 0 || input[i - 1] == '(')
                SyntaxError();

            char temp;

            // Look at all operations in brackets
            while ((temp = (char)Pop(&operations)) != '(')
                Calculate(&numbers, temp);
        } else if (IsOperation(input[i])) {
            // Calculate if there is still a stack with operations
            // and priority operation (current input[i]) is less than or equal to
            // the operation that is on the stack.
            while (!Empty(&operations) &&
                   Priority((char)Peek(&operations)) >= Priority(input[i]))

                Calculate(&numbers, (char)Pop(&operations));
            Push(&operations, (int)input[i]);
        } else if (IsNumber(input[i])) {
            // Pass &i, since we need to change i after
            // the number has passed.
            int number = CountNumberFromDigits(input, input_length, &i);
            Push(&numbers, number);
        }
    }

    while (!Empty(&operations)) {
        Calculate(&numbers, (char)Pop(&operations));
    }

    return Pop(&numbers);
}

void Calculate(stack_t *numbers, char operation) {
    int right = Pop(numbers);
    int left = Pop(numbers);

    switch (operation) {
        case '+':
            Push(numbers, left + right);
            break;
        case '-':
            Push(numbers, left - right);
            break;
        case '*':
            Push(numbers, left * right);
            break;
        case '/':
            if (right == 0) {
                printf("division by zero");
                exit(0);
            }
            Push(numbers, left / right);
            break;
        default:
            SyntaxError();
    }
}

int CountNumberFromDigits(char *input, int input_length, int *index) {
    int n = 0;
    while (*index < input_length && IsNumber(input[*index])) {
        n *= 10;
        // Char digit minus char digit 0 = normal tenth digit.
        n += input[*index] - '0';
        (*index)++;
    }
    (*index)--;
    return n;
}

int Priority(char c) {
    switch (c) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
            return -1;
    }
}

bool IsGoodSymbol(char c) { return IsNumber(c) || IsOperation(c); }

bool IsNumber(char c) { return c >= '0' && c <= '9'; }

bool IsOperation(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}
