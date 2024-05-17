#include "heapsort.h"  //access heapsort.h
#include <iostream>
#include <string>
#include <chrono> // Include chrono for time measurements

using namespace std;
using namespace chrono;


   void BinarySearch(SummedCount Summedcounts[], int size, int b1, int b2) {
    // Sort the Summedcounts array using heap sort based on the Sum value
    heapSort(Summedcounts, size);

    // Binary search for the left boundary (b1)
    int left = 0, right = size - 1;
    int leftBoundary = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (Summedcounts[mid].Sum >= b1) {
            leftBoundary = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    // If no valid boundary found, return
    if (leftBoundary == -1) {
        cout << "No regions found with summed birth counts in the given range." << endl;
        return;
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

    BinarySearch(Summedcounts, MAXSUMS, b1, b2);
    
    // Stop measuring time
    auto end_time = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<nanoseconds>(end_time - start_time);

   
// Print the execution time
    cout << "Binary execution time: " << duration.count() << " nanoseconds" << endl;
    
  

    return 0;
}