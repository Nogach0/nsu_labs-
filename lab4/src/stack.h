#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 1000
#define STACK_MAX_SIZE 500

typedef struct stack_t {
    int data[STACK_MAX_SIZE];
    int top;
} stack_t;

void SyntaxError();
void Push(stack_t *stack, int value);
bool Empty(stack_t *stack);
int Pop(stack_t *stack);
int Peek(stack_t *stack);
