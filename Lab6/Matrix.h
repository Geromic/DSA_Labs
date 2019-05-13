#pragma once
#include <iostream>
#include <tuple>
#include <exception>

using namespace std;

typedef int TElem;

#define NULL_TELEM 0

typedef tuple<int, int, TElem> MatrixElem;

typedef struct node{
	MatrixElem data;
	node* next;
} node;

class Matrix {
private:
	/*representation of the matrix*/
	node** array;
	int tableSize;
	int rows, cols;
	int size;
	int hash(int row, int col) const { return (row % this->tableSize + col % this->tableSize) % this->tableSize; };
	void resize();

public:
	//constructor
	//throws exception if nrLines or nrCols is negative or zero
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const { return this->rows; };

	//returns the number of columns
	int nrColumns() const { return this->cols; };

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	~Matrix();
};