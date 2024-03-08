#ifndef _LL

#define _LL

#include <stdbool.h>
#include "item.h"

typedef struct Node Node;

/*
struct item {
    char key[255];
    int id;
};
*/

struct Node {
	item data;
	Node *next;
};

typedef struct LL LL;
struct LL {
	Node *head;
};

LL * list_create(void);
bool list_add(LL *, item *);
item * list_find(LL *, bool (*)(item *,item *), item *);

void list_destroy(LL **);
void list_remove(LL *, bool (*)(item *,item *), item *);

#endif


