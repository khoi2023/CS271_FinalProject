/*
DoublyLinkedList.hpp
This file defines a DoublyLinkedList class template for use in data structures and algorithms.
The DoublyLinkedList class represents a doubly linked list and includes methods for managing its elements.
It includes methods for inserting, deleting, searching, and manipulating the list.
The class also provides methods for concatenating two lists and checking for equality.
Written by: Duc T.
*/
#include <iostream>

#pragma once

using namespace std;


template<class T>
class DoublyLinkedList{

    private:
    // Node structure for the doubly linked list
    // Each node contains a value, a pointer to the previous node, and a pointer to the next node
    struct Node{
        T value;

        Node *prev;
        
        Node *next;

        Node() : prev(nullptr), next(nullptr) {}

        Node(const T &item) : value(item), prev(nullptr), next(nullptr) {}
        
        ~Node() {}
    };
    
    Node* head;

    Node* tail;
    
    size_t numElements;

    Node* getPointer(size_t index); 

    public:

    // Default constructor.
    // Initializes an empty doubly linked list.
    // Parameters: None.
    // Return value: None.
    DoublyLinkedList<T>(void);

    // Copy constructor.
    // Initializes a new doubly linked list as a copy of an existing one.
    // Parameters: A given doubly linked list.
    // Return value: None.
    DoublyLinkedList<T>(const DoublyLinkedList<T>& list);

    // Assignment operator.
    // Assigns the properties of one doubly linked list to another.
    // Parameters: A given doubly linked list.
    // Return value: A reference to the current doubly linked list.
    // This allows for chaining of assignment operations.
    DoublyLinkedList<T>& operator=(DoublyLinkedList<T> rhs);

    // Destructor.
    // Cleans up the memory used by the doubly linked list.
    // Parameters: None.
    // Return value: None.
    ~DoublyLinkedList<T>(void);

    // Insert operator.
    // Inserts a new node with a given value at a specified index position in the doubly linked list.
    // Parameters: The value to be inserted and the index position.
    // Return value: Throws std::out_of_range if the index is out of range.
    // This function also increases the size of the list by one.
    void insert(const T &item, size_t index);

    // Erase operator.
    // Deletes a node at a specified index position in the doubly linked list.
    // Parameters: The index position of the node to be deleted.
    // Return value: Throws std::out_of_range if the index is out of range.
    // This function also decreases the size of the list by one.
    void erase(size_t index);

    // Search operator.
    // Searches for a given value in the doubly linked list.
    // Parameters: The value to be searched for.
    // Return value: The index position of the first occurrence of the value.
    // If the value is not found, it returns -1.
    size_t search(const T &item) const;

    // Push front operator.
    // Adds a new node with a given value at the start of the doubly linked list.
    // Parameters: The value to be added.
    // Return value: None.
    // This function also increases the size of the list by one.
    void push_front(const T &item);

    // Push back operator.
    // Adds a new node with a given value at the end of the doubly linked list.
    // Parameters: The value to be added.
    // Return value: None.
    // This function also increases the size of the list by one.
    void push_back(const T &item);

    // Pop front operator.
    // Removes the first node of the doubly linked list.
    // Parameters: None.
    // Return value: The value of the removed node.
    // Throws std::out_of_range if the list is empty.
    // This function also decreases the size of the list by one.
    T pop_front(void);

    // Pop back operator.
    // Removes the last node of the doubly linked list.
    // Parameters: None.
    // Return value: The value of the removed node.
    // Throws std::out_of_range if the list is empty.
    // This function also decreases the size of the list by one.
    T pop_back(void);

    // Find by index operator.
    // Retrieves the value of the node at a given index position in the doubly linked list.
    // Parameters: The index position to find.
    // Return value: Reference to the value at the given index.
    // Throws std::out_of_range if the index is out of range.
    T& operator[](size_t index);

    // Size operator.
    // Returns the number of elements in the doubly linked list.
    // Parameters: None.
    // Return value: The number of elements in the list.
    size_t size(void) const;

    // Empty check operator.
    // Checks whether the doubly linked list is empty.
    // Parameters: None.
    // Return value: True if the list is empty, false otherwise.
    bool empty(void) const;

    // Concatenate operator.
    // Concatenates two doubly linked lists into a new one.
    // Parameters: A given doubly linked list.
    // Return value: A new doubly linked list that is the result of concatenating the two lists.
    DoublyLinkedList<T> concatenate(const DoublyLinkedList<T> &list) const;

    // Equality operator.
    // Checks whether two doubly linked lists are equal.
    // Parameters: A given doubly linked list.
    // Return value: True if the lists are equal, false otherwise.
    bool operator==(const DoublyLinkedList<T> &rhs) const;

    // Inequality operator.
    // Checks whether two doubly linked lists are not equal.
    // Parameters: A given doubly linked list.
    // Return value: True if the lists are not equal, false otherwise.
    // This is the negation of the equality operator.
    bool operator!=(const DoublyLinkedList<T> &rhs) const;
};

#include "DoublyLinkedList.tpp"