#pragma once
#include <utility>

#include <iostream>
#include <climits>
using namespace std;

typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool(*Relation)(TPriority p1, TPriority p2);

class ThirdPriorityQueue
{
private:
	//representation of the ThirdPriorityQueue
	Element* data;
	Relation r;
	int cap;
	int len;

	void resize();
	void bubbleDown(int pos);
public:
	//implicit constructor
	ThirdPriorityQueue(Relation r);
	//adds an element with a priority to the queue
	void push(TElem e, TPriority p);

	//returns the element with the third highest priority with respect to the relation
	//throws exception if the queue has less than 3 elements
	Element top();

	//removes and returns the element with the third highest priority
	//throws exception if the queue has less than 3 elements
	Element pop();

	//checks if the queue has at most two elements
	bool atMostTwo();

	 //destructor
	~ThirdPriorityQueue() { delete[] this->data; };

	void printQueue() {
		int lvl = 1, current;
		int i = 1;
		while (i <= this->len) {
			current = 1;
			while (current <= lvl && i <=this->len) {
				std::cout << this->data[i].second << " ";
				current++;
				i++;
			}
			std::cout << endl;
			lvl *= 2;
		}
	};
};

