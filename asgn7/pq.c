#include"pq.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct ListElement ListElement;
struct ListElement {
    Node *tree;
    ListElement *next;
};

struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *newQueue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (newQueue == NULL) {
        return NULL; // Allocation error
    }

    newQueue->list = NULL;

    return newQueue;
}

void pq_free(PriorityQueue **q) {
    if (*q != NULL) {
        free(*q);
        *q = NULL;
    }
}

bool pq_is_empty(PriorityQueue *q) {
    return q->list == NULL;
}

bool pq_size_is_1(PriorityQueue *q) {
    return q->list != NULL && q->list->next == NULL;
}

bool pq_less_than(ListElement *e1, ListElement *e2) {
    if (e1->tree->weight < e2->tree->weight) {
        return true;
    } else if (e1->tree->weight == e2->tree->weight) {
        return e1->tree->symbol < e2->tree->symbol;
    }

    return false;
}

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *newElement = (ListElement *)malloc(sizeof(ListElement));
    if (newElement == NULL) {
        exit(EXIT_FAILURE); // Allocation error
    }

    newElement->tree = tree;
    newElement->next = NULL;

    if (q->list == NULL || pq_less_than(newElement, q->list)) {
        newElement->next = q->list;
        q->list = newElement;
    } else {
        ListElement *current = q->list;
        while (current->next != NULL && !pq_less_than(newElement, current->next)) {
            current = current->next;
        }
        newElement->next = current->next;
        current->next = newElement;
    }
}

Node *dequeue(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        fprintf(stderr, "Error: Attempted to dequeue from an empty priority queue.\n");
        exit(EXIT_FAILURE);
    }

    Node *tree = q->list->tree;
    ListElement *temp = q->list;
    q->list = q->list->next;
    free(temp);

    return tree;
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    
    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        
        node_print_tree(e->tree);
        e = e->next;
    }

    printf("=============================================\n");
}
