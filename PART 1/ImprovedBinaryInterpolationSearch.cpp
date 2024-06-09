#include "heapsort.h"  // access heapsort.h
#include <iostream>
#include <string>
#include <chrono>
#include <cmath> // Include cmath for sqrt

using namespace std;
using namespace chrono;

bool printOnce = false; //boolean value to print the found counts once

void BinaryInterpolationSearch(SummedCount Summedcounts[], int size, int b1, int b2) {
    int low = 0, high = size - 1; // define the index low and high of the array
    int leftBoundary = -1;     // leftboundary = the first sum to be greater than b1
    bool countsFound = false;   // Flag to track if counts are found within the range


    // Perform Interpolation Search to find the left boundary (first element >= b1)
    while (low <= high && b1 >= Summedcounts[low].Sum && b1 <= Summedcounts[high].Sum) {
        if (low == high) {  // If low and high point to the same element
            if (Summedcounts[low].Sum == b1)  
                leftBoundary = low;   // Set leftBoundary if element equals b1
            break;
        }


        // Calculate the position using the interpolation formula
        int pos = low + (((high - low) / (Summedcounts[high].Sum - Summedcounts[low].Sum)) * (b1 - Summedcounts[low].Sum));

        if (Summedcounts[pos].Sum == b1) {  // If element at pos equals b1, leftBoundary = pos 
            leftBoundary = pos;
            break;
        }

        if (Summedcounts[pos].Sum < b1) {  // If element at pos less than b1
            low = pos + 1;  //update the number of index low to the updated number of cells in Summedcounts

             // If element at pos greater than b1
        } else {
            high = pos - 1;  //update the number of index high to the updated number of cells in Summedcounts
        }

        int size = high - low + 1;  //update size
         
        if (size <= 3) {  
            int next = (size* (b1 - Summedcounts[low].Sum) / (Summedcounts[high].Sum - Summedcounts[low].Sum));     //if updated size is <=3 calculate next

            while (Summedcounts[next].Sum != b1) {    //while sumcount at next index is not b1
                int i = 1;    //  define i=1
                size = high - low + 1;   //update size
                
                    if ( Summedcounts[next].Sum < b1) {   //if sumcount at index next < b1
                        while (b1 > Summedcounts[next + i * (int)sqrt(size) - 1].Sum) {
                            i*=2;      //increment i exponentially while b1> summedcounts at index   next + i*root(size) -1
                        }
                        high = next + i * sqrt(size);   //update high to next + i * root(size)
                    } else {
                        while (b1 < Summedcounts[next - i * (int)sqrt(size) + 1].Sum) { 
                            i*=2;      //increment exponentially i while b1< summedcounts at index   next - i*root(size) + 1
                        }
                        high = next - (i - 1) * sqrt(size);    //update high to next - (i-1)*root(size)
                    }
                    low = next - i * sqrt(size);      //update low to next - i* root(size)
                
                next = low + ((high - low + 1) * (b1 - Summedcounts[low].Sum)) / (Summedcounts[high].Sum - Summedcounts[low].Sum);   //update next
                if (Summedcounts[next].Sum == b1) {    //if sumcount at index next = b1
                    leftBoundary = next;              //leftboundary found at next
                    break;
                } else {                 
                    return;            //else return
                }
            }
        }
    }

    if (!printOnce) {  //if printOnce is false then print the found regions
        if (leftBoundary == -1) {
            leftBoundary = low;  // If leftBoundary not found, set it to low
        }

        cout << "Regions with summed birth counts in the range [" << b1 << ", " << b2 << "]:" << endl;

        // Iterate from leftBoundary to the end or until the sum exceeds b2
        for (int i = leftBoundary; i < size && Summedcounts[i].Sum <= b2; ++i) {
            cout << "Region: " << Summedcounts[i].Region << ", Sum: " << Summedcounts[i].Sum << endl;
            countsFound = true; // Set flag to true if any counts are found within the range
        }

        if (!countsFound) {  // if countsfound = false
            cout << "No regions found with summed birth counts in the given range." << endl;
        }
    }
}

int main() {
    Read_Data(); //access Read_Data() from read_print.h
    CalculateBirthSums(); // Calculate and store summed birth counts for each region between 2005 and 2022

    // Sort the Summedcounts array using heap sort based on the Sum value
    heapSort(Summedcounts, MAXSUMS); 

    int b1, b2; //define bound b1 and bound b2
    cout << "Enter the lower bound (b1) and upper bound (b2) for the birth counts range: ";
    cin >> b1 >> b2;


    auto start_time = high_resolution_clock::now(); // Start measuring time

    const int iterations = 2000; // Number of iterations to find average execution time of the algorithm
    for (int i = 0; i < iterations; ++i) {

    BinaryInterpolationSearch(Summedcounts, MAXSUMS, b1, b2); // Perform Binary interpolation search on the data
    printOnce = true;
    }    
    
    auto end_time = high_resolution_clock::now();  // Stop measuring time

    auto duration = duration_cast<microseconds>(end_time - start_time); // Calculate the duration in microseconds
    // Print the average execution time of Interpolation Search
    cout << "Binary Interpolation Search execution time: " << duration.count() /iterations << " microseconds" << endl;

    return 0;
}