#include "ThirdPriorityQueue.h"

#include <exception>

void ThirdPriorityQueue::resize()
{
	this->cap *= 2;
	Element* aux = new Element[this->cap];
	for (int i = 0; i < this->cap; i++)
		aux[i].second = -INT_MAX;
	for (int i = 0; i <= this->len; i++) {
		aux[i] = this->data[i];
	}
	delete[] this->data;
	this->data = aux;
}

void ThirdPriorityQueue::bubbleDown(int p)
{
	int pos = p;
	Element elem = this->data[p];
	Element tmp;
	while (pos < this->len) {
		int maxChild = -1;
		if (pos * 2 <= this->len) {
			//it has a left child, so we assume it is the "best"
			maxChild = pos * 2;
		}
		if (pos * 2 + 1 <= this->len && r(this->data[2 * pos + 1].second, this->data[2 * pos].second)) {
			maxChild = pos * 2 + 1;
		}
		if (maxChild != -1 && r(this->data[maxChild].second, elem.second)) {
			tmp = this->data[pos];
			this->data[pos] = this->data[maxChild];
			this->data[maxChild] = tmp;
			pos = maxChild;
		}
		else {
			pos = this->len + 1;
		}
	}
}

ThirdPriorityQueue::ThirdPriorityQueue(Relation r)
{
	//t(1)
	this->cap = 10;
	this->len = 0;
	this->data = new Element[this->cap];
	this->r = r;
	for (int i = 0; i < this->cap; i++) {
		this->data[i].second = INT_MIN;
	}
}

void ThirdPriorityQueue::push(TElem e, TPriority p)
{
	//t(n)
	if (this->len+1 == this->cap) resize();

	this->data[this->len+1] = Element(e, p);
	this->len++;

	//this is fun
	int position = this->len;
	Element elem = this->data[position];
	int parent = position / 2;
	while (position > 1 && this->r(elem.second, this->data[parent].second) == true) {
		this->data[position] = this->data[parent];
		position = parent;
		parent = position / 2;
	}
	this->data[position] = elem;
}

Element ThirdPriorityQueue::top()
{
	//t(1)
	if (this->len < 3)
		throw std::exception("You need 3 elems \n");
	if (r(this->data[2].second, this->data[3].second)) {
		//"maxim" dintre 3, 4, 5 daca exista
		if (this->data[4].second == -INT_MAX && this->data[5].second == -INT_MAX)
			return data[3];
		if (this->data[4].second == -INT_MAX) {
			if (this->r(this->data[3].second, this->data[5].second))
				return data[3];
			return data[5];
		}
		if (this->data[5].second == -INT_MAX) {
			if (this->r(this->data[3].second, this->data[4].second))
				return data[3];
			return data[4];
		}
		if (this->data[4].second != -INT_MAX && this->data[5].second != -INT_MAX) {
			if (this->r(this->data[4].second, this->data[5].second)) {
				if (this->r(this->data[3].second, this->data[4].second))
					return data[3];
				return data[4];
			}
			if (this->r(this->data[3].second, this->data[5].second))
				return data[3];
			return data[5];
		}
	}
	else {
		//"best of" dintre 2, 6, 7
		if (this->data[6].second == -INT_MAX && this->data[7].second == -INT_MAX)
			return data[2];
		if (this->data[6].second == -INT_MAX) {
			if (this->r(this->data[2].second, this->data[7].second))
				return data[2];
			return data[7];
		}
		if (this->data[7].second == -INT_MAX) {
			if (this->r(this->data[2].second, this->data[6].second))
				return data[2];
			return data[6];
		}
		if (this->data[6].second != -INT_MAX && this->data[7].second != -INT_MAX) {
			if (this->r(this->data[6].second, this->data[7].second)) {
				if (this->r(this->data[2].second, this->data[6].second))
					return data[2];
				return data[6];
			}
			if (this->r(this->data[2].second, this->data[7].second))
				return data[2];
			return data[7];
		}
	}
}

Element ThirdPriorityQueue::pop()
{
	//o(n)
	if (this->len < 3)
		throw std::exception("Too few elems!");

	int p;

	if (r(this->data[2].second, this->data[3].second)) {
		//"best of" dintre 3, 4, 5 daca exista
		if (this->data[4].second == -INT_MAX && this->data[5].second == -INT_MAX)
			p = 3;
		else if (this->data[4].second == -INT_MAX) {
			if (this->r(this->data[3].second, this->data[5].second))
				p = 3;
			else p = 5;
		}
		else if (this->data[5].second == -INT_MAX) {
			if (this->r(this->data[3].second, this->data[4].second))
				p = 3;
			else p = 4;
		}
		if (this->data[4].second != -INT_MAX && this->data[5].second != -INT_MAX) {
			if (this->r(this->data[4].second, this->data[5].second)) {
				if (this->r(this->data[3].second, this->data[4].second))
					p = 3;
				else p = 4;
			}
			else if (this->r(this->data[3].second, this->data[5].second))
				p = 3;
			else p = 5;
		}
	}
	else {
		//"best of" dintre 2, 6, 7
		if (this->data[6].second == -INT_MAX && this->data[7].second == -INT_MAX)
			p = 2;
		else if (this->data[6].second == -INT_MAX) {
			if (this->r(this->data[2].second, this->data[7].second))
				p = 2;
			else p = 7;
		}
		else if (this->data[7].second == -INT_MAX) {
			if (this->r(this->data[2].second, this->data[6].second))
				p = 2;
			else p = 6;
		}
		else if (this->data[6].second != -INT_MAX && this->data[7].second != -INT_MAX) {
			if (this->r(this->data[6].second, this->data[7].second)) {
				if (this->r(this->data[2].second, this->data[6].second))
					p = 2;
				else p = 6;
			}
			else if (this->r(this->data[2].second, this->data[7].second))
				p = 2;
			else p = 7;
		}
	}

	int parent;
	Element deleted = this->data[p];

	this->data[p] = this->data[this->len];
	this->len--;

	bubbleDown(p);
	this->data[len + 1].second = -INT_MAX;
	return deleted;
}

bool ThirdPriorityQueue::atMostTwo()
{
	//t(1)
	return this->len <= 2;
}

