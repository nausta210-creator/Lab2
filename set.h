#ifndef SET_H
#define SET_H

#include "flist.h"

using namespace std;

struct Set {
    ForwardList* buckets;
    int size;
    int count;
};

void setInit(Set& s, int size);
void setDestroy(Set& s);
void setAdd(Set& s, const string& key);
void setDel(Set& s, const string& key);
bool setContains(const Set& s, const string& key);

#endif