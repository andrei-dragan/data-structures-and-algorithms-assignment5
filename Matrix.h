#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

typedef struct node;
struct BSTNode {
	int i, j;
	TElem value;
	BSTNode* left;
	BSTNode* right;
	BSTNode();
};

class Matrix {

private:
	//TODO - Representation
	int n, m;
	BSTNode* root;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//returns the number of non-zero elements from a given column
	//throws an exception if col is not valid
	int numberOfNonZeroElems(int col) const;
};
