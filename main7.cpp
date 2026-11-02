#include "dlist.h"
#include "array.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct LRUCache {
    int capacity;
    DoublyLinkedList list;
    DynamicArray mapKeys;
    DynamicArray mapVals;
    DynamicArray used;
    int mapSize;
};

static  int hashInt(int key, int size) {
    return ( int)(key % size);
}

static int findInHash(const LRUCache& cache, int key) {
    int idx = hashInt(key, cache.mapSize);
    for (int i = 0; i < cache.mapSize; ++i) {
        int cur = (idx + i) % cache.mapSize;
        if (getAt(cache.used, cur) == "0") return -1;
        if (getAt(cache.mapKeys, cur) == to_string(key)) return cur;
    }
    return -1;
}

static void insertInHash(LRUCache& cache, int key, int value) {
    int idx = hashInt(key, cache.mapSize);
    for (int i = 0; i < cache.mapSize; ++i) {
        int cur = (idx + i) % cache.mapSize;
        if (getAt(cache.used, cur) == "0" || getAt(cache.mapKeys, cur) == to_string(key)) {
            setAt(cache.mapKeys, cur, to_string(key));
            setAt(cache.mapVals, cur, to_string(value));
            setAt(cache.used, cur, "1");
            return;
        }
    }
}

static void lruInit(LRUCache& cache, int capacity) {
    cache.capacity = capacity;
    initDList(cache.list);
    cache.mapSize = capacity * 2;
    initArray(cache.mapKeys, cache.mapSize);
    initArray(cache.mapVals, cache.mapSize);
    initArray(cache.used, cache.mapSize);
    for (int i = 0; i < cache.mapSize; ++i) {
        pushBack(cache.mapKeys, "");
        pushBack(cache.mapVals, "");
        pushBack(cache.used, "0");
    }
}

static void lruDestroy(LRUCache& cache) {
    destroyDList(cache.list);
    destroyArray(cache.mapKeys);
    destroyArray(cache.mapVals);
    destroyArray(cache.used);
}

static void lruSet(LRUCache& cache, int key, int value) {
    string keyStr = to_string(key);
    string valStr = to_string(value);
    string item = keyStr + ":" + valStr;

    int hashIdx = findInHash(cache, key);

    if (hashIdx != -1) {
        string oldVal = getAt(cache.mapVals, hashIdx);
        string oldItem = keyStr + ":" + oldVal;
        removeValueDList(cache.list, oldItem);
    } else {
        int currentSize = 0;
        DNode* cur = cache.list.head;
        while (cur) { currentSize++; cur = cur->next; }

        if (currentSize >= cache.capacity) {
            if (cache.list.tail != nullptr) {
                string tailData = cache.list.tail->data;
                size_t pos = tailData.find(':');
                int tailKey = stoi(tailData.substr(0, pos));
                int tIdx = findInHash(cache, tailKey);
                if (tIdx != -1) setAt(cache.used, tIdx, "0");
                popTailDList(cache.list);
            }
        }
    }

    pushHeadDList(cache.list, item);
    insertInHash(cache, key, value);
}

static int lruGet(LRUCache& cache, int key) {
    int hashIdx = findInHash(cache, key);
    if (hashIdx == -1) return -1;

    string valStr = getAt(cache.mapVals, hashIdx);
    int value = stoi(valStr);

    string keyStr = to_string(key);
    string item = keyStr + ":" + valStr;
    removeValueDList(cache.list, item);
    pushHeadDList(cache.list, item);

    return value;
}

int main() {
    int cap, Q;
    cin >> cap >> Q;

    LRUCache cache;
    lruInit(cache, cap);

    cin.ignore();

    for (int i = 0; i < Q; ++i) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "SET") {
            int k, v;
            ss >> k >> v;
            lruSet(cache, k, v);
        } else if (cmd == "GET") {
            int k;
            ss >> k;
            cout << lruGet(cache, k) << endl;
        }
    }

    lruDestroy(cache);
    return 0;
}