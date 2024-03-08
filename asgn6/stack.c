#include "stack.h"
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct stack{
    uint32_t *items;
    uint32_t capacity;
    uint32_t top;
} Stack;

Stack *stack_create(uint32_t capacity){
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->capacity = capacity;
    s->top = 0;
    // We need enough memory for <capacity> numbers
    s->items = calloc(s->capacity, sizeof(uint32_t));
    // We created our stack, return it!
    return s;
}

void stack_free(Stack **sp){
    if (sp != NULL && *sp != NULL) {
        if ((*sp)->items) {
            free((*sp)->items);
            (*sp)->items = NULL;
        }
        free(*sp);
    }
    if (sp != NULL) {
        *sp = NULL;
    }
}

bool stack_push(Stack *s, uint32_t val){
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = val;
    s->top++;
    return true;
}

bool stack_pop(Stack *s, uint32_t *val) {
    if (stack_empty(s)) {
        return false;
    }
    s->top--;
    *val = s->items[s->top];
    return true;
}

bool stack_peek(const Stack *s, uint32_t *val) {
    if (stack_empty(s)) {
        return false;
    }
    *val = s->items[s->top - 1];
    return true;
}

bool stack_empty(const Stack *s) {
    return s->top == 0;
}

bool stack_full(const Stack *s) {
    return s->top == s->capacity;
}

uint32_t stack_size(const Stack *s) {
    return s->top;
}

void stack_copy(Stack *dst, const Stack *src) {
    assert(dst->capacity >= src->top); // Ensure dst has enough capacity
    dst->top = src->top;
    // printf("inside stack_copy\n");
    for (uint32_t i = 0; i < src->top; i++) {
        dst->items[i] = src->items[i];
    }
    // printf("%u", dst->top);
}

void stack_print(const Stack *s, FILE *outfile, char *cities[]) {
    // printf("inside stack_print\n");
    printf("printout stack;\n");
    printf("%u\n", s->top);
    for (uint32_t i = 0; i < s->top; i++) {
        printf("%s\n", cities[s->items[i]]);
        fprintf(outfile, "%s\n", cities[s->items[i]]);
    }
}
