#include <iostream>
#include "read_print.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;



// Heapify function to maintain heap property
void heapify(SummedCount arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // Calculate left child index
    int r = 2 * i + 2; // Calculate right child index

    // If left child is larger than root
    if (l < n && arr[l].Sum > arr[largest].Sum)
        largest = l; // Update largest to left child index

    // If right child is larger than largest so far
    if (r < n && arr[r].Sum > arr[largest].Sum)
        largest = r; // Update largest to right child index

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]); // Swap root with largest

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest); // Recursively call heapify for the affected sub-tree
    }
}

// Heap sort algorithm
void heapSort(SummedCount arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i); // Call heapify to build the heap

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]); // Swap root with last element

        // Call max heapify on the reduced heap
        heapify(arr, i, 0); // Call heapify to maintain heap property
    }
}
