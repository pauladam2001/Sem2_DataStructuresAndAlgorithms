#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	this->head = nullptr;
	this->length = 0;
}
//Theta(1)

Map::~Map() {
    Node* auxNode;
    while (this->head != nullptr) {
        auxNode = this->head->next;
        delete this->head;
        this->head = auxNode;
    }
}
//Theta(1)

TValue Map::add(TKey c, TValue v){
    Node* currentNode = this->head;
    TValue oldValue;
    if (this->length == 0) {                // if the length is 0 we 'initialize' the head with the given pair
        this->length++;
        Node* newNode = new Node;
        newNode->info.first = c;
        newNode->info.second = v;
        newNode->next = nullptr;
        this->head = newNode;
        return NULL_TVALUE;
    }
    while (currentNode != nullptr) {
        if (currentNode->info.first == c) {             // if the key is already in the map we just change the value
            oldValue = currentNode->info.second;
            currentNode->info.second = v;
            return oldValue;
        }
        else {
            currentNode = currentNode->next;
        }
    }
    this->length++;
    Node* newNode = new Node;                           // if the key is not in the map we insert the new pair at the beginning
    newNode->info.first = c;
    newNode->info.second = v;
    newNode->next = this->head;     //insert at the beginning
    this->head = newNode;
    return NULL_TVALUE;
}
//Best case: Theta(1), Worst case: Theta(length) => Total complexity: O(length) (best case when the length is 0 or the key is found on the first position, worst case when the key is on the last position or it is not in the map and we need to parse the whole array)

TValue Map::search(TKey c) const{
    Node* currentNode = this->head;
    while (currentNode != nullptr && currentNode->info.first != c) {
        currentNode = currentNode->next;
    }
    if (currentNode == nullptr)
	    return NULL_TVALUE;
    else
        return currentNode->info.second;
}
//Best case: Theta(1), Worst case: Theta(length) => Total complexity: O(length) (we can find the key in the first node, or we may need to verify every node)

TValue Map::remove(TKey c){
    Node* currentNode = this->head;
    Node* previousNode = nullptr;
    TValue deletedValue;
    if (currentNode != nullptr && currentNode->info.first == c) {       // if the key is stored in the head
        deletedValue = currentNode->info.second;
        this->head = currentNode->next;
        delete currentNode;
        this->length--;
        return deletedValue;
    }
    while (currentNode != nullptr && currentNode->info.first != c) {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    if (currentNode == nullptr)                         // if the key is not in the map
        return NULL_TVALUE;
    deletedValue = currentNode->info.second;            // if the key is in the map and it is not the head we link the previous node to the node after
    this->length--;                                     // the one that will be deleted
    previousNode->next = currentNode->next;
    delete currentNode;
    return deletedValue;
}
//Best case: Theta(1), Worst case: Theta(length) => Total complexity: 0(length) (best case if the key is stored in the head, worst case if the key is on the last position or it is not in the map)

int Map::size() const {
	return this->length;
}
//Theta(1)

bool Map::isEmpty() const{
    if (this->length == 0)
        return true;
	return false;
}
//Theta(1)

MapIterator Map::iterator() const {
	return MapIterator(*this);
}
//Theta(1)
