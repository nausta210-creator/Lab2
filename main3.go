package main

import (
    "bufio"
    "fmt"
    "os"
    "strings"
)

func countIntersection(a, b *Set) int {
    count := 0
    for i := 0; i < a.Size; i++ {
        cur := a.Buckets[i].Head
        for cur != nil {
            if b.Contains(cur.Data) {
                count++
            }
            cur = cur.Next
        }
    }
    return count
}

func main() {
    reader := bufio.NewReader(os.Stdin)
    input, _ := reader.ReadString('\n')
    input = strings.TrimSpace(input)

    var rawSets [100][]string
    setCount := 0
    depth := 0
    cur := ""
    for i := 0; i < len(input); i++ {
        c := input[i]
        if c == '{' {
            depth++
            if depth == 2 {
                cur = ""
                rawSets[setCount] = []string{}
            }
        } else if c == '}' {
            if depth == 2 {
                if cur != "" {
                    rawSets[setCount] = append(rawSets[setCount], cur)
                }
                setCount++
            }
            depth--
        } else if c == ',' || c == ' ' {
            if depth == 2 && cur != "" {
                rawSets[setCount] = append(rawSets[setCount], cur)
                cur = ""
            }
        } else {
            cur += string(c)
        }
    }

    if setCount < 2 {
        return
    }

    sets := make([]*Set, setCount)
    for i := 0; i < setCount; i++ {
        sets[i] = &Set{}
        sets[i].Init(1009)
        for _, v := range rawSets[i] {
            sets[i].Add(v)
        }
    }

    bestI, bestJ, bestCount := 0, 1, -1
    for i := 0; i < setCount; i++ {
        for j := i + 1; j < setCount; j++ {
            c := countIntersection(sets[i], sets[j])
            if c > bestCount {
                bestCount = c
                bestI = i
                bestJ = j
            }
        }
    }

    fmt.Print("{{")
    for k, v := range rawSets[bestI] {
        if k > 0 {
            fmt.Print(", ")
        }
        fmt.Print(v)
    }
    fmt.Print("}, {")
    for k, v := range rawSets[bestJ] {
        if k > 0 {
            fmt.Print(", ")
        }
        fmt.Print(v)
    }
    fmt.Printf("}}, %d\n", bestCount)

    for i := 0; i < setCount; i++ {
        sets[i].Destroy()
    }
}