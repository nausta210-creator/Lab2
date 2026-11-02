#include "array.h"
#include <iostream>

using namespace std;

struct Block {
    int w;
    int h;
};

static Block parseBlock(const string& s) {
    Block b = {0, 0};
    int part = 0;
    int cur = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c >= '0' && c <= '9') cur = cur * 10 + (c - '0');
        else if (c == ' ' || c == ':') {
            if (part == 0) { b.w = cur; part = 1; cur = 0; }
            else { b.h = cur; break; }
        }
    }
    if (part == 1 && cur > 0) b.h = cur;
    return b;
}

static void bubbleSort(Block* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j].w > arr[j + 1].w) {
                Block tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main() {
    int N;
    if (!(cin >> N)) return 0;

    DynamicArray blocks;
    initArray(blocks, N);

    for (int i = 0; i < N; ++i) {
        int w, h;
        cin >> w >> h;
        pushBack(blocks, to_string(w) + " " + to_string(h));
    }

    Block* vec = new Block[N];
    for (int i = 0; i < N; ++i) vec[i] = parseBlock(getAt(blocks, i));

    bubbleSort(vec, N);

    int* uniqW = new int[N];
    int* maxH = new int[N];
    int m = 0;

    for (int i = 0; i < N; ++i) {
        if (m == 0 || uniqW[m - 1] != vec[i].w) {
            uniqW[m] = vec[i].w;
            maxH[m] = vec[i].h;
            m++;
        } else {
            if (vec[i].h > maxH[m - 1]) maxH[m - 1] = vec[i].h;
        }
    }

    int bestPrev = 0, answer = 0;
    for (int i = 0; i < m; ++i) {
        int dp = maxH[i] + bestPrev;
        if (dp > answer) answer = dp;
        if (dp > bestPrev) bestPrev = dp;
    }

    cout << answer << endl;

    delete[] vec;
    delete[] uniqW;
    delete[] maxH;
    destroyArray(blocks);
    return 0;
}