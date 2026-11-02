#include "set.h"
#include <iostream>

static int hashString(const string& key, int size) {
    long long h = 14695981039346656037ULL; //Число алгоритма FNV-1a
    for (size_t i = 0; i < key.size(); ++i) {
        h ^= (char)key[i]; //XOR; приводим char к числу 0..255
        h *= 1099511628211ULL; //Умножение на константу FNV
    }
    return (int)h % size;
}

void setInit(Set& s, int size) {
    s.size = size;
    s.count = 0;
    s.buckets = new ForwardList[size];     
    for (int i = 0; i < size; ++i)
        initFList(s.buckets[i]);            
}

void setDestroy(Set& s) {
    for (int i = 0; i < s.size; ++i)
        destroyFList(s.buckets[i]);         
    delete[] s.buckets;
    s.buckets = nullptr;
    s.size = 0;
    s.count = 0;
}

void setAdd(Set& s, const string& key) {
    int idx = hashString(key, s.size);
    if (findValue(s.buckets[idx], key)) return;  
    pushHead(s.buckets[idx], key);               
    s.count++;
}

void setDel(Set& s, const string& key) {
    int idx = hashString(key, s.size);
    if (findValue(s.buckets[idx], key)) {        
        removeValue(s.buckets[idx], key);        
        s.count--;
    }
}

bool setContains(const Set& s, const string& key) {
    int idx = hashString(key, s.size);
    return findValue(s.buckets[idx], key);       
}