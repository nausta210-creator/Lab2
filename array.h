#ifndef ARRAY_H
#define ARRAY_H

#include <string>
#include <cstddef>

using namespace std;

struct DynamicArray {
    string* data;
    size_t capacity;
    size_t length;
};

void initArray(DynamicArray& arr, size_t initial_capacity = 4);
void destroyArray(DynamicArray& arr);

void pushBack(DynamicArray& arr, const string& value);
void insertAt(DynamicArray& arr, size_t index, const string& value);
string getAt(const DynamicArray& arr, size_t index);
void removeAt(DynamicArray& arr, size_t index);
void setAt(DynamicArray& arr, size_t index, const string& value);
size_t getSize(const DynamicArray& arr);
void printArray(const DynamicArray& arr);

#endif