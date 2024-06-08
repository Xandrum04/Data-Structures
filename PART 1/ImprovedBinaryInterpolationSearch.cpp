#include "heapsort.h"  // Access heapsort.h for the heap sort function
#include <iostream>
#include <string>
#include <chrono> // Include chrono for time measurements
#include <cmath>  // Include cmath for sqrt function

using namespace std;
using namespace chrono;

void BinaryInterpolationSearch(SummedCount Summedcounts[], int size, int b1, int b2) {
    // Sort the Summedcounts array using heap sort based on the Sum value
    heapSort(Summedcounts, size);

    int left = 0, right = size - 1; // Define the index left and right of the array
    int next;     // Define next index
    bool countsFound = false;  // Flag to track if counts are found within the range

    // Perform Binary Interpolation Search to find the left boundary (first element >= b1)
    while (left <= right && b1 >= Summedcounts[left].Sum && b1 <= Summedcounts[right].Sum) {
        int size = right - left + 1; // Calculate the size of the current array
        int i = 1; // Initialize i with 1 for exponential steps

        // Calculate next
        next = left + (size * (b1 - Summedcounts[left].Sum) / (Summedcounts[right].Sum - Summedcounts[left].Sum));

        // If sum at index next isn't b1, keep searching
        while (Summedcounts[next].Sum != b1) {
            int jump = pow(2, i) * sqrt(size); // Calculate the exponential jump

            // Update boundaries using exponential steps
            if (Summedcounts[next].Sum < b1)
                left = next;
            else
                right = next;

            next = left + (size * (b1 - Summedcounts[left].Sum) / (Summedcounts[right].Sum - Summedcounts[left].Sum));
            
            // Break loop if next is out of bounds or if i exceeds the size of the array
            if (next < 0 || next >= size || i > size)
                break;

            i *= 2; // Increase i exponentially
        }

        // If value at next equals b1, break the outer loop
        if (Summedcounts[next].Sum == b1)
            break;
        else {
            next = -1; // No value found
            break;
        }
    }

    // Determine the left boundary for the range b1 to b2
    int leftBoundary = (next != -1) ? next : left;  // If next != -1, then leftBoundary = next. Otherwise, leftBoundary = left 
    cout << "Regions with summed birth counts in the range [" << b1 << ", " << b2 << "]:" << endl;

    // Iterate from leftBoundary to the end or until the sum exceeds b2
    for (int i = leftBoundary; i < size && Summedcounts[i].Sum <= b2; ++i) {
        cout << "Region: " << Summedcounts[i].Region << ", Sum: " << Summedcounts[i].Sum << endl;
        countsFound = true;  // Set flag to true if any counts are found within the range
    }

    if (!countsFound) {    // If countsFound = false
        cout << "No regions found with summed birth counts in the given range." << endl;
    }
}

int main() {
    Read_Data(); // Access Read_Data() from read_print.h
    CalculateBirthSums(); // Calculate and store summed birth counts for each region between 2005 and 2022

    auto start_time = high_resolution_clock::now(); // Start measuring time

    int b1, b2; // Define bound b1 and bound b2
    cout << "Enter the lower bound (b1) and upper bound (b2) for the birth counts range: ";
    cin >> b1 >> b2;

    BinaryInterpolationSearch(Summedcounts, MAXSUMS, b1, b2);  // Perform binary interpolation search on the data
    
    auto end_time = high_resolution_clock::now();  // Stop measuring time
    auto duration = duration_cast<microseconds>(end_time - start_time); // Calculate the duration
    // Print the execution time
    cout << "Binary Interpolation Search execution time: " << duration.count() << " microseconds" << endl; // Output the execution time

    return 0;
}
