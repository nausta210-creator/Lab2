package main

import (
    "bufio"
    "fmt"
    "os"
    "strconv"
    "strings"
)

const limit = 2000000000

func isDigit(c byte) bool { return c >= '0' && c <= '9' }
func isSpace(c byte) bool { return c == ' ' || c == '\t' || c == '\n' || c == '\r' }
func isOperator(c byte) bool { return c == '+' || c == '-' || c == '*' }

func precedence(op byte) int {
    if op == '*' {
        return 2
    }
    if op == '+' || op == '-' {
        return 1
    }
    return 0
}

func topOp(s *Stack) byte {
    if s.Top == nil {
        return 0
    }
    return s.Top.Data[0]
}

func isTopOpenParen(s *Stack) bool {
    return s.Top != nil && s.Top.Data == "("
}

func applyOp(values *Stack, op byte) (string, bool) {
    bStr := values.Pop()
    aStr := values.Pop()
    if bStr == "" || aStr == "" {
        return "Не хватает чисел", false
    }
    a, _ := strconv.ParseInt(aStr, 10, 64)
    b, _ := strconv.ParseInt(bStr, 10, 64)
    var res int64
    switch op {
    case '+':
        res = a + b
    case '-':
        res = a - b
    case '*':
        res = a * b
    }
    if res > limit || res < -limit {
        return "Переполнение", false
    }
    values.Push(strconv.FormatInt(res, 10))
    return "", true
}

func flushUntilParen(values, ops *Stack) (string, bool) {
    for ops.Top != nil && !isTopOpenParen(ops) {
        op := ops.Pop()[0]
        if err, ok := applyOp(values, op); !ok {
            return err, false
        }
    }
    return "", true
}

func flushAll(values, ops *Stack) (string, bool) {
    for ops.Top != nil {
        if isTopOpenParen(ops) {
            return "Не закрыта скобка", false
        }
        op := ops.Pop()[0]
        if err, ok := applyOp(values, op); !ok {
            return err, false
        }
    }
    return "", true
}

func evaluate(expr string) (int64, string) {
    values := &Stack{}
    values.Init()
    ops := &Stack{}
    ops.Init()

    expectOperand := true
    i := 0
    n := len(expr)

    for i < n {
        c := expr[i]
        if isSpace(c) {
            i++
            continue
        }
        if isDigit(c) {
            if !expectOperand {
                return 0, "Два числа подряд"
            }
            j := i
            for j < n && isDigit(expr[j]) {
                j++
            }
            numStr := expr[i:j]
            v, _ := strconv.ParseInt(numStr, 10, 64)
            if v > limit {
                return 0, "Число слишком большое"
            }
            values.Push(numStr)
            i = j
            expectOperand = false
            continue
        }
        if c == '-' && expectOperand {
            i++
            for i < n && isSpace(expr[i]) {
                i++
            }
            j := i
            for j < n && isDigit(expr[j]) {
                j++
            }
            if j == i {
                return 0, "После минуса нет числа"
            }
            v, _ := strconv.ParseInt(expr[i:j], 10, 64)
            values.Push(strconv.FormatInt(-v, 10))
            i = j
            expectOperand = false
            continue
        }
        if c == '(' {
            if !expectOperand {
                return 0, "Скобка не на месте"
            }
            ops.Push("(")
            i++
            expectOperand = true
            continue
        }
        if c == ')' {
            if expectOperand {
                return 0, "Пустые скобки"
            }
            if err, ok := flushUntilParen(values, ops); !ok {
                return 0, err
            }
            if ops.Top == nil {
                return 0, "Лишняя )"
            }
            ops.Pop()
            i++
            expectOperand = false
            continue
        }
        if isOperator(c) {
            if expectOperand {
                return 0, "Оператор не на месте"
            }
            for ops.Top != nil && !isTopOpenParen(ops) && precedence(topOp(ops)) >= precedence(c) {
                op := ops.Pop()[0]
                if err, ok := applyOp(values, op); !ok {
                    return 0, err
                }
            }
            ops.Push(string(c))
            i++
            expectOperand = true
            continue
        }
        return 0, "Неизвестный символ"
    }

    if expectOperand {
        return 0, "Выражение заканчивается оператором"
    }
    if err, ok := flushAll(values, ops); !ok {
        return 0, err
    }

    last := values.Pop()
    if last == "" {
        return 0, "Пустое выражение"
    }
    if values.Top != nil {
        return 0, "Лишние числа"
    }
    res, _ := strconv.ParseInt(last, 10, 64)
    return res, ""
}

func main() {
    reader := bufio.NewReader(os.Stdin)
    fmt.Print("Введите выражение: ")
    expr, _ := reader.ReadString('\n')
    expr = strings.TrimRight(expr, "\r\n")

    res, err := evaluate(expr)
    if err == "" {
        fmt.Printf("Результат: %d\n", res)
    } else {
        fmt.Printf("Ошибка: %s\n", err)
    }
}