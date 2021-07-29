#include "SortedBagIterator.h"
#include <exception>

using namespace std;

// I used the INORDER BINARY TREE ITERATOR (left subtree -> root -> right subtree), so we will get the elements of the bag in increasing order

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    this->stack.index = -1;
    this->stack.data = new BSTNode*[this->bag.size()];

	BSTNode* currNode = this->bag.root;

    while (currNode != nullptr) {
        this->stack.index++;
        this->stack.data[this->stack.index] = currNode;
        currNode = currNode->leftChild;
    }

    if (this->stack.index >= 0)
        this->currentNode = this->stack.data[this->stack.index];
    else
        this->currentNode = nullptr;
}
//Best case: Theta(1), Worst case: Theta(nrOfElems) => Total complexity: O(nrOfElems) (best case when the bag has 1 element, worst case if the BST is degenerate)

TComp SortedBagIterator::getCurrent() {
    if (!this->valid())
        throw exception();
    return this->currentNode->info;
}
//Theta(1)

bool SortedBagIterator::valid() {
    if (this->currentNode == nullptr)
        return false;
    return true;

//    if (this->stack.index == -1)
//        return false;
//    return true;
}
//Theta(1)

void SortedBagIterator::next() {
    if (!this->valid())
        throw exception();

    BSTNode* currNode = this->stack.data[this->stack.index];
    this->stack.index--;

    if (currNode->rightChild != nullptr) {
        currNode = currNode->rightChild;
        while (currNode != nullptr) {
            this->stack.index++;
            this->stack.data[this->stack.index] = currNode;
            currNode = currNode->leftChild;
        }
    }

    if (this->stack.index >= 0)
        this->currentNode = this->stack.data[this->stack.index];
    else
        this->currentNode = nullptr;
}
//Best case: Theta(1), Worst case: Theta(nrOfElems) => Total complexity: O(nrOfElems) (best case when the currentNode doesn't have a right child, worst case when the root has a right child and the left subtree is degenerate)

void SortedBagIterator::first() {
    BSTNode* currNode = this->bag.root;

    this->stack.index = -1;

    while (currNode != nullptr) {
        this->stack.index++;
        this->stack.data[this->stack.index] = currNode;
        currNode = currNode->leftChild;
    }

    if (this->stack.index >= 0)
        this->currentNode = this->stack.data[this->stack.index];
    else
        this->currentNode = nullptr;
}
//Best case: Theta(1), Worst case: Theta(nrOfElems) => Total complexity: O(nrOfElems) (best case when the bag has 1 element, worst case if the BST is degenerate)
