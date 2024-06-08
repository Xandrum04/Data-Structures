#include "read_print.h"
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

// Function to calculate the maximum value in Summedcounts array
int getMax(SummedCount arr[], int n) {
    int max = arr[0].Sum;
    for (int i = 1; i < n; i++) {
        if (arr[i].Sum > max) {
            max = arr[i].Sum;
        }
    }
    return max;
}

// Counting Sort function
void countingSort(SummedCount arr[], int n) {
    // Find the maximum element in the array
    int max = getMax(arr, n);
    int* count = new int[max + 1] {0}; // Create count array and initialize to 0
    SummedCount* output = new SummedCount[n]; // Create output array

    // Store the count of each element
    for (int i = 0; i < n; i++) {
        count[arr[i].Sum]++;
    }

    // Change count[i] so that count[i] now contains the actual position of this element in output array
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i].Sum] - 1] = arr[i];
        count[arr[i].Sum]--;
    }

    // Copy the output array to arr, so that arr now contains sorted elements
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] count;
    delete[] output;
}

int main() {
    Read_Data(); // Populate the array with data from the file

    CalculateDeathSums(); // Calculate and store summed death counts for each region between 2005 and 2022

    // Start measuring time
    auto start_time = high_resolution_clock::now(); // Record the start time

    const int iterations = 1000; // Number of iterations for averaging
    for (int i = 0; i < iterations; ++i) {
        // Sort Summedcounts based on the total sum of each region in ascending order using Counting Sort
        countingSort(Summedcounts, MAXSUMS); // Call countingSort to sort the summed counts
    }

    // Stop measuring time
    auto end_time = high_resolution_clock::now(); // Record the end time

    // Calculate duration
    auto duration = duration_cast<microseconds>(end_time - start_time); // Calculate the duration in microseconds

    // Print the contents of Summedcounts array
    cout << "Summed Death Counts for each region between 2005 and 2022 :" << endl << endl;
    PrintSummedCounts(Summedcounts, MAXSUMS); // Call function to print the summed counts

    // Print the execution time
    cout << "Average Counting Sort execution time: " << duration.count() / iterations << " microseconds" << endl; // Print the execution time

    return 0; // Return 0 to indicate successful execution
}
