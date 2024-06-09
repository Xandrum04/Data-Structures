#include "read_print.h" // Access read_print.h
#include <iostream>
#include <string>
#include <chrono> // Include chrono for time measurements

using namespace std;
using namespace chrono;

// Partition function for QuickSort
int partition(SummedCount arr[], int low, int high) {
    SummedCount pivot = arr[high]; // Choose the pivot element
    int i = low - 1; // Index of smaller element

    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j].Sum <= pivot.Sum) {
            i++; // Increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Main QuickSort function
void quickSort(SummedCount arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    Read_Data(); // Access Read_Data() from read_print.h

    CalculateBirthSums(); // Calculate and store summed birth counts for each region between 2005 and 2022

    // Start measuring time
    auto start_time = high_resolution_clock::now();

    const int iterations = 1000; // Number of iterations to find average execution time of the algorithm
    for (int i = 0; i < iterations; ++i) {
        
        // Sort Summedcounts based on the total sum of each region using QuickSort
        quickSort(Summedcounts, 0, MAXSUMS - 1);
    }

    // Stop measuring time
    auto end_time = high_resolution_clock::now();

    // Calculate duration of the sorting
    auto duration = duration_cast<microseconds>(end_time - start_time);  // Calculate the duration in microseconds

    // Print the contents of Summedcounts array
    cout << "Summed Birth Counts for each region between 2005 and 2022 :" << endl << endl;
    PrintSummedCounts(Summedcounts, MAXSUMS);

    // Print the average execution time of quick sort
    cout << "Average Quicksort execution time: " << duration.count() / iterations << " microseconds" << endl;

    return 0;
}
