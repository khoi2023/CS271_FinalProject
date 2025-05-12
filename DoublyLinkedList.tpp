/*
DoublyLinkedList.tpp
A file that contains the implementation of the List class methods in the DoublyLinkedList.hpp file.
Written by: Duc T.
*/

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <stdexcept>
#include "DoublyLinkedList.hpp"

using namespace std;

// Default constructor.
// Parameter: NONE.
// Return value: NONE.
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(void) {
    head = nullptr;
    tail = nullptr;
    numElements = 0;
}

// Copy constructor. This copies the data from a doubly linked list to another one.
// Parameter: A given doubly linked list.
// Return value: NONE.
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& list) {
    head = nullptr;
    tail = nullptr;
    numElements = 0;
    // Use a pointer to trace the nodes of the list we want to copy.
    Node* current = list.head;
    Node* lastNodeGenerated = nullptr;

    while (current != nullptr) {
        Node *newNode = new Node;
        newNode->value = current->value;
        newNode->prev = lastNodeGenerated;
        newNode->next = nullptr;

        if (lastNodeGenerated != nullptr) {
            lastNodeGenerated->next = newNode;
        } else {
            head = newNode;  // Set head for the first node
        }
        lastNodeGenerated = newNode;
        current = current->next;
        numElements++;
    }
    
    // Set tail to the last node generated.
    tail = lastNodeGenerated;
}

// Destructor.
// Parameter: None.
// Return value: None.
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList(void) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
    // Set head and tail to nullptr to avoid dangling pointers.
    head = nullptr;
    tail = nullptr;
    // Set the number of elements to 0.
    numElements = 0;
}

// Assignment Operator. This assigns to a list the same list as the list being assigned.
// Parameter: The list to be assigned.
// Return value: A new list which is exactly the same as the list being assigned.
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T> rhs) {
    if (this == &rhs) {
        return *this;  // Self-assignment check
    }

    // Destroy the current list
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
    head = nullptr;
    tail = nullptr;
    numElements = 0;

    // Copy the new list
    Node* current2 = rhs.head;
    Node* lastNodeGenerated = nullptr;

    while (current2 != nullptr) {
        Node* newNode = new Node;
        newNode->value = current2->value;
        newNode->prev = lastNodeGenerated;
        newNode->next = nullptr;

        if (lastNodeGenerated == nullptr) {
            head = newNode;  // Set head for the new list
        } else {
            lastNodeGenerated->next = newNode;
        }

        lastNodeGenerated = newNode;
        current2 = current2->next;
        numElements++;
    }
    tail = lastNodeGenerated;
    return *this;  // Allow chain assignments
}

// Insert operator. This inserts a node with a given value at a given index position in the doubly linked list.
// Parameters: Value and the index position to be inserted.
// Return value: Throws std::out_of_range if the index is out of range.
template <class T>
void DoublyLinkedList<T>::insert(const T &item, size_t index) {
    if (index > numElements) {
        throw out_of_range("Index out of range.");
    }

    Node* temp = new Node;
    temp->value = item;
    temp->prev = nullptr;
    temp->next = nullptr;

    if (index == 0) { // Inserting at the beginning.
        temp->next = head;
        if (head != nullptr) {
            head->prev = temp;
        }
        head = temp;
        if (numElements == 0) {
            tail = temp;
        }
    } else {
        Node* current = head;
        for (size_t i = 0; i < index; i++) {
            if (current == nullptr) {
                // This should never happen because of our index check above.
                throw runtime_error("Unexpected null pointer encountered.");
            }
            current = current->next;
        }
        // Insert temp before 'current'
        if (current != nullptr) {
            temp->next = current;
            temp->prev = current->prev;
            if (current->prev != nullptr) {
                current->prev->next = temp;
            }
            current->prev = temp;
        } else {
            // If current is null, inserting at the end.
            temp->prev = tail;
            if (tail != nullptr) {
                tail->next = temp;
            }
            tail = temp;
        }
    }
    numElements++;
}

// Erase operator. This deletes a node at a given index position in the doubly linked list.
// Parameters: Index position of the node to be deleted.
// Return value: Throws std::out_of_range if the index is out of range.
template <class T>
void DoublyLinkedList<T>::erase(size_t index) {
    if (index >= numElements) {
        throw out_of_range("Index out of range.");
    }

    Node* toDelete = head;

    // Case 1: Deleting the head node
    if (index == 0) {
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr; // List becomes empty.
        }
        delete toDelete;
    }
    // Case 2: Deleting the tail node
    else if (index == numElements - 1) {
        toDelete = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr; // List becomes empty.
        }
        delete toDelete;
    }
    // Case 3: Deleting a middle node
    else {
        for (size_t i = 0; i < index; i++) {
            toDelete = toDelete->next;
        }
        Node* prevToDelete = toDelete->prev;
        Node* nextToDelete = toDelete->next;
        prevToDelete->next = nextToDelete;
        nextToDelete->prev = prevToDelete;
        delete toDelete;
    }
    numElements--;
}

