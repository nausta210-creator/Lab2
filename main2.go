package main

import (
    "bufio"
    "fmt"
    "os"
    "strings"
)

func main() {
    filePath := ""
    query := ""

    for i := 1; i < len(os.Args); i++ {
        if os.Args[i] == "--file" && i+1 < len(os.Args) {
            filePath = os.Args[i+1]
            i++
        } else if os.Args[i] == "--query" && i+1 < len(os.Args) {
            query = os.Args[i+1]
            i++
        }
    }

    s := &Set{}
    s.Init(1009)

    if filePath != "" {
        f, err := os.Open(filePath)
        if err != nil {
            fmt.Fprintln(os.Stderr, "Ошибка открытия файла")
            return
        }
        defer f.Close()
        sc := bufio.NewScanner(f)
        for sc.Scan() {
            line := sc.Text()
            if line != "" {
                s.Add(line)
            }
        }
    }

    tokens := strings.Fields(query)
    for i := 0; i+1 < len(tokens); i += 2 {
        cmd := tokens[i]
        arg := tokens[i+1]
        switch cmd {
        case "SETADD":
            s.Add(arg)
            fmt.Printf("SETADD %s -> OK\n", arg)
        case "SETDEL":
            s.Del(arg)
            fmt.Printf("SETDEL %s -> OK\n", arg)
        case "SET_AT":
            if s.Contains(arg) {
                fmt.Printf("SET_AT %s -> YES\n", arg)
            } else {
                fmt.Printf("SET_AT %s -> NO\n", arg)
            }
        }
    }
    s.Destroy()
}