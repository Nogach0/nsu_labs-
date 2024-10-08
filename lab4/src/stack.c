#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void SyntaxError() {
    printf("syntax error");
    exit(0);
}

void Push(stack_t *stack, int value) {
    stack->top++;
    stack->data[stack->top] = value;
}

bool Empty(stack_t *stack) { return stack->top < 0; }

int Pop(stack_t *stack) {
    if (Empty(stack)) {
        SyntaxError();
    }
    return stack->data[stack->top--]; // first take the element, then do -1
}

int Peek(stack_t *stack) {
    if (Empty(stack)) {
        SyntaxError();
    }
    return stack->data[stack->top];
}
