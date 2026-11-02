#ifndef STACK_H
#define STACK_H

#include <string>

using namespace std;

struct SNode {
    string data;
    SNode* next;
};

struct Stack {
    SNode* top;
};

void initStack(Stack& st);
void destroyStack(Stack& st);
void pushStack(Stack& st, const string& val);
string popStack(Stack& st);
void printStack(const Stack& st);

#endif