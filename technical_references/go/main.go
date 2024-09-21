package main

import (
	"fmt"
	"math/rand"
)

func add(x int, y int) int {
	return x + y
}

func swap(x int, y int) (int, int) {
	return y, x
}

type Vertex struct {
	X int
	Y int
}

func main() {
	fmt.Println("My favorite number is", rand.Intn(10))
	fmt.Println(add(3, 4))
	fmt.Println(swap(3, 4))
	v := Vertex{1, 2}
	fmt.Println(v)
	v.X = 3
	fmt.Println(v.X)
}