// Search operator. This returns the index value of the first node with value equal to 'item'.
// Parameter: value 'item' to be found in the list.
// Return value: The smallest index of a node containing 'item'. If no such node exists, returns -1.
template <class T>
size_t DoublyLinkedList<T>::search(const T &item) const {
    Node* current = head;
    size_t counter = 0;
    while (current != nullptr) {  // Check if current is not null
        if (current->value == item) {
            return counter;  // Found item, return index.
        }
        current = current->next;
        counter++;
    }
    return -1; // Return -1 if item is not found.
}

// Push front operator. This adds a new node with the 'item' value at the start of the doubly linked list.
// Parameter: value 'item' to be added.
// Return value: None.
template <class T>
void DoublyLinkedList<T>::push_front(const T &item) {
    Node* temp = new Node;
    temp->value = item;
    temp->prev = nullptr;
    temp->next = head;
    if (head != nullptr) {
        head->prev = temp;
    }
    head = temp;
    if (numElements == 0) {
        tail = temp;
    }
    numElements++;
}

// Push back operator. This adds a new node with the 'item' value at the end of the doubly linked list.
// Parameter: value 'item' to be added.
// Return value: None.
template <class T>
void DoublyLinkedList<T>::push_back(const T &item) {
    Node* temp = new Node;
    temp->value = item;
    temp->next = nullptr;
    temp->prev = tail;

    if (tail == nullptr) {
        head = temp;
        tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
    numElements++;
}

// Pop front operator. This removes the first node of the doubly linked list.
// Parameter: None.
// Return value: The value of the removed node.
// Throws: std::out_of_range if the list is empty.
template <class T>
T DoublyLinkedList<T>::pop_front(void) {
    if (numElements == 0) {
        throw out_of_range("The list is empty!");
    }
    T return_value = head->value;
    Node *temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr; // List becomes empty.
    }
    delete temp;
    numElements--;
    return return_value;
}

// Pop back operator. This removes the last node of the doubly linked list.
// Parameter: None.
// Return value: The value of the removed node.
// Throws: std::out_of_range if the list is empty.
template <class T>
T DoublyLinkedList<T>::pop_back(void) {
    if (numElements == 0) {
        throw out_of_range("The list is empty");
    }
    T return_value = tail->value;
    Node *temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr; // List becomes empty.
    }
    delete temp;
    numElements--;
    return return_value;
}

// Find by index operator. This retrieves the value of the node at a given index position in the doubly linked list.
// Parameter: The index position to find.
// Return value: Reference to the value at the given index.
// Throws: std::out_of_range if the index is out of range.
template <class T>
T& DoublyLinkedList<T>::operator[](size_t index) {
    if (index >= numElements) {
        throw out_of_range("Index is out of bounds.");
    }
    Node* ptr = head;
    for (size_t i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    return ptr->value; 
}

// Size operator. This returns the number of elements in the list.
// Parameter: None.
// Return value: The number of elements in the list.
template <class T>
size_t DoublyLinkedList<T>::size(void) const {
    return numElements;
}

// Empty operator. This checks whether the list is empty.
// Parameter: None.
// Return value: True if the list is empty, False otherwise.
template <class T>
bool DoublyLinkedList<T>::empty(void) const {
    return (numElements == 0);
}

// Concatenation operator. This returns a new list created by combining the current list with another list.
// Parameter: The list to be concatenated with the current list.
// Return value: A new list after concatenation, with the elements of the current list followed by the elements of the other list.
template <class T>
DoublyLinkedList<T> DoublyLinkedList<T>::concatenate(const DoublyLinkedList<T> &list) const {
    DoublyLinkedList<T> result;
    Node *temp = head;
    while (temp != nullptr) {
        result.push_back(temp->value);
        temp = temp->next;
    }
    temp = list.head;
    while (temp != nullptr) {
        result.push_back(temp->value);
        temp = temp->next;
    }
    return result;
}

// Equality operator. This checks whether rhs list is equal to the current list.
// Parameter: rhs list.
// Return value: True if the lists are equal, False otherwise.
template <class T>
bool DoublyLinkedList<T>::operator==(const DoublyLinkedList<T> &rhs) const {
    if (numElements != rhs.numElements) {
        return false;
    }
    Node *temp1 = head;
    Node *temp2 = rhs.head;
    while (temp1 != nullptr && temp2 != nullptr) {
        if (temp1->value != temp2->value) {
            return false;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}

// Inequality operator. This checks whether rhs list is different from the current list.
// Parameter: rhs list.
// Return value: True if the lists are different, False otherwise.
template <class T>
bool DoublyLinkedList<T>::operator!=(const DoublyLinkedList<T> &rhs) const {
    return !(*this == rhs);
}
