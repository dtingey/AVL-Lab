#pragma once

#include "Node.h"
#include "AVLInterface.h"
#include <iostream>
#include <queue>

using namespace std;

class AVL : public AVLInterface {
public:
	AVL() { cout << "Constructor" << endl; root = NULL;}
	virtual ~AVL() {clear();}

	NodeInterface * getRootNode() const;

	bool add(int data);
	bool insert(Node *&local_root, int data);
	
	bool remove(int data);
	bool erase(Node *& T, int data);

	void clear();
	int getInorderPredValue(Node* T);
	Node* balanceTree(Node* T);
	Node* balance(Node* T);
	int getBalance(Node* T);
	Node* rotateRight(Node* T);
	Node* rotateLeft(Node* T);
	int getHeight(Node* T);
	void printTree();
private:
    Node *root;
	int treeSize = 0;
};