// package list

// import "fmt"

// type Node struct {
// 	val  int
// 	next *Node
// }

// type List struct {
// 	head, tail *Node
// 	length     int
// }

// // Size returns number of data elements in list
// func (p *List) Size() int {
// 	return (*p).length
// }

// // Empty bool returns true if empty
// func (p *List) Empty() bool {
// 	if (*p).length == 0 {
// 		return true
// 	} else {
// 		return false
// 	}
// }

// // At returns the value of the nth item (starting at 0 for first)
// func (p *List) At(i int) int {

// 	if i >= (*p).length {
// 		fmt.Println("Index out of range!")
// 		return -1
// 	}
// 	cur := (*p).head
// 	for j := 0; j <= i; j++ {
// 		cur = cur.next
// 	}

// 	return (*cur).val
// }

// // PushFront adds an item to the frontNode of the list
// func (p *List) PushFront(item int) {
// 	frontNode := Node{item, (*p).head.next}
// 	(*p).head.next = &frontNode
// }

// // PopFront remove frontNode item and return its value
// func (p *List) PopFront() {
// 	(*p).head.next = (*p).head.next.next
// }

// // PushBack adds an item at the end
// func (p *List) PushBack(item int) {
// 	endNode := Node{item, (*p).tail.next}
// 	(*p).tail.next.next = &endNode
// 	(*p).tail.next = &endNode
// }

// func (p *List) PopBack() {

// }
