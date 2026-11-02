#ifndef HASH_H
#define HASH_H

#include "array.h"

using namespace std;

struct HashTable {
    DynamicArray slots;
    DynamicArray used;
    int size;
    int count;
    int method; 
};

void hashInit(HashTable& t, int size, int method);
void hashDestroy(HashTable& t);
bool hashInsert(HashTable& t, const string& key);
bool hashSearch(const HashTable& t, const string& key);
bool hashRemove(HashTable& t, const string& key);

int foldHash(const string& key, int size);

#endif