#ifndef _HASH

#define _HASH 

#include "ll.h"
#include "item.h"

typedef struct Hashtable Hashtable;

struct Hashtable {
    int index;
    Node** bucket; //array of pointers to node
};

Hashtable * hash_create(void);

bool hash_put(Hashtable *, char *key, int val);

int * hash_get(Hashtable *, char *key);

void hash_destroy(Hashtable **);

#endif
