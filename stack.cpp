#include "stack.h"
#include <iostream>

using namespace std;

void initStack(Stack& st) {
    st.top = nullptr;
}

void destroyStack(Stack& st) {
    while (st.top != nullptr) {
        popStack(st);
    }
}

void pushStack(Stack& st, const string& val) {
    SNode* newNode = new SNode{val, st.top};
    st.top = newNode;
}

string popStack(Stack& st) {
    if (st.top == nullptr) return "";
    SNode* temp = st.top;
    string val = temp->data;
    st.top = st.top->next;
    delete temp;
    return val;
}

void printStack(const Stack& st) {
    if (st.top == nullptr) {
        cout << "[Пустой стек]" << endl;
        return;
    }
    cout << "[ ";
    SNode* curr = st.top;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) {
            cout << " -> ";
        }
        curr = curr->next;
    }
    cout << " ]" << endl;
}