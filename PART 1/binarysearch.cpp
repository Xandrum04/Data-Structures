#include "heapsort.h"  //access heapsort.h
#include <iostream>
#include <string>
#include <chrono> // Include chrono for time measurements

using namespace std;
using namespace chrono;

bool printOnce= false;  //boolean value to print the found counts once

   void BinarySearch(SummedCount Summedcounts[], int size, int b1, int b2) {
    

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

    if (!printOnce){ //if printOnce is false then print the found regions

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
}




int main()
{
   
    Read_Data(); //access Read_Data() from read_print.h

    CalculateBirthSums(); // Calculate and store summed birth counts for each region between 2005 and 2022

    // Sort the Summedcounts array using heap sort based on the Sum value
    heapSort(Summedcounts, MAXSUMS);

    int b1, b2; //define bound b1 and bound b2
    cout << "Enter the lower bound (b1) and upper bound (b2) for the birth counts range: ";
    cin >> b1 >> b2;

 // Start measuring time
    auto start_time = high_resolution_clock::now();

    const int iterations = 2000; // Number of iterations to find average execution time of the algorithm
    for (int i = 0; i < iterations; ++i) {

        

    BinarySearch(Summedcounts, MAXSUMS, b1, b2);  // Perform Binary Search on the data
    printOnce = true;  
    }
    // Stop measuring time
    auto end_time = high_resolution_clock::now();

    
    auto duration = duration_cast<microseconds>(end_time - start_time); // Calculate the duration in microseconds

   
    // Print the average execution time of Binary Search
    cout << "Binary Search execution time: " << duration.count() / iterations << " microseconds" << endl;
    
  

    return 0;
}