// Circular linked list

package main

import "fmt"

type node_t struct {
	next  *node_t
	prior *node_t
	data  interface{}
}

type RingList struct {
	head *node_t
	sz   int
}

func (lst *RingList) size() int {
	return lst.sz
}

func (lst *RingList) isEmpty() bool {
	return lst.head == nil
}

func (lst *RingList) push(value interface{}) *node_t {

	new_node := node_t{next: nil, prior: nil, data: value}

	if lst.isEmpty() {
		new_node.next = &new_node
		new_node.prior = &new_node
		lst.head = &new_node
	} else {

		last_node := lst.head.prior

		for i := 0; i < lst.sz-1; i++ {
			last_node = last_node.next
		}

		new_node.prior = last_node
		new_node.next = last_node.next
		last_node.next = &new_node
	}

	lst.sz++
	return &new_node
}

func (lst *RingList) insert_after(node *node_t, value interface{}) {

	if node != nil {
		new_node := node_t{next: nil, prior: nil, data: value}

		if lst.isEmpty() {
			new_node.next = &new_node
			new_node.prior = &new_node
			lst.head = &new_node
		} else {
			new_node.prior = node
			new_node.next = node.next
			node.next = &new_node
		}

		lst.sz++
	}
}

func (lst *RingList) print() {

	tmp := lst.head

	for sz := 0; sz < lst.size(); sz++ {
		fmt.Println(tmp.data)
		tmp = tmp.next
	}

}

func (lst *RingList) node(idx int) *node_t {

	if idx > lst.sz {
		return nil
	}

	tmp := lst.head

	for sz := 0; sz < idx; sz++ {
		tmp = tmp.next
	}

	return tmp
}

func (lst *RingList) remove(node *node_t) {

	if node != nil {

		if lst.sz == 1 {
			lst.head = nil
			lst.sz--
			return
		}

		node.prior.next = node.next
		node.next.prior = node.prior

		if node == lst.head {
			lst.head = lst.head.next
		}

		lst.sz--
	}

}

func (lst *RingList) count(value interface{}) int {

	counter := 0
	n := lst.head

	for i := 0; i < lst.sz; i++ {
		if n.data == value {
			counter++
		}

		n = n.next
	}

	return counter
}

func main() {

	ring := new(RingList)

	// ulozme data na konec seznamu
	ring.push(1)
	ring.push(2)
	ring.push(3)
	n := ring.push(4) // funkce push na vraci na nove vytvoreny node

	// take muzeme ulozit dalsi uzel za uzel ktery chceme
	ring.insert_after(n, 6)
	ring.insert_after(n, 5)

	ring.print()
	fmt.Println("-------")

	// ziskame ukazatel na dany uzel
	n = ring.node(3)
	ring.remove(n)

	ring.print()
	fmt.Println("-------")

	n = ring.node(1)
	ring.insert_after(n, 3)
	ring.insert_after(n, 3)
	ring.insert_after(n, 3)
	ring.insert_after(n, 3)

	ring.print()

	// a vyhledame pocet opakovani dane hodnoty v seznamu
	count_of_item := ring.count(3)
	fmt.Printf("Total count = %v \n", count_of_item)
}
