#include "flist.h"
#include <iostream>

using namespace std;

void initFList(ForwardList& list) {
    list.head = nullptr;
}

void destroyFList(ForwardList& list) {
    while (list.head != nullptr) {
        popHead(list);
    }
}

void pushHead(ForwardList& list, const string& val) {
    FNode* new_node = new FNode{val, list.head};
    list.head = new_node;
}

void pushTail(ForwardList& list, const string& val) {
    FNode* new_node = new FNode{val, nullptr};
    if (list.head == nullptr) {
        list.head = new_node;
        return;
    }
    FNode* curr = list.head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = new_node;
}

void pushAfter(ForwardList& list, const string& target, const string& val) {
    FNode* curr = list.head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr) {
        FNode* new_node = new FNode{val, curr->next};
        curr->next = new_node;
    } else {
        cout << "Элемент '" << target << "' не найден для вставки после" << endl;
    }
}

void pushBefore(ForwardList& list, const string& target, const string& val) {
    if (list.head == nullptr) return;
    if (list.head->data == target) {
        pushHead(list, val);
        return;
    }
    FNode* curr = list.head;
    while (curr->next != nullptr && curr->next->data != target) {
        curr = curr->next;
    }
    if (curr->next != nullptr) {
        FNode* new_node = new FNode{val, curr->next};
        curr->next = new_node;
    } else {
        cout << "Элемент '" << target << "' не найден для вставки до" << endl;
    }
}

void popHead(ForwardList& list) {
    if (list.head == nullptr) return;
    FNode* temp = list.head;
    list.head = list.head->next;
    delete temp;
}

void popTail(ForwardList& list) {
    if (list.head == nullptr) return;
    if (list.head->next == nullptr) {
        delete list.head;
        list.head = nullptr;
        return;
    }
    FNode* curr = list.head;
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
}

void removeValue(ForwardList& list, const string& val) {
    if (list.head == nullptr) return;
    if (list.head->data == val) {
        popHead(list);
        return;
    }
    FNode* curr = list.head;
    while (curr->next != nullptr && curr->next->data != val) {
        curr = curr->next;
    }
    if (curr->next != nullptr) {
        FNode* to_delete = curr->next;
        curr->next = to_delete->next;
        delete to_delete;
    }
}

void removeBefore(ForwardList& list, const string& target) {
    if (list.head == nullptr || list.head->data == target) return;
    if (list.head->next != nullptr && list.head->next->data == target) {
        popHead(list);
        return;
    }
    FNode* curr = list.head;
    while (curr->next != nullptr && curr->next->next != nullptr && curr->next->next->data != target) {
        curr = curr->next;
    }
    if (curr->next != nullptr && curr->next->next != nullptr) {
        FNode* to_delete = curr->next;
        curr->next = to_delete->next;
        delete to_delete;
    }
}

void removeAfter(ForwardList& list, const string& target) {
    FNode* curr = list.head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr && curr->next != nullptr) {
        FNode* to_delete = curr->next;
        curr->next = to_delete->next;
        delete to_delete;
    }
}

bool findValue(const ForwardList& list, const string& val) {
    FNode* curr = list.head;
    while (curr != nullptr) {
        if (curr->data == val) return true;
        curr = curr->next;
    }
    return false;
}

void printFList(const ForwardList& list) {
    if (list.head == nullptr) {
        cout << "[Пустой список]" << endl;
        return;
    }
    cout << "[ ";
    FNode* curr = list.head;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) {
            cout << " -> ";
        }
        curr = curr->next;
    }
    cout << " ]" << endl;
}

static void printRecursiveHelper(FNode* node) {
    if (node == nullptr) return;
    cout << node->data << " ";
    printRecursiveHelper(node->next);
}

void printFListRecursive(const ForwardList& list) {
    cout << "[ ";
    printRecursiveHelper(list.head);
    cout << "]" << endl;
}

string getAtFList(const ForwardList& list, size_t index) {
    FNode* curr = list.head;
    size_t currentIndex = 0;
    while (curr != nullptr) {
        if (currentIndex == index) {
            return curr->data;
        }
        curr = curr->next;
        currentIndex++;
    }
    cout << "Ошибка: Индекс выходит за границы списка" << endl;
    return "";
}