#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Deck {
    struct Node* front;
    struct Node* rear;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

struct Deck* createDeck() {
    struct Deck* deck = (struct Deck*)malloc(sizeof(struct Deck));
    if (deck == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    deck->front = NULL;
    deck->rear = NULL;
    return deck;
}

void insertFront(struct Deck* deck, int data) {
    struct Node* newNode = createNode(data);
    if (deck->front == NULL) {
        deck->front = newNode;
        deck->rear = newNode;
    } else {
        newNode->next = deck->front;
        deck->front->prev = newNode;
        deck->front = newNode;
    }
}

void insertRear(struct Deck* deck, int data) {
    struct Node* newNode = createNode(data);
    if (deck->rear == NULL) {
        deck->front = newNode;
        deck->rear = newNode;
    } else {
        newNode->prev = deck->rear;
        deck->rear->next = newNode;
        deck->rear = newNode;
    }
}

int deleteFront(struct Deck* deck) {
    if (deck->front == NULL) {
        printf("Deck is empty\n");
        exit(1);
    }
    int data = deck->front->data;
    struct Node* temp = deck->front;
    deck->front = deck->front->next;
    if (deck->front != NULL) {
        deck->front->prev = NULL;
    } else {
        deck->rear = NULL;
    }
    free(temp);
    return data;
}

int deleteRear(struct Deck* deck) {
    if (deck->rear == NULL) {
        printf("Deck is empty\n");
        exit(1);
    }
    int data = deck->rear->data;
    struct Node* temp = deck->rear;
    deck->rear = deck->rear->prev;
    if (deck->rear != NULL) {
        deck->rear->next = NULL;
    } else {
        deck->front = NULL;
    }
    free(temp);
    return data;
}

int main() {
    struct Deck* deck = createDeck();

    // Insert elements at front and rear
    insertFront(deck, 1);
    insertRear(deck, 2);
    insertFront(deck, 3);
    insertRear(deck, 4);

    // Delete elements from front and rear
    printf("Deleted from front: %d\n", deleteFront(deck));
    printf("Deleted from rear: %d\n", deleteRear(deck));

    // Free memory allocated for the deck
    free(deck);

    return 0;
}
