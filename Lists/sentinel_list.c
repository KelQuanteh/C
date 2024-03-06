#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Stack {
    struct Node* sentinel;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    stack->sentinel = (struct Node*)malloc(sizeof(struct Node));
    if (stack->sentinel == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    stack->sentinel->next = NULL; // Initially, the sentinel doesn't point to any node
    return stack;
}

void push(struct Stack* stack, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = stack->sentinel->next;
    stack->sentinel->next = newNode;
}

int pop(struct Stack* stack) {
    if (stack->sentinel->next == NULL) {
        printf("Stack is empty\n");
        exit(1);
    }
    struct Node* top = stack->sentinel->next;
    int data = top->data;
    stack->sentinel->next = top->next;
    free(top);
    return data;
}

int peek(struct Stack* stack) {
    if (stack->sentinel->next == NULL) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack->sentinel->next->data;
}

int main() {
    struct Stack* stack = createStack();

    push(stack, 1);
    push(stack, 2);
    push(stack, 3);

    printf("Top element: %d\n", peek(stack));

    printf("Popping elements: ");
    while (stack->sentinel->next != NULL) {
        printf("%d ", pop(stack));
    }
    printf("\n");

    // Free memory allocated for the stack and sentinel
    free(stack->sentinel);
    free(stack);

    return 0;
}
