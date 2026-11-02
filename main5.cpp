#include "dlist.h"     
#include "array.h"      
#include <iostream>
#include <string>

using namespace std;

struct HNode {
    char ch;
    int freq;
    HNode* left;
    HNode* right;
};

static HNode* createNode(char ch, int freq, HNode* left = nullptr, HNode* right = nullptr) {
    HNode* n = new HNode;
    n->ch = ch;
    n->freq = freq;
    n->left = left;
    n->right = right;
    return n;
}

static void destroyTree(HNode* root) {
    if (!root) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

//Указатель на узел -> строка
static string packNode(HNode* node) {
    long long addr = (long long)node;
    return to_string(node->freq) + ":" + to_string(addr);
}

static HNode* unpackNode(const string& s) {
    size_t pos = s.find(':');
    if (pos == string::npos) return nullptr; //Не найдено
    
     long long addr = 0;
    for (size_t i = pos + 1; i < s.size(); ++i) {
        if (s[i] >= '0' && s[i] <= '9')
            addr = addr * 10 + (s[i] - '0');
    }
    return (HNode*)addr; //Обратно указатель
}

static int getPackedFreq(const string& s) {
    int freq = 0;
    for (size_t i = 0; i < s.size() && s[i] != ':'; ++i) {
        if (s[i] >= '0' && s[i] <= '9')
            freq = freq * 10 + (s[i] - '0');
    }
    return freq;
}

static HNode* buildHuffman(const string& text) {
    if (text.empty()) return nullptr;

    int freq[256] = {0};
    for (size_t i = 0; i < text.size(); ++i)
        freq[(char)text[i]]++;

    DoublyLinkedList nodes;
    initDList(nodes);

    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            HNode* leaf = createNode((char)i, freq[i]);
            pushTailDList(nodes, packNode(leaf)); 
        }
    }

    if (nodes.head == nodes.tail) {
        HNode* only = unpackNode(nodes.head->data);
        HNode* root = createNode('\0', only->freq, only, nullptr);
        destroyDList(nodes);
        return root;
    }

    while (nodes.head != nodes.tail) { 
        
        DNode* min1 = nodes.head;
        DNode* min2 = nodes.head->next;
        
        if (getPackedFreq(min1->data) > getPackedFreq(min2->data)) {
            DNode* temp = min1; min1 = min2; min2 = temp;
        }

        for (DNode* curr = nodes.head->next->next; curr != nullptr; curr = curr->next) {
            int f = getPackedFreq(curr->data);
            if (f < getPackedFreq(min1->data)) {
                min2 = min1;
                min1 = curr;
            } else if (f < getPackedFreq(min2->data)) {
                min2 = curr;
            }
        }

        HNode* a = unpackNode(min1->data);
        HNode* b = unpackNode(min2->data);

        HNode* parent = createNode('\0', a->freq + b->freq, a, b);

        string strA = min1->data;
        string strB = min2->data;
        removeValueDList(nodes, strA); 
        removeValueDList(nodes, strB);

        pushTailDList(nodes, packNode(parent)); 
    }

    HNode* root = unpackNode(nodes.head->data);
    destroyDList(nodes);
    return root;
}

static void generateCodes(HNode* root, const string& prefix, DynamicArray& table) {
    if (!root) return;
    if (!root->left && !root->right) {
        string s = "";
        s += root->ch;
        s += " ";
        s += prefix;
        pushBack(table, s); 
        return;
    }
    generateCodes(root->left, prefix + "0", table);
    generateCodes(root->right, prefix + "1", table);
}

static string getCode(const DynamicArray& table, char ch) {
    for (size_t i = 0; i < getSize(table); ++i) { 
        string s = getAt(table, i);               
        if (s.size() >= 2 && s[0] == ch && s[1] == ' ')
            return s.substr(2); //С позиции 2 до конца
    }
    return "";
}

static string encode(const string& text, const DynamicArray& table) {
    string result;
    for (size_t i = 0; i < text.size(); ++i)
        result += getCode(table, text[i]);
    return result;
}

static string decode(const string& encoded, HNode* root) {
    string result;
    HNode* cur = root;
    for (size_t i = 0; i < encoded.size(); ++i) {
        if (encoded[i] == '0') cur = cur->left;
        else cur = cur->right;

        if (!cur) return result;
        if (!cur->left && !cur->right) {
            result += cur->ch;
            cur = root;
        }
    }
    return result;
}

int main() {
    string text;
    cout << "Введите строку: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "Пустая строка" << endl;
        return 0;
    }

    HNode* root = buildHuffman(text);

    DynamicArray table;
    initArray(table, 4);
    generateCodes(root, "", table);

    cout << "\nТаблица кодов:\n";
    for (size_t i = 0; i < getSize(table); ++i) {
        cout << "  " << getAt(table, i) << "\n";
    }

    string encoded = encode(text, table);
    cout << "\nЗакодировано: " << encoded << "\n";

    string decoded = decode(encoded, root);
    cout << "Декодировано: " << decoded << "\n";

    if (decoded == text) cout << "[OK] совпадает\n";
    else                 cout << "[ОШИБКА] не совпадает\n";

    destroyArray(table);
    destroyTree(root);

    return 0;
}