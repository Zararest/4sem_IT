#ifndef HASHTABLE_ 
#define HASHTABLE_

#define MIN_CAPACITY 64
#define REHASH_FACTOR 2                                 

typedef int Key;
typedef int Bool;

typedef struct _TableCell TableCell;
typedef struct _HashTable HashTable;

void* my_calloc(size_t nmem, size_t size);

HashTable* createHashTable(int capacity);
void rehash(HashTable* table);
void freeHashTable(HashTable* table);

Key addElem(HashTable* table, const char* element);
char* getElem(HashTable* table, Key key);
void removeElem(HashTable* table, const char* element);

Key Hash(const char* element);

#endif