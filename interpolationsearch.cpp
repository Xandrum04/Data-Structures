#include "heapsort.h"  //access heapsort.h
#include <iostream>
#include <string>
#include <chrono> // Include chrono for time measurements

using namespace std;
using namespace chrono;


 void InterpolationSearch(SummedCount Summedcounts[], int size, int b1, int b2) {
    // Sort the Summedcounts array using heap sort based on the Sum value
    heapSort(Summedcounts, size);

    // Interpolation search for the left boundary (b1)
    int low = 0, high = size - 1;  // define the index low and high of the array
    int leftBoundary = -1;

    while (low <= high && b1 >= Summedcounts[low].Sum && b1 <= Summedcounts[high].Sum) {
        if (low == high) {
            if (Summedcounts[low].Sum == b1) //if the sum count at index low = b1, make low the leftboundary
            leftBoundary = low;
            break;
        }

        // Estimate the position of b1
        int pos = low + (((double)(high - low) / (Summedcounts[high].Sum - Summedcounts[low].Sum)) * (b1 - Summedcounts[low].Sum));

        if (Summedcounts[pos].Sum == b1) {  //if sum at index pos = b1 make pos the left boundary
            leftBoundary = pos;
            break;
        }

        if (Summedcounts[pos].Sum < b1) {  //if sum at index pos < b1 add 1 to low
            low = pos + 1;
        } else {                           //if sum at index pos > b1 subtract 1 from high
            high = pos - 1;
        } 
    }

    if (leftBoundary == -1) {
        // No exact match found, find the first element greater than or equal to b1
        leftBoundary = low;
    }

    // Print regions with summed birth counts in the range [b1, b2]
    cout << "Regions with summed birth counts in the range [" << b1 << ", " << b2 << "]:" << endl;

    for (int i = leftBoundary; i < size && Summedcounts[i].Sum <= b2; ++i) {
        cout << "Region: " << Summedcounts[i].Region << ", Sum: " << Summedcounts[i].Sum << endl;
    }
}



int main()
{
   
    Read_Data(); //access Read_Data() from read_print.h

    CalculateBirthSums(); // Calculate and store summed birth counts for each region between 2005 and 2022

    
 // Start measuring time
    auto start_time = high_resolution_clock::now();

    int b1, b2;
    cout << "Enter the lower bound (b1) and upper bound (b2) for the birth counts range: ";
    cin >> b1 >> b2;

    InterpolationSearch(Summedcounts, MAXSUMS, b1, b2);
    
    // Stop measuring time
    auto end_time = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<nanoseconds>(end_time - start_time);

   
// Print the execution time
    cout << "Binary execution time: " << duration.count() << " nanoseconds" << endl;
    
  

    return 0;
}