#include "Node.h"

int Node::getData() const
{
    cout << "getData"<<endl;
    return data;
}

NodeInterface * Node::getLeftChild() const
{
    cout << "getLeftChild"<<endl;
    return leftChild;
}

NodeInterface * Node::getRightChild() const
{
    cout << "getRightChild"<<endl;
    return rightChild;
}

/*
* Returns the height of this node. The height is the number of nodes
* along the longest path from this node to a leaf.  While a conventional
* interface only gives information on the functionality of a class and does
* not comment on how a class should be implemented, this function has been
* provided to point you in the right direction for your solution.  For an
* example on height, see page 448 of the text book.
*
* @return the height of this tree with this node as the local root.
*/
int Node::getHeight()
{
    cout << "getHeight"<<endl;
    return height;
}

void Node::setLeftChild(Node *ptr)
{
      cout << "setLeft"<<endl;
      leftChild = ptr;
}
void Node::setRightChild(Node *ptr)
{
      cout << "setRight"<<endl;
      rightChild = ptr;
}

void Node::setHeight(int h)
{
      cout << "setHeight"<<endl;
      height = h;
}

void Node::updateHeight()
{
      cout << "updateHeight"<<endl;
      int leftHeight = 0;
      int rightHeight = 0;
      if (leftChild != NULL)
            leftHeight = leftChild->getHeight();
      if (rightChild != NULL)
            rightHeight = rightChild->getHeight();
      height = max(leftHeight, rightHeight) + 1;
}