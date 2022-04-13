#include "AVL.h"

using namespace std;

NodeInterface * AVL::getRootNode() const
{
	cout << "In AVL::getRootNode"<<endl;
	return root;
}

bool AVL::add(int data)
{
	cout << "In AVL::add"<<endl;
	bool success;
	success = insert(root, data);
	this->root = balanceTree(root);
	return success;
}

bool AVL::insert(Node *&local_root, int data) {
	cout << "insert" << endl;
	bool success;
	if (local_root == NULL) {
		Node * ptr = new Node(data);
		local_root = ptr;
		treeSize++;
		cout << treeSize << endl;
		cout << data << endl;
		return true;
	} else {
		if (data < local_root->getData()) {
			success = insert(local_root->leftChild, data);
			local_root->updateHeight();
			return success;
		} else if (local_root->getData() < data) {
			success = insert(local_root->rightChild, data);
			local_root->updateHeight();
			return success;
		} else {
			cout << "this item is already in list" << endl;
			return false;
		}
	}
}

bool AVL::remove(int data)
{
	cout << "In AVL::remove"<<endl;
	bool success;
	success = erase(root, data);
	this->root = balanceTree(root);
	return success;
}

bool AVL::erase(Node *& T, int data) {
	cout << "erase" << endl;
	bool success;
	if (T == NULL) {
		cout << "tree is empty or value not found" << endl;
		return false;
	}
	else {
		//recursive find step
		if (T->data > data) {
			cout << "left" << endl;
			success = erase(T->leftChild, data);
			T->updateHeight();
			return success;
		} else if (T->data < data) {
			cout << "right" << endl;
			success = erase(T->rightChild, data);
			T->updateHeight();
			return success;
		} else {
			cout << "found it" << endl;
			//CASE 1: NO CHILDREN
			if (T->leftChild == NULL && T->rightChild == NULL) {
				if (root == T) {
					root == NULL;
				}
				Node * victim = T;
				T = NULL;
				delete victim;
				cout << "remove no children" << endl;
				treeSize--;
				return true;
			}
			//CASE 2: ONE CHILD (right)
			else if (T->leftChild == NULL) {
				Node * victim = T;
				T = T->rightChild;
				if (T == root) {
					root = T;
					cout << "deleting root with one child right, moving root" << endl;
				}
				delete victim;
				cout << "remove one child (right)" << endl;
				treeSize--;
				T->updateHeight();
				return true;
			}
			//CASE 2.5: ONE CHILD (left)
			else if (T->rightChild == NULL) {
				Node * victim = T;
				T = T->leftChild;
				if (T == root) {
					root = T;
					cout << "deleting root with one child left, moving root" << endl;
				}
				delete victim;
				cout << "remove one child (left)" << endl;
				treeSize--;
				T->updateHeight();
				return true;
			}
			//CASE 3: ONE CHILD (left) or TWO CHILDREN
			else {
				int inOrderPred = getInorderPredValue(T);
				cout << "InOrderPred: " << inOrderPred << endl;
				T->data = inOrderPred;
				if (root == T) {
					root = T;
					cout << "deleting root with two children or left child, replacing value" << endl;
				}
				cout << "Value was replaced by " << T->data << endl;
				cout << "remove (two children or left child)" << endl;
				erase(T->leftChild, inOrderPred);
				T->updateHeight();
				return true;
			}
		}
	}
}

void AVL::clear()
{
	while (root != NULL) {
		erase(root, root->data);
	}
	cout << treeSize << endl;
}

int AVL::getInorderPredValue(Node* T) {
	T = T->leftChild;
	while(T->rightChild !=NULL) {
		T = T->rightChild;
	}
		//cout << "In order Predecessor: " << T->data << endl;
	return T->data;
}

Node* AVL::balanceTree(Node * T) {
	cout << "In AVL::balanceTree" << endl;
	if (T == NULL) {
		return T;
	}
	else {
		T->leftChild = balanceTree(T->leftChild);
		T->rightChild = balanceTree(T->rightChild);
		T = balance(T);
		T->updateHeight();
		return T;
	}
}

Node* AVL::balance(Node * T) {
	cout << "In AVL::balance" << endl;
	if (T == NULL) {
		return T;
	}
	else {
		int balance = getBalance(T);
		cout << "Balance: " << balance << endl;
		if (balance > 1) {
			if (getBalance(T->leftChild) >= 0) {
				T = rotateRight(T);
			}
			else {
				T->leftChild = rotateLeft(T->leftChild);
				T = rotateRight(T);
			}
		}
		else if (balance < -1) {
			if (getBalance(T->rightChild) <= 0) {
				T = rotateLeft(T);
			}
			else {
				T->rightChild = rotateRight(T->rightChild);
				T = rotateLeft(T);
			}
		}
		return T;
	}
}

int AVL::getBalance(Node * T) {
	if (T == NULL) {
		return 0;
	}
	else {
		return getHeight(T->leftChild) - getHeight(T->rightChild);
	}
}

int AVL::getHeight(Node * T) {
	if (T == NULL) {
		return 0;
	}
	else {
		return T->height;
	}
}

Node* AVL::rotateRight(Node * T) {
	cout << "In AVL::rotateRight" << endl;
	Node * temp = T->leftChild;
	T->leftChild = temp->rightChild;
	temp->rightChild = T;
	T->height = max(getHeight(T->leftChild), getHeight(T->rightChild)) + 1;
	temp->height = max(getHeight(temp->leftChild), T->height) + 1;
	return temp;
}

Node *AVL::rotateLeft(Node * T) {
	cout << "In AVL::rotateLeft" << endl;
	Node * temp = T->rightChild;
	T->rightChild = temp->leftChild;
	temp->leftChild = T;
	T->height = max(getHeight(T->leftChild), getHeight(T->rightChild)) + 1;
	temp->height = max(getHeight(temp->rightChild), T->height) + 1;
	return temp;
}

//print tree in breadth first order
void AVL::printTree() {
	if (root == NULL) {
		cout << "Tree is empty" << endl;
	}
	else {
		queue<Node*> q;
		q.push(root);
		while (!q.empty()) {
			Node * temp = q.front();
			q.pop();
			cout << temp->data << " ";
			if (temp->leftChild != NULL) {
				q.push(temp->leftChild);
			}
			if (temp->rightChild != NULL) {
				q.push(temp->rightChild);
			}
		}
		cout << endl;
	}
}