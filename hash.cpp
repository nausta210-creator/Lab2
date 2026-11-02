#include "hash.h"

static int int hash1(const string& key, int size) {
     long long h = 14695981039346656037ULL; //Начальное значение FNV-1a
    for (size_t i = 0; i < key.size(); ++i) {
        h ^= ( char)key[i];
        h *= 1099511628211ULL;
    }
    return ( int)(h % size);
}

static  int hash2(const string& key, int size) {
     long long h = 5381;
    for (size_t i = 0; i < key.size(); ++i) {
        h = ((h << 5) + h) + ( char)key[i];
    }
    return ( int)(h % (size - 1)) + 1;
}

int foldHash(const string& key, int size) {
    long long sum = 0;
    string part = "";
    for (size_t i = 0; i < key.size(); ++i) {
        part += key[i];
        if (part.size() == 3) {
            sum += stoll(part); //превращаем в число
            part = "";
        }
    }
    if (!part.empty()) sum += stoll(part);
    return (int)(sum % size);
}

static  int getHash(const HashTable& t, const string& key) {
    if (t.method == 2) {
        return foldHash(key, t.size);
    }
    return hash1(key, t.size);
}

void hashInit(HashTable& t, int size, int method) {
    t.size = size;
    t.count = 0;
    t.method = method;
    initArray(t.slots, size);
    initArray(t.used, size);
    for (int i = 0; i < size; ++i) {
        pushBack(t.slots, "");
        pushBack(t.used, "0");
    }
}

void hashDestroy(HashTable& t) {
    destroyArray(t.slots);
    destroyArray(t.used);
    t.size = 0;
    t.count = 0;
}

bool hashInsert(HashTable& t, const string& key) {
    if (t.count >= t.size) return false;

    int idx = getHash(t, key);
    int step;
    if (t.method == 2) {
        step = hash2(key, t.size);
    } else {
        step = 1;
    }

    for (int i = 0; i < t.size; ++i) {
        int cur = (idx + i * step) % t.size;
        if (getAt(t.used, cur) == "0") {
            setAt(t.slots, cur, key);
            setAt(t.used, cur, "1");
            t.count++;
            return true;
        }
        if (getAt(t.slots, cur) == key) return false;
    }
    return false;
}

bool hashSearch(const HashTable& t, const string& key) {
    int idx = getHash(t, key);
    int step;
    if (t.method == 2) {
        step = hash2(key, t.size);
    } else {
        step = 1;
    }

    for (int i = 0; i < t.size; ++i) {
        int cur = (idx + i * step) % t.size;
        if (getAt(t.used, cur) == "0") return false;
        if (getAt(t.slots, cur) == key) return true;
    }
    return false;
}

bool hashRemove(HashTable& t, const string& key) {
    int idx = getHash(t, key);
    int step;
    if (t.method == 2) {
        step = hash2(key, t.size);
    } else {
        step = 1;
    }

    for (int i = 0; i < t.size; ++i) {
        int cur = (idx + i * step) % t.size;
        if (getAt(t.used, cur) == "0") return false;
        if (getAt(t.slots, cur) == key) {
            setAt(t.slots, cur, "");
            setAt(t.used, cur, "0");
            t.count--;
            return true;
        }
    }
    return false;
}