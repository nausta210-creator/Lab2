#include "stack.h"      
#include <iostream>
#include <string>

using namespace std;

static const string E_EMPTY_EXPR = "Пустое выражение";
static const string E_TWO_NUMBERS = "Два числа подряд: пропущен знак операции";
static const string E_NUMBER_TOO_BIG = "Число по модулю превосходит 2000000000";
static const string E_BAD_UNARY_MINUS = "После знака минус ожидалось число";
static const string E_PAREN_AFTER_OPERAND = "Открывающая скобка не может стоять сразу после числа";
static const string E_EMPTY_PARENS = "Пустые скобки или закрывающая скобка стоит не на месте";
static const string E_UNBALANCED_CLOSE = "Лишняя закрывающая скобка: нет парной открывающей";
static const string E_UNBALANCED_OPEN = "Не закрыта открывающая скобка";
static const string E_OP_IN_WRONG_PLACE = "Знак операции стоит не на месте";
static const string E_ENDS_WITH_OP = "Выражение не может заканчиваться знаком операции или скобкой";
static const string E_EXTRA_OPERANDS = "Лишние числа: между ними пропущен знак операции";
static const string E_NOT_ENOUGH_OPERANDS ="Не хватает чисел для выполнения операции";
static const string E_OVERFLOW ="Промежуточный результат по модулю превосходит 2000000000";
static const string E_BAD_NUMBER ="Внутренняя ошибка: в стеке оказалось не число";
static const string E_BAD_CHAR ="Недопустимый символ: ";

static const long long LIMIT = 2000000000LL;

static bool myIsDigit(char c) {
    return c >= '0' && c <= '9';
}

static bool myIsSpace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static bool parseNumber(const string& s, long long& out) {
    if (s.size() == 0) return false;

    size_t i = 0;
    bool neg = false;

    if (s[0] == '-') { neg = true;  i = 1; }
    else if (s[0] == '+') { i = 1; }

    if (i >= s.size()) return false;

    long long v = 0;
    for (; i < s.size(); ++i) {
        char c = s[i];
        if (!myIsDigit(c)) return false;
        v = v * 10 + (c - '0');
    }

    if (neg) {
        out = -v;
    } else {
        out = v;
    }    
    
    return true;
}

static string numberToString(long long v) {
    if (v == 0) return "0";
    bool neg = (v < 0);
    if (neg) v = -v;
    string s;
    while (v > 0) {
        char c = char('0' + (v % 10));
        s = c + s;
        v /= 10;
    }
    if (neg) s = "-" + s;
    return s;
}

static int precedence(char op) {
    if (op == '*') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

static bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*';
}

static char topOp(const Stack& ops) {
    if (ops.top == 0) return '\0';
    return ops.top->data[0];
}

static bool isTopOpenParen(const Stack& ops) {
    if (ops.top == 0) return false;
    return ops.top->data == "(";
}

static bool applyOp(Stack& values, char op, string& error) {
    string bStr = popStack(values);
    string aStr = popStack(values);
    if (bStr.size() == 0 || aStr.size() == 0) {
        error = E_NOT_ENOUGH_OPERANDS;
        return false;
    }

    long long a, b;
    if (!parseNumber(aStr, a) || !parseNumber(bStr, b)) {
        error = E_BAD_NUMBER;
        return false;
    }

    long long res = 0;
    if      (op == '+') res = a + b;
    else if (op == '-') res = a - b;
    else if (op == '*') res = a * b;

    if (res > LIMIT || res < -LIMIT) {
        error = E_OVERFLOW;
        return false;
    }

    pushStack(values, numberToString(res));
    return true;
}

static bool readNumber(const string& expr, size_t& i, string& out) {
    size_t n = expr.size();
    size_t start = i;
    out = "";
    while (i < n && myIsDigit(expr[i])) {
        out = out + expr[i];
        i++;
    }
    return i > start;
}

