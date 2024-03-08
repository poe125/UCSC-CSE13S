#include "ll.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

LL * list_create(){
	LL *l = (LL *)malloc(sizeof(LL));
	if (l == NULL) {
		return NULL;
	}
	l->head = NULL;
	return l;
}

//fix this function for the Part II
bool list_add(LL *l, item *i)
{
	Node *n = (Node *)malloc(sizeof(Node));
	if (n == NULL) {
		return false;
	}
	//this must be done first
	n->data = *i;
	n->next = NULL;
	//make the node static so it remembers where it left off
	static Node *tail;

	if (l->head == NULL) {
        l->head = n;
        tail = l->head;
		return true;
	 	} else if(i->id == 0){
			tail = l->head;
		} else {
			while(tail->next != NULL){
				tail = tail->next;
			}
		}
	tail->next = n;
	//printf("%s", n->data.key);
	//printf("%d\n", n->data.id);
	return true;
}

item * list_find(LL *l, bool (*cmp)(item *,item *), item *i)
{
	//it should be in a linked list, but it's only looking at the first link
	// should be fixed
	Node *n = l->head;
        while (n != NULL) {
			if (cmp(&n->data, i)) {
				return &n->data;
			}
			n = n->next;
			}
	printf("There is no match\n");
	return NULL;
}

void list_remove(LL *l, bool (*cmp)(item *, item *), item *i) {
    Node *current = l->head;
    Node *prev = NULL;

    while (current != NULL) {
        if (cmp(&current->data, i)) { // Look for where it matches, if it does
            printf("Found the match\n");
            if (prev == NULL) {
                // If the match is at the head of the list
                printf("Is the head of the list\n");
                l->head = current->next;
                free(current);
                current = l->head; // Update current to the new head
            } else {
                prev->next = current->next;
                free(current);
                current = prev->next; // Update current to the next node
            }
            break;
        }
        prev = current;
        current = current->next;
    }
}


void list_destroy(LL **l){
	free(*l);
}

