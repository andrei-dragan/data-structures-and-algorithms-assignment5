#include "Matrix.h"
#include <exception>
#include <iostream>
using namespace std;

BSTNode::BSTNode() {
	this->i = -1;
	this->j = -1;
	this->value = NULL_TELEM;
	this->left = NULL;
	this->right = NULL;
} // Theta(1)

Matrix::Matrix(int nrLines, int nrCols) {
	this->n = nrLines;
	this->m = nrCols;
	this->root = NULL;
} // Theta(1)


int Matrix::nrLines() const {
	return this->n;
	return 0;
} // Theta(1)


int Matrix::nrColumns() const {
	return this->m;
	return 0;
} // Theta(1)


TElem Matrix::element(int i, int j) const {
	// Validate the position
	if (!(0 <= i && i < this->n && 0 <= j && j < this->m))
		throw exception();

	// Search for element 
	BSTNode* node = this->root;
	int codeToFind = i * this->m + j;
	while (node != NULL && (node->i * this->m + node->j) != codeToFind) {
		if (codeToFind <= (node->i * this->m + node->j)) node = node->left;
		else node = node->right;
	}

	if (node == NULL)
		return NULL_TELEM;
	else
		return node->value;
} // Best Case: Theta(1), Worst Case: Theta(height) => Total: O(height)

TElem Matrix::modify(int i, int j, TElem e) {
	// Validate the position
	if (!(0 <= i && i < this->n && 0 <= j && j < this->m))
		throw exception();

	// Search for element and modify
	BSTNode* prev = NULL;
	BSTNode* node = this->root;
	int codeToFind = i * this->m + j;
	while (node != NULL && (node->i * this->m + node->j) != codeToFind) {
		prev = node;
		if (codeToFind <= (node->i * this->m + node->j)) node = node->left;
		else node = node->right;
	}

	if (node != NULL) {
		// the node is already in the BST - we just change the value
		if (e != NULL_TELEM) {
			TElem oldValue = node->value;
			node->value = e;
			return oldValue;
		}
		else {
			// we need to delete it
			TElem oldValue = node->value;
			if (node->left == NULL || node->right == NULL) {
				BSTNode* newNode = NULL;
				if (node->left == NULL) newNode = node->right;
				else newNode = node->left;

				if (prev == NULL) this->root = newNode;
				else if (prev->left == node)prev->left = newNode;
				else if (prev->right == node)prev->right = newNode;
				free(node);
			}
			else {
				BSTNode* prev_next = NULL;
				BSTNode* next = node->right;
				while (next->left != NULL) {
					prev_next = next;
					next = next->left;
				}

				if (prev_next != NULL) prev_next->left = next->right;
				else node->right = next->right;
				node->i = next->i;
				node->j = next->j;
				node->value = next->value;
				free(next);
			}
			return oldValue;
		}
	}
	else {
		// we need to add it in the BST
		if (prev == NULL) {
			// we create the root
			BSTNode* nodeToAdd = new BSTNode();
			nodeToAdd->i = i;
			nodeToAdd->j = j;
			nodeToAdd->value = e;
			nodeToAdd->left = NULL;
			nodeToAdd->right = NULL;
			this->root = nodeToAdd;
		}
		else {
			if (codeToFind <= (prev->i * this->m + prev->j)) { // add it to the left
				BSTNode* nodeToAdd = new BSTNode();
				nodeToAdd->i = i;
				nodeToAdd->j = j;
				nodeToAdd->value = e;
				nodeToAdd->left = NULL;
				nodeToAdd->right = NULL;
				prev->left = nodeToAdd;
			}
			else { // add it to the right
				BSTNode* nodeToAdd = new BSTNode();
				nodeToAdd->i = i;
				nodeToAdd->j = j;
				nodeToAdd->value = e;
				nodeToAdd->left = NULL;
				nodeToAdd->right = NULL;
				prev->right = nodeToAdd;
			}
		}
		return NULL_TELEM;
	}
} // Best Case: Theta(1), Worst Case: Theta(height) => Total: O(height)


int Matrix::numberOfNonZeroElems(int col) const {
	// Validate the position
	if (!(0 <= col && col < this->m))
		throw exception();

	int ans = 0;

	for (int i = 0; i < this->n; i++) {
		int codeToFind = i * this->m + col;
		BSTNode* node = this->root;
		while (node != NULL && (node->i * this->m + node->j) != codeToFind) {
			if (codeToFind <= (node->i * this->m + node->j)) node = node->left;
			else node = node->right;
		}
		if (node != NULL)ans++;
	}
	return ans;
} // Best Case: Theta(1 + 2 + ... + heigth = height * (heigth + 1) / 2), Worst Case: Theta(n * height) => Total: O(n * height)