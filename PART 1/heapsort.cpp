#include "read_print.h"  // Access read_print.h
#include <iostream>      
#include <string>        
#include <chrono>        // Include chrono for time measurements

using namespace std;      
using namespace chrono;   

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

int main() {
    Read_Data(); // Call Read_Data() to read the data

    CalculateDeathSums(); // Calculate and store summed death counts for each region between 2005 and 2022

    // Start measuring time
    auto start_time = high_resolution_clock::now(); 

    const int iterations = 1000; // Number of iterations to find average execution time of the algorithm
    for (int i = 0; i < iterations; ++i) {

        // Sort Summedcounts based on the total sum of each region in ascending order using HeapSort
        heapSort(Summedcounts, MAXSUMS); 
    }

    // Stop measuring time
    auto end_time = high_resolution_clock::now();

    // Calculate duration of the sorting
    auto duration = duration_cast<microseconds>(end_time - start_time); // Calculate the duration in microseconds

    // Print the contents of the Summedcounts array
    cout << "Summed Death Counts for each region between 2005 and 2022 :" << endl << endl;
    PrintSummedCounts(Summedcounts, MAXSUMS); 

    // Print the average execution time of heapsort
    cout << "Average HeapSort execution time: " << duration.count() / iterations << " microseconds" << endl;

    return 0; 
}
