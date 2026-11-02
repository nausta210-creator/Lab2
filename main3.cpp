#include "set.h"
#include <iostream>
#include <string>

using namespace std;

static int countIntersection(const Set& a, const Set& b) {
    int count = 0;
    for (int i = 0; i < a.size; ++i) {
        FNode* cur = a.buckets[i].head;
        while (cur) {
            if (setContains(b, cur->data)) count++;
            cur = cur->next;
        }
    }
    return count;
}

int main() {
    string input;
    getline(cin, input);

    string rawSets[100][100];
    int rawCounts[100];
    int setCount = 0;

    int depth = 0;
    string cur = "";
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        if (c == '{') {
            depth++;
            if (depth == 2) { cur = ""; rawCounts[setCount] = 0; }
        } else if (c == '}') {
            if (depth == 2) {
                if (!cur.empty()) rawSets[setCount][rawCounts[setCount]++] = cur;
                setCount++;
            }
            depth--;
        } else if (c == ',') {
            if (depth == 2 && !cur.empty()) {
                rawSets[setCount][rawCounts[setCount]++] = cur;
                cur = "";
            }
        } else if (c == ' ') {
            if (depth == 2 && !cur.empty()) {
                rawSets[setCount][rawCounts[setCount]++] = cur;
                cur = "";
            }
        } else {
            cur += c;
        }
    }

    if (setCount < 2) return 1;

    Set* sets = new Set[setCount];
    for (int i = 0; i < setCount; ++i) {
        setInit(sets[i], 1009);
        for (int j = 0; j < rawCounts[i]; ++j) setAdd(sets[i], rawSets[i][j]);
    }

    int bestI = 0, bestJ = 1, bestCount = -1;
    for (int i = 0; i < setCount; ++i) {
        for (int j = i + 1; j < setCount; ++j) {
            int c = countIntersection(sets[i], sets[j]);
            if (c > bestCount) {
                bestCount = c;
                bestI = i;
                bestJ = j;
            }
        }
    }

    cout << "{{";
    for (int k = 0; k < rawCounts[bestI]; ++k) {
        if (k) cout << ", ";
        cout << rawSets[bestI][k];
    }
    cout << "}, {";
    for (int k = 0; k < rawCounts[bestJ]; ++k) {
        if (k) cout << ", ";
        cout << rawSets[bestJ][k];
    }
    cout << "}}, " << bestCount << endl;

    for (int i = 0; i < setCount; ++i) setDestroy(sets[i]);
    delete[] sets;
    return 0;
}