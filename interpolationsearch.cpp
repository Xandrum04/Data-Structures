#include "heapsort.h"  // Include the header file for heapSort function
#include <iostream>
#include <string>
#include <chrono> 

using namespace std;
using namespace chrono;

// Function to perform Interpolation Search on an array of SummedCount objects
void InterpolationSearch(SummedCount Summedcounts[], int size, int b1, int b2) {
    heapSort(Summedcounts, size); // Sort the array using heap sort

    int low = 0, high = size - 1;  
    int leftBoundary = -1; // Initialize leftBoundary to -1
    bool countsFound = false;  // Flag to track if counts are found within the range

    // Perform Interpolation Search to find the left boundary (first element >= b1)
    while (low <= high && b1 >= Summedcounts[low].Sum && b1 <= Summedcounts[high].Sum) {
        if (low == high) { // If low and high converge to the same element
            if (Summedcounts[low].Sum == b1) 
                leftBoundary = low; // Set leftBoundary if element equals b1
            break;
        }

        // Calculate the position using the interpolation formula
        int pos = low + (((double)(high - low) / (Summedcounts[high].Sum - Summedcounts[low].Sum)) * (b1 - Summedcounts[low].Sum));

        if (Summedcounts[pos].Sum == b1) {
            leftBoundary = pos; // If element at pos equals b1, set leftBoundary
            break;
        }

        if (Summedcounts[pos].Sum < b1) {
            low = pos + 1; // Move low to the right
        } else {
            high = pos - 1; // Move high to the left
        } 
    }

    if (leftBoundary == -1) {
        leftBoundary = low; // If leftBoundary not found, set it to low
    }

    cout << "Regions with summed birth counts in the range [" << b1 << ", " << b2 << "]:" << endl;

    // Iterate from leftBoundary to the end or until the sum exceeds b2
    for (int i = leftBoundary; i < size && Summedcounts[i].Sum <= b2; ++i) {
        cout << "Region: " << Summedcounts[i].Region << ", Sum: " << Summedcounts[i].Sum << endl;
        countsFound = true;  // Set flag to true if any counts are found within the range
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

    InterpolationSearch(Summedcounts, MAXSUMS, b1, b2); // Perform interpolation search on the data
    
    auto end_time = high_resolution_clock::now(); // Record end time
    auto duration = duration_cast<nanoseconds>(end_time - start_time); // Calculate the duration

    cout << "Binary execution time: " << duration.count() << " nanoseconds" << endl; // Output the execution time

    return 0;
}