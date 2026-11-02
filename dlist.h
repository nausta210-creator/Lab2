#ifndef DLIST_H
#define DLIST_H

#include <string>

using namespace std;

struct DNode {
    string data;
    DNode* prev;
    DNode* next;
};

struct DoublyLinkedList {
    DNode* head;
    DNode* tail;
};

void initDList(DoublyLinkedList& list);
void destroyDList(DoublyLinkedList& list);

void pushHeadDList(DoublyLinkedList& list, const string& val);
void pushTailDList(DoublyLinkedList& list, const string& val);
void pushBeforeDList(DoublyLinkedList& list, const string& target, const string& val);
void pushAfterDList(DoublyLinkedList& list, const string& target, const string& val);

void popHeadDList(DoublyLinkedList& list);
void popTailDList(DoublyLinkedList& list);
void removeValueDList(DoublyLinkedList& list, const string& val);
void removeBeforeDList(DoublyLinkedList& list, const string& target);
void removeAfterDList(DoublyLinkedList& list, const string& target);

string getAtDList(const DoublyLinkedList& list, size_t index);
bool findValueDList(const DoublyLinkedList& list, const string& val);
void printDList(const DoublyLinkedList& list);
void printDListReverse(const DoublyLinkedList& list);

#endif