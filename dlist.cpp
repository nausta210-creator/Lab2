#include "dlist.h"
#include <iostream>

using namespace std;

void initDList(DoublyLinkedList& list) {
    list.head = nullptr;
    list.tail = nullptr;
}

void destroyDList(DoublyLinkedList& list) {
    while (list.head != nullptr) {
        popHeadDList(list);
    }
}

void pushHeadDList(DoublyLinkedList& list, const string& val) {
    DNode* new_node = new DNode{val, nullptr, list.head};
    if (list.head != nullptr) {
        list.head->prev = new_node;
    } else {
        list.tail = new_node;
    }
    list.head = new_node;
}

void pushTailDList(DoublyLinkedList& list, const string& val) {
    DNode* new_node = new DNode{val, list.tail, nullptr};
    if (list.tail != nullptr) {
        list.tail->next = new_node;
    } else {
        list.head = new_node;
    }
    list.tail = new_node;
}

void pushAfterDList(DoublyLinkedList& list, const string& target, const string& val) {
    DNode* curr = list.head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr) {
        DNode* new_node = new DNode{val, curr, curr->next};
        if (curr->next != nullptr) {
            curr->next->prev = new_node;
        } else {
            list.tail = new_node;
        }
        curr->next = new_node;
    } else {
        cout << "Элемент '" << target << "' не найден" << endl;
    }
}

void pushBeforeDList(DoublyLinkedList& list, const string& target, const string& val) {
    DNode* curr = list.head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr) {
        DNode* new_node = new DNode{val, curr->prev, curr};
        if (curr->prev != nullptr) {
            curr->prev->next = new_node;
        } else {
            list.head = new_node;
        }
        curr->prev = new_node;
    } else {
        cout << "Элемент '" << target << "' не найден" << endl;
    }
}

void popHeadDList(DoublyLinkedList& list) {
    if (list.head == nullptr) return;
    DNode* temp = list.head;
    list.head = list.head->next;
    if (list.head != nullptr) {
        list.head->prev = nullptr;
    } else {
        list.tail = nullptr;
    }
    delete temp;
}

void popTailDList(DoublyLinkedList& list) {
    if (list.tail == nullptr) return;
    DNode* temp = list.tail;
    list.tail = list.tail->prev;
    if (list.tail != nullptr) {
        list.tail->next = nullptr;
    } else {
        list.head = nullptr;
    }
    delete temp;
}

void removeValueDList(DoublyLinkedList& list, const string& val) {
    DNode* curr = list.head;
    while (curr != nullptr && curr->data != val) {
        curr = curr->next;
    }
    if (curr == nullptr) return;

    if (curr == list.head) {
        popHeadDList(list);
    } else if (curr == list.tail) {
        popTailDList(list);
    } else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
    }
}

void removeBeforeDList(DoublyLinkedList& list, const string& target) {
    DNode* curr = list.head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr && curr->prev != nullptr) {
        DNode* to_delete = curr->prev;
        if (to_delete == list.head) {
            popHeadDList(list);
        } else {
            to_delete->prev->next = curr;
            curr->prev = to_delete->prev;
            delete to_delete;
        }
    }
}

void removeAfterDList(DoublyLinkedList& list, const string& target) {
    DNode* curr = list.head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr && curr->next != nullptr) {
        DNode* to_delete = curr->next;
        if (to_delete == list.tail) {
            popTailDList(list);
        } else {
            curr->next = to_delete->next;
            to_delete->next->prev = curr;
            delete to_delete;
        }
    }
}

string getAtDList(const DoublyLinkedList& list, size_t index) {
    DNode* curr = list.head;
    size_t currIdx = 0;
    while (curr != nullptr) {
        if (currIdx == index) return curr->data;
        curr = curr->next;
        currIdx++;
    }
    cout << "Ошибка: Индекс выходит за границы" << endl;
    return "";
}

bool findValueDList(const DoublyLinkedList& list, const string& val) {
    DNode* curr = list.head;
    while (curr != nullptr) {
        if (curr->data == val) return true;
        curr = curr->next;
    }
    return false;
}

void printDListReverse(const DoublyLinkedList& list) {
    if (list.tail == nullptr) {
        cout << "[Пустой список]" << endl;
        return;
    }
    cout << "[ ";
    DNode* curr = list.tail;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->prev != nullptr) {
            cout << " <=> ";
        }
        curr = curr->prev;
    }
    cout << " ]" << endl;
}

void printDList(const DoublyLinkedList& list) {
    if (list.head == nullptr) {
        cout << "[Пустой список]" << endl;
        return;
    }
    cout << "[ ";
    DNode* curr = list.head;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) {
            cout << " <=> ";
        }
        curr = curr->next;
    }
    cout << " ]" << endl;
}