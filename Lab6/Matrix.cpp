#include "Matrix.h"

void Matrix::resize()
{
	double loadFactor = this->size / this->tableSize;
	if (loadFactor <= 0.7)
		return;

	this->tableSize *= 2;
	cout << tableSize << endl;
	node** newArray = new node*[this->tableSize];
	for (int i = 0; i < this->tableSize; i++) {
		newArray[i] = nullptr;
	}

	for (int i = 0; i < this->tableSize / 2; i++) {
		node* current = this->array[i];

		while (current != nullptr) {
			int position = this->hash(get<0>(current->data), get<1>(current->data));
			node* tempNode = new node;
			tempNode->data = MatrixElem(get<0>(current->data), get<1>(current->data), get<2>(current->data));
			tempNode->next = newArray[position];
			newArray[position] = tempNode;
			current = current->next;
		}
	}

	for (int i = 0; i < this->tableSize/2; i++) {
		node* current = this->array[i];
		while (current != nullptr) {
			node* copy = current->next;
			delete current;
			current = copy;
		}
	}
	delete[] this->array;
	this->array = newArray;
}

Matrix::Matrix(int nrLines, int nrCols)
{
	if (nrLines <= 0 || nrCols <= 0)
		throw exception();

	this->rows = nrLines;
	this->cols = nrCols;
	this->tableSize = 10;
	this->size = 0;

	this->array = new node*[this->tableSize];
	for (int i = 0; i < this->tableSize; i++) {
		this->array[i] = nullptr;
	}
}

TElem Matrix::element(int i, int j) const
{
	if (i < 0 || i >= this->rows || j < 0 || j >= this->cols)
		throw exception();

	int position = this->hash(i, j);
	if (this->array[position] == nullptr) {
		return NULL_TELEM;
	}
	else {
		node* current = this->array[position];
		while (current != nullptr) {
			if (get<0>(current->data) == i && get<1>(current->data) == j) {
				TElem returnValue = get<2>(current->data);
				return returnValue;
			}
			current = current->next;
		}
		delete current;

		return NULL_TELEM;
	}
}

TElem Matrix::modify(int i, int j, TElem e)
{
	if (i < 0 || i >= this->rows || j < 0 || j >= this->cols)
		throw exception();

	this->resize();

	int position = this->hash(i, j);
	if (this->array[position] == nullptr) {
		this->array[position] = new node;
		this->array[position]->data = MatrixElem(i, j, e);
		this->array[position]->next = nullptr;
		this->size++;
		return NULL_TELEM;
	}
	else {
		node* current = this->array[position];
		while (current != nullptr) {
			if (get<0>(current->data) == i && get<1>(current->data) == j) {
				TElem returnValue = get<2>(current->data);
				current->data = MatrixElem(i, j, e);
				return returnValue;
			}
			current = current->next;
		}

		node* tempNode = new node; 
		tempNode->data = MatrixElem(i, j, e);
		tempNode->next = this->array[position];
		this->array[position] = tempNode;
		this->size++;
		
		return NULL_TELEM;
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < this->tableSize; i++) {
		node* current = this->array[i];
		while (current != nullptr) {
			node* copy = current->next;
			delete current;
			current = copy;
		}
	}
	delete[] this->array;
}