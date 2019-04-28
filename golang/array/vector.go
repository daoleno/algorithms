package vector

import "errors"

// Vector is
type Vector []int

const initSize = 8

func (p *Vector) realloc(length, capcacity int) (b Vector) {
	if capcacity < initSize {
		capcacity = initSize
	}

	if capcacity < length {
		capcacity = length
	}

	b = make(Vector, length, capcacity)
	copy(b, *p)
	*p = b

	return b
}

func (p *Vector) expand(i, n int) {
	a := *p

	len0 := len(a)
	len1 := len0 + n

	if len1 <= cap(a) {
		// Space is enough
		a = a[0:len0]
	} else {
		// Space is not enough.Double space
		newCap := cap(a) * 2
		if newCap < len1 {
			// Still not enough.set request length as capcacity
			newCap = len1
		}

		a = p.realloc(n, newCap)
	}

	// if i = 3, n = 1
	//		[*******] --> [***0****]

	for j := len0 - 1; j > i; j-- {
		a[j+n] = a[j]
	}

	*p = a
}

// Resize resize length and capcacity of vector
func (p *Vector) Resize(length, capcacity int) {
	a := *p

	if length > cap(a) || capcacity > cap(a) {
		a = p.realloc(length, capcacity)
	} else if length < len(a) {
		// clear trailing element
		for i := length + 1; i < len(a); i++ {
			var zero int
			a[i] = zero
		}

	}
}

// Size number of items
func (p *Vector) Size() int {

	return len(*p)
}

// Capcacity number of items it can hold
func (p *Vector) Capcacity() int {
	return cap(*p)
}

// IsEmpty check whether vector is empty
func (p *Vector) IsEmpty() bool {
	if len(*p) == 0 {
		return true
	} else {
		return false
	}
}

// At returns item at given index, blows up if index out of bounds
func (p *Vector) At(i int) int {
	return (*p)[i]
}

// Insert inserts item at index, shifts that index's value and trailing elements to the right
func (p *Vector) Insert(i, item int) {
	p.expand(i, 1)
	(*p)[i] = item
}

// Push add item at end of vector
func (p *Vector) Push(item int) {
	p.expand(len(*p), 1)
	(*p)[len(*p)] = item
}

// Prepend add item at begin of vector
func (p *Vector) Prepend(item int) {
	p.Insert(0, item)
}

// Delete delete item at index, shifting all trailing elements left
func (p *Vector) Delete(i int) {
	a := *p
	n := len(a)
	copy(a[i:n-1], a[i+1:n])
	// for GC
	var zero int
	a[n-1] = zero

	*p = a[0 : n-1]
}

// Remove looks for value and removes index holding it (even if in multiple places)
func (p *Vector) Remove(item int) {
	// TODO: index will be changed ?
	for i, x := range *p {
		if x == item {
			p.Delete(i)
		}
	}
}

// Pop remove from end, return value
func (p *Vector) Pop() int {
	a := *p
	n := len(a)
	item := a[n]
	p.Delete(n)
	return item
}

// Find looks for value and returns first index with that value, -1 if not found
func (p *Vector) Find(item int) (i int, err error) {

	for i, x := range *p {
		if x == item {
			return i, nil
		}
	}
	err = errors.New("Can't find anything")
	return -1, err
}
