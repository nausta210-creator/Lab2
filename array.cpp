#include "array.h"
#include <iostream>

using namespace std;

void initArray(DynamicArray& arr, size_t initial_capacity) {
    if (initial_capacity > 0) {
        arr.capacity = initial_capacity;
    } else {
        arr.capacity = 4;
    }
    arr.length = 0;
    arr.data = new string[arr.capacity];
}

void destroyArray(DynamicArray& arr) {
    if (arr.data != nullptr) {
        delete[] arr.data;
        arr.data = nullptr;
    }
    arr.length = 0;
    arr.capacity = 0;
}

static void resizeArray(DynamicArray& arr, size_t new_capacity) {
    string* new_data = new string[new_capacity];
    for (size_t i = 0; i < arr.length; ++i) {
        new_data[i] = arr.data[i];
    }
    delete[] arr.data;
    arr.data = new_data;
    arr.capacity = new_capacity;
}

void pushBack(DynamicArray& arr, const string& value) {
    if (arr.length == arr.capacity) {
        resizeArray(arr, arr.capacity * 2);
    }
    arr.data[arr.length++] = value;
}

void insertAt(DynamicArray& arr, size_t index, const string& value) {
    if (index > arr.length || index < 0) {
        cout << "Ошибка: Индекс выходит за границы" << endl;
        return;
    }
    if (arr.length == arr.capacity) {
        resizeArray(arr, arr.capacity * 2);
    }
    for (size_t i = arr.length; i > index; --i) {
        arr.data[i] = arr.data[i - 1];
    }
    arr.data[index] = value;
    arr.length++;
}

string getAt(const DynamicArray& arr, size_t index) {
    if (index >= arr.length || index < 0) {
        cout << "Ошибка: Индекс выходит за границы" << endl;
        return "";
    }
    return arr.data[index];
}

void removeAt(DynamicArray& arr, size_t index) {
    if (index >= arr.length || index < 0) {
        cout << "Ошибка: Индекс выходит за границы" << endl;
        return;
    }
    for (size_t i = index; i < arr.length - 1; ++i) {
        arr.data[i] = arr.data[i + 1];
    }
    arr.length--;
}

void setAt(DynamicArray& arr, size_t index, const string& value) {
    if (index >= arr.length || index < 0) {
        cout << "Ошибка: Индекс выходит за границы" << endl;
        return;
    }
    arr.data[index] = value;
}

size_t getSize(const DynamicArray& arr) {
    return arr.length;
}

void printArray(const DynamicArray& arr) {
    if (arr.length == 0) {
        cout << "[Пустой массив]" << endl;
        return;
    }
    cout << "[ ";
    for (size_t i = 0; i < arr.length; ++i) {
        cout << arr.data[i];
        if (i + 1 < arr.length) {
            cout << ", ";
        }
    }
    cout << " ]" << endl;
}