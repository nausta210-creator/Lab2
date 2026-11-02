#include "hash.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

static double now_ms() {
    return (double)clock() * 1000.0 / CLOCKS_PER_SEC;
}

int main() {
    cout << "Подзадание 6.1" << endl;
    cout << "N\tLinear(ms)\tDouble(ms)" << endl;

    int sizes[] = { 100, 10000 };
    for (int s = 0; s < 2; ++s) {
        int N = sizes[s];
        int tableSize = N * 2;

        HashTable lt;
        hashInit(lt, tableSize, 1);
        double t0 = now_ms();
        for (int i = 0; i < N; ++i) {
            string k = to_string(i * 1000 + 123);
            hashInsert(lt, k);
        }
        double t1 = now_ms();

        HashTable dt;
        hashInit(dt, tableSize, 2);
        double t2 = now_ms();
        for (int i = 0; i < N; ++i) {
            string k = to_string(i * 1000 + 123);
            hashInsert(dt, k);
        }
        double t3 = now_ms();

        cout << N << "\t" << (t1 - t0) << "\t\t" << (t3 - t2) << endl;

        hashDestroy(lt);
        hashDestroy(dt);
    }

    cout << "\nПодзадание 6.2" << endl;
    string key;
    cout << "Введите числовой ключ: ";
    cin >> key;

    int sum = 0;
    string part = "";
    for (size_t i = 0; i < key.size(); ++i) {
        part += key[i];
        if (part.size() == 3) {
            sum += stoll(part);
            part = "";
        }
    }
    if (!part.empty()) sum += stoll(part);

    cout << "Сумма: " << sum << endl;
    cout << "Хеш: " << foldHash(key, 100) << endl;

    return 0;
}