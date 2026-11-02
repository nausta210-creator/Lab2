package main

import (
    "bufio"
    "fmt"
    "os"
    "strconv"
)

type Block struct {
    W, H int64
}

func main() {
    reader := bufio.NewReader(os.Stdin)
    var n int
    fmt.Fscan(reader, &n)

    blocks := &DynamicArray{}
    blocks.Init(n)

    for i := 0; i < n; i++ {
        var w, h int64
        fmt.Fscan(reader, &w, &h)
        blocks.PushBack(strconv.FormatInt(w, 10) + " " + strconv.FormatInt(h, 10))
    }

    vec := make([]Block, n)
    for i := 0; i < n; i++ {
        s := blocks.GetAt(i)
        var w, h int64
        fmt.Sscanf(s, "%d %d", &w, &h)
        vec[i] = Block{W: w, H: h}
    }

    // сортировка пузырьком
    for i := 0; i < n-1; i++ {
        for j := 0; j < n-i-1; j++ {
            if vec[j].W > vec[j+1].W {
                vec[j], vec[j+1] = vec[j+1], vec[j]
            }
        }
    }

    uniqW := []int64{}
    maxH := []int64{}
    for i := 0; i < n; i++ {
        if len(uniqW) == 0 || uniqW[len(uniqW)-1] != vec[i].W {
            uniqW = append(uniqW, vec[i].W)
            maxH = append(maxH, vec[i].H)
        } else {
            if vec[i].H > maxH[len(maxH)-1] {
                maxH[len(maxH)-1] = vec[i].H
            }
        }
    }

    var bestPrev, answer int64
    for i := 0; i < len(uniqW); i++ {
        dp := maxH[i] + bestPrev
        if dp > answer {
            answer = dp
        }
        if dp > bestPrev {
            bestPrev = dp
        }
    }

    fmt.Println(answer)
}