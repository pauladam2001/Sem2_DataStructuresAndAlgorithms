#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>

//best case for complexities not exactly good (don't need to consider the case when nrOfElems = 1 the best case)
//and also when i have 2 whiles the complex. is O(nrOfElems + nrOfElems)

SortedBag::SortedBag(Relation r) {
	this->root = nullptr;
	this->nrOfElems = 0;
	this->relation = r;
}
//Theta(1)

void SortedBag::add(TComp e) {
	BSTNode* currentNode = this->root;
	BSTNode* parentNode = nullptr;      // we also need to have the parent in order to set the links

	BSTNode* newNode = new BSTNode{};
	newNode->info = e;                  // initializing the node that will be added
	newNode->leftChild = nullptr;
	newNode->rightChild = nullptr;

    while (currentNode != nullptr) {
        parentNode = currentNode;
        if (this->relation(newNode->info, currentNode->info))       //if elem "<=" (for example) than the currentNode, we go to the left subtree
            currentNode = currentNode->leftChild;
        else
            currentNode = currentNode->rightChild;                  //otherwise we go to the right subtree
    }

    if (parentNode == nullptr)          //means the bag is empty, so we add in the root
        this->root = newNode;
    else {                              // decide in what direction to add the new node, left or right
        if (this->relation(newNode->info, parentNode->info))
            parentNode->leftChild = newNode;
        else
            parentNode->rightChild = newNode;
    }

    this->nrOfElems++;
}
//Best case: Theta(1), Worst case: Theta(nrOfElems) => Total complexity: O(nrOfElems) (best case when the bag is empty, worst case if the BST is degenerate and the element should be one of the leaves)

bool SortedBag::remove(TComp e) {
    BSTNode* parentNodeToBeRemoved = nullptr;       //we need the parent in order to make the connections
    BSTNode* currentNodeToBeRemoved = nullptr;

    BSTNode* traverseParentNode = nullptr;
    BSTNode* traverseCurrentNode = this->root;

    while(traverseCurrentNode != nullptr) {              //same while with the function nrOccurrences
                                                        //if e appears multiple times, we need the last appearance of e in the BST, because,
        if(traverseCurrentNode->info == e) {            //otherwise, the recursive call of the function (when whe have 2 descendants) will get
            parentNodeToBeRemoved = traverseParentNode;    // into an infinite cycle (the maximum and e will have the same value)
            currentNodeToBeRemoved = traverseCurrentNode;
        }
        if(this->relation(e, traverseCurrentNode->info)) {          //if elem "<=" (for example) than the currentNode, we go to the left subtree
            traverseParentNode = traverseCurrentNode;
            traverseCurrentNode = traverseCurrentNode->leftChild;
        }
        else {
            traverseParentNode = traverseCurrentNode;               //otherwise we go to the right subtree
            traverseCurrentNode = traverseCurrentNode->rightChild;
        }
    }

    if(currentNodeToBeRemoved == nullptr)       //if we didn't find the element in the BST
        return false;

    int nrOfDescendants = 0;
    if(currentNodeToBeRemoved->leftChild != nullptr)
        nrOfDescendants++;                                  // compute how many descendants the node to be removed has
    if(currentNodeToBeRemoved->rightChild != nullptr)
        nrOfDescendants++;

    if(nrOfDescendants == 0) {       // if it has no descendants we set the corresponding child of the parent to nullptr
        if(currentNodeToBeRemoved == this->root) {       //the node to be removed is the root
            delete currentNodeToBeRemoved;
            this->root = nullptr;
        }
        else {       //the node to be removed is a leaf
            if(parentNodeToBeRemoved->leftChild == currentNodeToBeRemoved)    //we check if it is the left child or the right child
                parentNodeToBeRemoved->leftChild = nullptr;
            else
                parentNodeToBeRemoved->rightChild = nullptr;
            delete currentNodeToBeRemoved;
        }

        this->nrOfElems--;
        return true;
    }
    else if(nrOfDescendants == 1) {      //if it has 1 descendant we set the corresponding child of the parent to the descendant
        if(currentNodeToBeRemoved == this->root) {      //the node to be removed is the root (and has 1 child)
            if(currentNodeToBeRemoved->leftChild != nullptr)  //we check if the node to be removed has a left child or a right child
                this->root = this->root->leftChild;
            else
                this->root = this->root->rightChild;
            delete currentNodeToBeRemoved;
        }
        else {      //the node to be removed is not the root and it has a parent and 1 child (we make the child of the parent to be the descendant)
            if(currentNodeToBeRemoved->leftChild != nullptr) {  //if the node to be removed has a left child
                if(parentNodeToBeRemoved->leftChild == currentNodeToBeRemoved) //we check if the node to be removed is the left or the right child
                    parentNodeToBeRemoved->leftChild = currentNodeToBeRemoved->leftChild;       //of the parent
                else
                    parentNodeToBeRemoved->rightChild = currentNodeToBeRemoved->leftChild;
            }
            else {  //if the node to be removed has a right child
                if(parentNodeToBeRemoved->leftChild == currentNodeToBeRemoved)  //we check if the node to be removed is the left or the right child
                    parentNodeToBeRemoved->leftChild = currentNodeToBeRemoved->rightChild;      //of the parent
                else
                    parentNodeToBeRemoved->rightChild = currentNodeToBeRemoved->rightChild;
            }
            delete currentNodeToBeRemoved;
        }

        this->nrOfElems--;
        return true;
    }//if it has 1 descendant we set the corresponding child of the parent to the descendant
    else {  //if it has 2 descendants we find the maximum of the left subtree, move it to the node to be removed and delete the maximum
        BSTNode* replaceNode = get_maximum(currentNodeToBeRemoved->leftChild);
        TElem max = replaceNode->info;
        remove(max);            //recursive call of the function in order to delete the maximum
        currentNodeToBeRemoved->info = max;

        return true;
    }
}
//Best case: Theta(1), Worst case: Theta(nrOfElems) => Total complexity: O(nrOfElems) (best case when the bag has 1 element, worst case when the bag has multiple elements and the node has 2 children, so we have to call the recursive function (2*O(nrOfElems))

