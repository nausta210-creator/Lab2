#include "set.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    string filePath;
    string query;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) filePath = argv[++i];
        else if (arg == "--query" && i + 1 < argc) query = argv[++i];
    }

    Set s;
    setInit(s, 1009);

    if (!filePath.empty()) {
        ifstream fin(filePath.c_str());
        if (!fin) {
            cerr << "Не удалось открыть файл: " << filePath << endl;
            setDestroy(s);
            return 1;
        }
        string line;
        while (getline(fin, line)) {
            if (!line.empty()) setAdd(s, line);
        }
    }

    string cur = "", cmd = "";
    for (size_t i = 0; i <= query.size(); ++i) {
        if (i == query.size() || query[i] == ' ' || query[i] == '\t') {
            if (!cur.empty()) {
                if (cmd.empty()) {
                    cmd = cur;
                } else {
                    if (cmd == "SETADD") {
                        setAdd(s, cur);
                        cout << "SETADD " << cur << " -> OK" << endl;
                    } else if (cmd == "SETDEL") {
                        setDel(s, cur);
                        cout << "SETDEL " << cur << " -> OK" << endl;
                    } else if (cmd == "SET_AT") {
                        cout << "SET_AT " << cur << " -> "
                             << (setContains(s, cur) ? "YES" : "NO") << endl;
                    }
                    cmd = "";
                }
                cur = "";
            }
        } else {
            cur += query[i];
        }
    }

    if (!filePath.empty()) {
        ofstream fout(filePath.c_str());
        if (fout) {
            for (int i = 0; i < s.size; ++i) {
                FNode* curr = s.buckets[i].head;
                while (curr != nullptr) {
                    fout << curr->data << "\n";
                    curr = curr->next;
                }
            }
        }
    }

    setDestroy(s);
    return 0;
}