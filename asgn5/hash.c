#include "hash.h"
#include "ll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Hashtable * hash_create(){
    Hashtable *ht = (Hashtable *)malloc(sizeof(Hashtable));
    // printf("inside hash_create");
    if(ht == NULL){
        return NULL;
    }
    ht->index = 3000; //size of bucket
    unsigned int t = (unsigned int)(ht->index);
    // printf("%d", ht->index);
    ht->bucket = (Node **)malloc(sizeof(Node *) * t);
    for(int i=0; i<(int)t; i++){
        ht->bucket[i] = NULL;
    }
    return ht;
}

size_t hash(char *key){
    size_t hash;  
    int c = 0;
    while (*key != '\0') {
        c += (int)*(key++);
    }
    hash = (size_t)c%1000;
    return hash;
}

void hash_list_destroy(Node **head) {
    //printf("inside hash_list_destroy");
    while (*head != NULL) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp->data.key);  // Free the key if allocated dynamically
        free(temp);
        temp = NULL;
    }
}

bool hash_put(Hashtable *ht, char *key, int val) {
    // unsigned int i=0;
    // char * x = key;
    // printf("hash_put: [%s]\n", x);
    // while(*x != '\0'){
    //     printf("*x: [%c]\n", *x);
    //     i++;
    //     x++;
    // }
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        //printf("hash_put: failed to allocate memory\n");
        return false;
    }

    n->data.id = val;
    n->next = NULL;
    strcpy(n->data.key, key);

    //printf("hash_put: [%s][%d]\n", n->data.key, n->data.id);
    // Hash the key
    size_t hashed = hash(key);
    
       // Add the new node to the linked list in the specified bucket
    if (ht->bucket[hashed] == NULL) {
        ht->bucket[hashed] = n;
    } else {
        Node *tail = ht->bucket[hashed];
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = n;
    }

    return true;
}


int * hash_get(Hashtable *ht, char *key){
    
    //printf("hash_get: Starting...\n");
//returns a pointer to the int that is the value for that key
    if (ht == NULL || key == NULL) {
        // Handle invalid input
        return NULL;
    }
    size_t hashed = hash(key);
    Node *n = ht->bucket[hashed];
    //printf("%s\n", ht->bucket[hashed]->data.key);
    //add to bucket[hashed]->data.key
    while(n!= NULL){
    //printf("%s\n", n->data.key);
    //but this gets called. and only the first word is being input
        if(strcmp(n->data.key, key)==0){
            //this never gets called
            //printf("%s\n", n->data.key);
            return &n->data.id;
        }
        n = n->next;
    }
    //printf("There is no match for the key: %s\n ", key);
    return NULL;
}

void hash_destroy(Hashtable **ht){
    //printf("inside hash_destroy");
//frees all the memory associated with a hash table.
    if (ht == NULL || *ht == NULL) {
        // Handle invalid input
        return;
    }

    // Free the memory used by each linked list in the hash table
    for (int i = 0; i < (*ht)->index; i++) {
        hash_list_destroy(&((*ht)->bucket[i]));
    }

    // Free the memory used by the array of buckets
    free((*ht)->bucket);

    // Free the memory used by the hash table structure
    free(*ht);

    // Set the pointer to NULL to avoid dangling pointers
    *ht = NULL;
}