bool SortedBag::search(TComp elem) const {
	BSTNode* currentNode = this->root;

    while (currentNode != nullptr) {
        if (currentNode->info == elem)
            return true;
        if (this->relation(elem, currentNode->info))    //if elem "<=" (for example) than the currentNode, we go to the left subtree
            currentNode = currentNode->leftChild;
        else
            currentNode = currentNode->rightChild;      //otherwise we go to the right subtree
    }
    return false;
}
//Best case: Theta(1), Worst case: Theta(nrOfElems) => Total complexity: O(nrOfElems) (best case when the searched element is the root, worst case when the BST is degenerate and the element doesn't exist)

int SortedBag::nrOccurrences(TComp elem) const {
	int ct = 0;
	BSTNode* currentNode = this->root;

    while (currentNode != nullptr) {
        if (currentNode->info == elem)
            ct++;
        if(this->relation(elem, currentNode->info))     //if elem "<=" (for example) than the currentNode, we go to the left subtree
            currentNode = currentNode->leftChild;
        else
            currentNode = currentNode->rightChild;      //otherwise we go to the right subtree
    }
    return ct;
}
//Best case: Theta(1), Worst case: Theta(nrOfElems) => Total complexity: O(nrOfElems) (best case when the bag has no elements, worst case if the BST is degenerate)

int SortedBag::size() const {
	return this->nrOfElems;
}
//Theta(1)

bool SortedBag::isEmpty() const {
    if (this->nrOfElems == 0)
        return true;
    return false;
}
//Theta(1)

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
//Theta(1)

SortedBag::~SortedBag() {
    this->stack.index = -1;
    this->stack.data = new BSTNode*[this->size()];
	BSTNode* currentNode = this->root;
	BSTNode* deletedNode;

    while (currentNode != nullptr) {
        this->stack.index++;
        this->stack.data[this->stack.index] = currentNode;
        currentNode = currentNode->leftChild;
    }
                                                                            // I used INORDER TRAVERSAL
    while (this->stack.index >= 0) {
        currentNode = this->stack.data[this->stack.index];
        this->stack.index--;
        deletedNode = currentNode;
        currentNode = currentNode->rightChild;

        while (currentNode != nullptr) {
            this->stack.index++;
            this->stack.data[this->stack.index] = currentNode;
            currentNode = currentNode->leftChild;
        }
        delete deletedNode;
    }
}
//Theta(nrOfElems)

BSTNode* SortedBag::get_maximum(BSTNode *node) {
    BSTNode* currentNode = new BSTNode{};
    currentNode->info = node->info;
    currentNode->leftChild = node->leftChild;
    currentNode->rightChild = node->rightChild;

    while (currentNode->rightChild != nullptr)
        currentNode = currentNode->rightChild;

    return currentNode;
}
//Best case: Theta(1), Worst case: Theta(nrOfElems) => Total complexity: O(nrOfElems) (best case when the maximum element is the node, worst case when the BST is degenerate and the maximum is the leaf)


void SortedBag::addOccurrences(int nr, TComp elem) {
    if (nr < 0)
        throw std::exception();

    BSTNode* currentNode = this->root;
    BSTNode* parentNode = nullptr;      // we also need to have the parent in order to set the links

    BSTNode* newNode = new BSTNode{};
    newNode->info = elem;                  // initializing the node that will be added
    newNode->leftChild = nullptr;
    newNode->rightChild = nullptr;

    while (currentNode != nullptr) {
        parentNode = currentNode;
        if (this->relation(newNode->info, currentNode->info))       //if elem "<=" (for example) than the currentNode, we go to the left subtree
            currentNode = currentNode->leftChild;
        else
            currentNode = currentNode->rightChild;                  //otherwise we go to the right subtree
    }

    if (parentNode == nullptr) {
        currentNode = newNode;    // currentNode = this->root
        nr--;
        this->nrOfElems++;
        while (nr > 0) {
            BSTNode* newNode1 = new BSTNode{};
            newNode1->info = elem;                  // initializing the node that will be added
            newNode1->leftChild = nullptr;
            newNode1->rightChild = nullptr;
            if (this->relation(newNode1->info, currentNode->info)) {
                currentNode->leftChild = newNode1;
                currentNode = currentNode->leftChild;
            }
            else {
                currentNode->rightChild = newNode1;
                currentNode = currentNode->rightChild;
            }
            nr--;
            this->nrOfElems++;
        }
    }
    else {
        while (nr > 0) {
            BSTNode* newNode1 = new BSTNode{};
            newNode1->info = elem;                  // initializing the node that will be added
            newNode1->leftChild = nullptr;
            newNode1->rightChild = nullptr;
            if (this->relation(newNode->info, parentNode->info)) {
                parentNode->leftChild = newNode1;
                parentNode = parentNode->leftChild;
            }
            else {
                parentNode->rightChild = newNode1;
                parentNode = parentNode->rightChild;
            }
            nr--;
            nrOfElems++;
        }
    }
}
//Best case: Theta(1), Worst case: Theta(nrOfElems + nr) => Total complexity: O(nrOfElems + nr) (best case when the bag is empty and nr = 1, worst case if the BST is degenerate and the element should be one of the leaves and nr > 1)