static bool flushUntilParen(Stack& values, Stack& ops, string& error) {
    while (ops.top != 0 && !isTopOpenParen(ops)) {
        char op = topOp(ops);
        popStack(ops);
        if (!applyOp(values, op, error)) return false;
    }
    return true;
}

static bool flushAll(Stack& values, Stack& ops, string& error) {
    while (ops.top != 0) {
        if (isTopOpenParen(ops)) {
            error = E_UNBALANCED_OPEN;
            return false;
        }
        char op = topOp(ops);
        popStack(ops);
        if (!applyOp(values, op, error)) return false;
    }
    return true;
}

static bool evaluate(const string& expr, long long& result, string& error) {
    Stack values, ops;
    initStack(values);
    initStack(ops);

    bool ok = true;
    bool expectOperand = true;
    size_t i = 0;
    size_t n = expr.size();

    while (ok && i < n) {
        char c = expr[i];

        if (myIsSpace(c)) { i++; continue; }

        if (myIsDigit(c)) {
            if (!expectOperand) { error = E_TWO_NUMBERS; ok = false; break; }

            string numStr;
            readNumber(expr, i, numStr);

            long long v;
            if (!parseNumber(numStr, v) || v > LIMIT) {
                error = E_NUMBER_TOO_BIG; ok = false; break;
            }
            pushStack(values, numStr);
            expectOperand = false;
            continue;
        }

        if (c == '-' && expectOperand) {
            i++;
            while (i < n && myIsSpace(expr[i])) i++;

            string numStr;
            if (!readNumber(expr, i, numStr)) {
                error = E_BAD_UNARY_MINUS; ok = false; break;
            }

            long long v;
            if (!parseNumber(numStr, v) || v > LIMIT) {
                error = E_NUMBER_TOO_BIG; ok = false; break;
            }
            pushStack(values, numberToString(-v));
            expectOperand = false;
            continue;
        }

        if (c == '(') {
            if (!expectOperand) { error = E_PAREN_AFTER_OPERAND; ok = false; break; }
            pushStack(ops, "(");
            i++;
            expectOperand = true;
            continue;
        }

        if (c == ')') {
            if (expectOperand) { error = E_EMPTY_PARENS; ok = false; break; }

            if (!flushUntilParen(values, ops, error)) { ok = false; break; }
            if (ops.top == 0) { error = E_UNBALANCED_CLOSE; ok = false; break; }

            popStack(ops);
            i++;
            expectOperand = false;
            continue;
        }

        if (isOperator(c)) {
            if (expectOperand) { error = E_OP_IN_WRONG_PLACE; ok = false; break; }

            while (ops.top != 0 && !isTopOpenParen(ops) &&
                   precedence(topOp(ops)) >= precedence(c)) {
                char op = topOp(ops);
                popStack(ops);
                if (!applyOp(values, op, error)) { ok = false; break; }
            }
            if (!ok) break;

            string s = "";
            s = s + c;
            pushStack(ops, s);
            i++;
            expectOperand = true;
            continue;
        }

        error = E_BAD_CHAR + c;
        ok = false;
    }

    if (ok && expectOperand) { error = E_ENDS_WITH_OP; ok = false; }
    if (ok && !flushAll(values, ops, error)) ok = false;

    if (ok) {
        string last = popStack(values);
        if (last.size() == 0) {
            error = E_EMPTY_EXPR; ok = false;
        } else if (values.top != 0) {
            error = E_EXTRA_OPERANDS; ok = false;
        } else {
            long long r;
            if (!parseNumber(last, r)) {
                error = E_BAD_NUMBER; ok = false;
            } else {
                result = r;
            }
        }
    }

    destroyStack(values);
    destroyStack(ops);
    return ok;
}

int main() {
    string expr;
    cout << "Введите выражение: ";
    getline(cin, expr);

    long long result = 0;
    string error;

    if (evaluate(expr, result, error))
        cout << "Результат: " << result << endl;
    else
        cout << "Ошибка: " << error << endl;

    return 0;
}