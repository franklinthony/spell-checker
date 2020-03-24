#ifndef HASHTABLE_SLL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_BUCKETS 369419	        	                  
#define MAX_STRING 100

struct Node {
    struct Node *next;
    char *key;
};

typedef struct HashTable {
    struct Node* buckets[MAX_BUCKETS];
    int numElements[MAX_BUCKETS];
} HashTable;

extern HashTable* CreateHashTable();
extern unsigned Hash(char *key);
extern void Insert(HashTable *h, char *key);
extern bool Search(HashTable *h, char *key);
extern void RemovePunctAndMakeLowerCase(char *key);

#endif // !HASHTABLE_SLL_H
