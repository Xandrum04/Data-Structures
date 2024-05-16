#include "read_print.h" // Include the header file for function declarations
#include <iostream>
#include <string>
#include <chrono> // Library for time calculation

using namespace std;
using namespace chrono;

// Heapify function to maintain heap property
void heapify(SummedCount arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // Left child
    int r = 2 * i + 2; // Right child

    // If left child is larger than root
    if (l < n && arr[l].Sum > arr[largest].Sum)
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r].Sum > arr[largest].Sum)
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Heap sort algorithm
void heapSort(SummedCount arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    Read_Data(); // Populate the array with data from the file

    CalculateDeathSums(); // Calculate and store summed death counts for each region between 2005 and 2022

    // Start measuring time
    auto start_time = high_resolution_clock::now();

    // Sort Summedcounts based on the total sum of each region in ascending order using HeapSort
    heapSort(Summedcounts, MAXSUMS);

    // Stop measuring time
    auto end_time = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<nanoseconds>(end_time - start_time);

    // Print the contents of Summedcounts array
    cout << "Summed Death Counts for each region between 2005 and 2022 :" << endl << endl;
    PrintSummedCounts(Summedcounts, MAXSUMS);

    // Print the execution time
    cout << "HeapSort execution time: " << duration.count() << " nanoseconds" << endl;

    return 0;
}
