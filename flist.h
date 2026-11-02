#ifndef FLIST_H
#define FLIST_H

#include <string>

using namespace std;

struct FNode {
    string data;
    FNode* next;
};

struct ForwardList {
    FNode* head;
};

void initFList(ForwardList& list);
void destroyFList(ForwardList& list);

void pushHead(ForwardList& list, const string& val);
void pushTail(ForwardList& list, const string& val);
void pushBefore(ForwardList& list, const string& target, const string& val);
void pushAfter(ForwardList& list, const string& target, const string& val);

void popHead(ForwardList& list);
void popTail(ForwardList& list);
void removeValue(ForwardList& list, const string& val);
void removeBefore(ForwardList& list, const string& target);
void removeAfter(ForwardList& list, const string& target);

string getAtFList(const ForwardList& list, size_t index);
bool findValue(const ForwardList& list, const string& val);
void printFList(const ForwardList& list);
void printFListRecursive(const ForwardList& list);

#endif