#include "heapsort.h"  //access heapsort.h
#include <iostream>
#include <string>
#include <chrono> // Include chrono for time measurements

using namespace std;
using namespace chrono;


   void BinarySearch(SummedCount Summedcounts[], int size, int b1, int b2) {
    // Sort the Summedcounts array using heap sort based on the Sum value
    heapSort(Summedcounts, size);

    int left = 0, right = size - 1;  // define the index left and right of the array
    int leftBoundary = -1;           // leftboundary = the first sum to be greater than b1

    while (left <= right) {       //check if all sums between b1 and b2 have been searched
        int mid = left + (right - left) / 2;   //Calculate median
        int i =0;

        if (Summedcounts[mid].Sum >= b1 && Summedcounts[i].Sum <= b2) {     // if the sum of the median index is >= b1 and the sum of the i index is <= b2
                                                                            // then make the median the leftboundary
            leftBoundary = mid;
            right = mid - 1;      //update the number of right to the updated number of cells in Summedcounts
            i =+ mid;             //update i by moving it mid number positions right
        } else {
            left = mid + 1;       //if the sum of the median index is <= b1 and the sum of the i index >=b2, update left by moving it one cell after the median
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

    int b1, b2; //define bound b1 and bound b2
    cout << "Enter the lower bound (b1) and upper bound (b2) for the birth counts range: ";
    cin >> b1 >> b2;

    BinarySearch(Summedcounts, MAXSUMS, b1, b2);  // Perform Binary Search on the data
    
    // Stop measuring time
    auto end_time = high_resolution_clock::now();

    // Calculate the duration
    auto duration = duration_cast<nanoseconds>(end_time - start_time);

   
// Print the execution time
    cout << "Binary Search execution time: " << duration.count() << " nanoseconds" << endl;
    
  

    return 0;
}