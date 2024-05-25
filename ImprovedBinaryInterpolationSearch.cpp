#include "heapsort.h"  // Include the header file for heapSort function
#include <iostream>
#include <string>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

// Function to perform Binary Interpolation Search on an array of SummedCount objects
void BinaryInterpolationSearch(SummedCount Summedcounts[], int size, int b1, int b2) {
    heapSort(Summedcounts, size); // Sort the array using heap sort

    int low = 0, high = size - 1;
    int leftBoundary = -1; // Initialize leftBoundary to -1
    bool countsFound = false; // Flag to track if counts are found within the range

    // Perform Exponential Search to find a good range for binary search
    int step = sqrt(size);
    int next = low;

    // Increase step exponentially to find the range where b1 could be
    while (next < high && Summedcounts[next].Sum < b1) {
        next += step;
        step *= 2;
    }

    // Determine the correct high boundary after exponential search
    int expLow = next / 2; // Set the lower boundary of the range
    int expHigh = min(next, high); // Set the upper boundary of the range

    // Perform binary search within the found range
    while (expLow <= expHigh) {
        int mid = expLow + (expHigh - expLow) / 2; // Calculate the middle index
        
        if (Summedcounts[mid].Sum == b1) {
            leftBoundary = mid; // If element at mid equals b1, set leftBoundary
            break;
        }
        if (Summedcounts[mid].Sum < b1) {
            expLow = mid + 1; // Move expLow to the right
        } else {
            expHigh = mid - 1; // Move expHigh to the left
        }
    }

    if (leftBoundary == -1) {
        leftBoundary = expLow; // If leftBoundary not found, set it to expLow
    }

    cout << "Regions with summed birth counts in the range [" << b1 << ", " << b2 << "]:" << endl;

    // Iterate from leftBoundary to the end or until the sum exceeds b2
    for (int i = leftBoundary; i < size && Summedcounts[i].Sum <= b2; ++i) {
        cout << "Region: " << Summedcounts[i].Region << ", Sum: " << Summedcounts[i].Sum << endl;
        countsFound = true; // Set flag to true if any counts are found within the range
    }

    if (!countsFound) {
        cout << "No regions found with summed birth counts in the given range." << endl;
    }
}

int main() {
    Read_Data(); // Function to read data into Summedcounts array
    CalculateBirthSums(); // Function to calculate the summed birth counts for each region

    auto start_time = high_resolution_clock::now(); // Record start time

    int b1, b2;
    cout << "Enter the lower bound (b1) and upper bound (b2) for the birth counts range: ";
    cin >> b1 >> b2;

    BinaryInterpolationSearch(Summedcounts, MAXSUMS, b1, b2); // Perform binary interpolation search on the data
    
    auto end_time = high_resolution_clock::now(); // Record end time
    auto duration = duration_cast<nanoseconds>(end_time - start_time); // Calculate the duration

    cout << "Binary execution time: " << duration.count() << " nanoseconds" << endl; // Output the execution time

    return 0;
}
