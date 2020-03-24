#include "hashTable_sll.h"

unsigned Hash(char *key) { //String hashing from K&R's "The C Programming Language"
    unsigned hash;
    
    for (hash = 0; *key != '\0'; key++)
        hash = *key + 31 * hash;
    
    return hash % MAX_BUCKETS;
}

HashTable* CreateHashTable() {
    HashTable *h = (HashTable*) malloc (sizeof(HashTable)); 
    
    for(int i = 0; i < MAX_BUCKETS; i++) {
        h->buckets[i] = NULL;
        h->numElements[i] = 0;
    }

    return h;
}

void Insert(HashTable *hashTable, char *key) { //Using chaining probing to handle collisions.
    if (!hashTable)
        hashTable = CreateHashTable(); 
    
    unsigned hashValue = Hash(key);
   
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->key = (char*) malloc(MAX_STRING * sizeof(char));
    strcpy(newNode->key, key);
    newNode->next = NULL;

    if(!hashTable->buckets[hashValue]){
        hashTable->buckets[hashValue] = newNode;
        hashTable->numElements[hashValue]++;
    }else{ 
        struct Node* aux = hashTable->buckets[hashValue];

        while(aux->next){
            aux = aux->next; 
            //printf("%s [%d]\n", aux->key, hashValue); //Uncomment if you want to print collisions.
        }
        aux->next = newNode;
        hashTable->numElements[hashValue]++;
    }
}

bool Search(HashTable *hashTable, char *key) {
    struct Node *aux;

    unsigned hashValue = Hash(key); 
    
    if (!hashTable) {
        printf("Hash Table is empty.\n");
        return false;
    }
    aux = hashTable->buckets[hashValue];

    while(aux){
        if (strcmp(aux->key, key) == 0)
            return true;

        aux = aux->next;
    }
    //printf("%s [%d]\n", key, hashValue = Hash(key)); //Uncomment if you want to print not found words.
    return false;
}

void RemovePunctAndMakeLowerCase(char *key) {
    char *src = key, *dst = key;

    while (*src) {
       if (ispunct((unsigned char)*src)) {
          /* Skip this character */
          src++;
       }
       else if (isupper((unsigned char)*src)) {
          /* Make it lowercase */
          *dst++ = tolower((unsigned char)*src);
          src++;
       }
       else if (src == dst) {
          /* Increment both pointers without copying */
          src++;
          dst++;
       }
       else {
          /* Copy character */
          *dst++ = *src++;
       }
    }

    *dst = 0;
}

/*
unsigned Hash(char *key) {          //Djb2 hashing
    unsigned long hash = 5381;
    int c;

    while (c = *key++)
        hash = ((hash << 5) + hash) + c;  

    return hash % MAX_BUCKETS;
}
*/

/*
unsigned Hash(char *key) {          //Jenkins Hashing
  size_t i = 0;
  unsigned long hash = 0;
  size_t length = strlen(key);

  while (i != length) {
    hash += key[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash % MAX_BUCKETS;
}
*/