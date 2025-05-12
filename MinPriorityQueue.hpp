/*
MinPriorityQueue.hpp
A file that contains the templated declarations for the priority queue (Min-Heap version).
Written by: Duc T.
*/

#pragma once
#include <iostream>
#include <unordered_map> // equivalent of Python's dictionary
#include <utility> // for std::pair

using namespace std;

// Min-PQ implementation, with an underlying min-heap
template<class K, class V>
class minPQ {

    private:
    
    V* arr; // the heap
    // use hash tables/maps to keep track of indices and keys.
    unordered_map<V, int> indexOf;
    unordered_map<V, K> keyOf;

    size_t capacity;
    size_t numElements;

    int left(int i);
    int right(int i);
    int parent(int i);

    // Heapify function
    void heapify(int i, size_t size);
    void buildHeap(size_t n);

    public:

    // Default constructor
    minPQ(size_t capacity = 10);

    // Copy constructor
    // Note: this is a deep copy
    minPQ(const minPQ<K, V> &pq);

    // Assignment operator
    // Note: this is a deep copy
    minPQ<K, V>& operator=(minPQ<K, V> rhs);

    // Destructor
    ~minPQ(void);

    // your approach should result the contents of the heap in sorted order
    // DO NOT modify the underlying heap!
    V* heapSort(void);

    // throw std::out_of_range if the queue is empty
    pair<K,V> top(void); // analogous to MIN-HEAP-MINIMUM

    // throw std::out_of_range if the queue is empty
    pair<K,V> pop(void); // analogous to MIN-HEAP-EXTRACT-MIN

    // throw std::out_of_range if value is not in the queue
    // throw std::out_of_range if old key is LESS THAN new key
    void updateKey(K newKey, V value); 

    // throw std::overflow_error if the queue is full
    // the exact implementation from the textbook will not work, because we're doing templated types
    void insert(K key, V value);

    // adds values from `values` into `this->arr` such that `this->arr` == `values`
    // then calls `buildHeap`
    void fromArrays(K *keys, V *values, int n); // in O(n)

    bool empty(void) const;
};

#include "MinPriorityQueue.tpp"