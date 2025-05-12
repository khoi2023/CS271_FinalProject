/*
File name: MinPriorityQueue.tpp
A file that contains the implementation of the PQ class methods (Min-Heap version).
Written by: Duc T.
*/

#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <utility>
#include <stdexcept>
#include "MinPriorityQueue.hpp"

using namespace std;

// Left function. Returns the index of the left child of the node at index i.
template<class K, class V>
int minPQ<K, V>::left(int i) {
    return 2 * i + 1;
}

// Right function. Returns the index of the right child of the node at index i.
template<class K, class V>
int minPQ<K, V>::right(int i) {
    return 2 * i + 2;
}

// Parent function. Returns the index of the parent of the node at index i.
template<class K, class V>
int minPQ<K, V>::parent(int i) {
    return (i - 1) / 2;
}

// Heapify function. Maintains the min-heap property of the sub-heap rooted at index i.
template<class K, class V>
void minPQ<K, V>::heapify(int i, size_t size) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < static_cast<int>(size) && keyOf[arr[l]] < keyOf[arr[i]]) {
        smallest = l;
    }
    if (r < static_cast<int>(size) && keyOf[arr[r]] < keyOf[arr[smallest]]) {
        smallest = r;
    }
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        heapify(smallest, size);
    }
}

// BuildHeap function. Builds a min-heap from the unordered array.
template<class K, class V>
void minPQ<K, V>::buildHeap(size_t n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(i, n);
    }
}

// Default constructor. Initializes the heap with the given capacity.
template<class K, class V>
minPQ<K, V>::minPQ(size_t capacity) {
    this->capacity = capacity;
    this->numElements = 0;
    this->arr = new V[capacity];
}

// Copy constructor. Initializes the heap with the same elements as the given heap.
template<class K, class V>
minPQ<K, V>::minPQ(const minPQ<K, V> &pq) {
    this->capacity = pq.capacity;
    this->numElements = pq.numElements;
    this->arr = new V[capacity];
    for (size_t i = 0; i < numElements; i++) {
        this->arr[i] = pq.arr[i];
    }
    indexOf = pq.indexOf;
    keyOf = pq.keyOf;
}

// Assignment operator. Implements copy/swap idiom.
template<class K, class V>
minPQ<K, V>& minPQ<K, V>::operator=(minPQ<K, V> rhs) {
    swap(this->arr, rhs.arr);
    swap(this->capacity, rhs.capacity);
    swap(this->numElements, rhs.numElements);
    swap(indexOf, rhs.indexOf);
    swap(keyOf, rhs.keyOf);
    return *this;
}

// Destructor. Deletes the allocated heap array.
template<class K, class V>
minPQ<K, V>::~minPQ(void) {
    delete[] arr;
}

// HeapSort function. Returns a new array with the contents of the heap in sorted order.
template<class K, class V>
V* minPQ<K, V>::heapSort(void) {
    minPQ<K, V> temp(*this);
    V* sortedArr = new V[temp.numElements];
    int index = 0;
    // Since it's a min-heap, repeatedly extract the min to form a sorted array (in ascending order)
    while (!temp.empty()) {
        sortedArr[index++] = temp.pop().second;
    }
    return sortedArr;
}

// Top function. Returns the minimum element in the heap.
template<class K, class V>
pair<K, V> minPQ<K, V>::top(void) {
    if (this->numElements == 0) {
        throw out_of_range("The queue is empty.");
    }
    V minVal = arr[0];
    K minKey = keyOf[minVal];
    return pair<K, V>(minKey, minVal);
}

// Pop function. Removes and returns the minimum element from the heap.
template<class K, class V>
pair<K, V> minPQ<K, V>::pop(void) {
    if (this->numElements == 0) {
        throw out_of_range("The queue is empty.");
    }
    V minVal = arr[0];
    K minKey = keyOf[minVal];
    arr[0] = arr[this->numElements - 1];
    indexOf[arr[0]] = 0;
    this->numElements--;
    keyOf.erase(minVal);
    indexOf.erase(minVal);
    heapify(0, this->numElements);
    return pair<K, V>(minKey, minVal);
}

// UpdateKey function. Updates the key of the given value.
template<class K, class V>
void minPQ<K, V>::updateKey(K newKey, V value) {
    if (keyOf.find(value) == keyOf.end()) {
        throw out_of_range("Value is not in the queue.");
    }
    if (newKey > keyOf[value]) {
        throw out_of_range("Old key is LESS THAN new key.");
    }
    keyOf[value] = newKey;
    int i = 0;
    if (indexOf.find(value) != indexOf.end())
        i = indexOf[value];
    else
        throw out_of_range("Value is not in the queue.");
    
    while (i > 0 && keyOf[arr[parent(i)]] > keyOf[arr[i]]) {
        swap(arr[i], arr[parent(i)]);
        indexOf[arr[i]] = i;
        indexOf[arr[parent(i)]] = parent(i);
        i = parent(i);
    }
}

// Insert function. Inserts a new element into the heap.
template<class K, class V>
void minPQ<K, V>::insert(K key, V value) {
    if (this->numElements == this->capacity) {
        throw overflow_error("The queue is full");
    }
    arr[this->numElements] = value;
    keyOf[value] = key;
    indexOf[value] = this->numElements;
    int i = this->numElements;
    this->numElements++;
    while (i > 0 && keyOf[arr[parent(i)]] > keyOf[arr[i]]) {
        swap(arr[i], arr[parent(i)]);
        indexOf[arr[i]] = i;
        indexOf[arr[parent(i)]] = parent(i);
        i = parent(i);
    }
}

// fromArrays function. Initializes the heap with the given arrays and builds the heap.
template<class K, class V>
void minPQ<K, V>::fromArrays(K *keys, V *values, int n) {
    numElements = n;
    indexOf.clear();
    keyOf.clear();
    for (int i = 0; i < numElements; i++) {
        arr[i] = values[i];
        indexOf[values[i]] = i;
        keyOf[values[i]] = keys[i];
    }
    buildHeap(n);
}

// Empty function. Returns true if the heap is empty, false otherwise.
template<class K, class V>
bool minPQ<K, V>::empty(void) const {
    return this->numElements == 0;
}