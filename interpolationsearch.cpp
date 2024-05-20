#include "heapsort.h"  
#include <iostream>
#include <string>
#include <chrono> 

using namespace std;
using namespace chrono;

void InterpolationSearch(SummedCount Summedcounts[], int size, int b1, int b2) {
    heapSort(Summedcounts, size);

    int low = 0, high = size - 1;  
    int leftBoundary = -1;
    bool countsFound = false;  // Flag to track if counts are found within the range

    while (low <= high && b1 >= Summedcounts[low].Sum && b1 <= Summedcounts[high].Sum) {
        if (low == high) {
            if (Summedcounts[low].Sum == b1) 
                leftBoundary = low;
            break;
        }

        int pos = low + (((double)(high - low) / (Summedcounts[high].Sum - Summedcounts[low].Sum)) * (b1 - Summedcounts[low].Sum));

        if (Summedcounts[pos].Sum == b1) {
            leftBoundary = pos;
            break;
        }

        if (Summedcounts[pos].Sum < b1) {
            low = pos + 1;
        } else {
            high = pos - 1;
        } 
    }

    if (leftBoundary == -1) {
        leftBoundary = low;
    }

    cout << "Regions with summed birth counts in the range [" << b1 << ", " << b2 << "]:" << endl;

    for (int i = leftBoundary; i < size && Summedcounts[i].Sum <= b2; ++i) {
        cout << "Region: " << Summedcounts[i].Region << ", Sum: " << Summedcounts[i].Sum << endl;
        countsFound = true;  // Set flag to true if any counts are found within the range
    }

    if (!countsFound) {
        cout << "No counts found in the specified range." << endl;
    }
}

int main() {
    Read_Data(); 
    CalculateBirthSums(); 

    auto start_time = high_resolution_clock::now();

    int b1, b2;
    cout << "Enter the lower bound (b1) and upper bound (b2) for the birth counts range: ";
    cin >> b1 >> b2;

    InterpolationSearch(Summedcounts, MAXSUMS, b1, b2);
    
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end_time - start_time);

    cout << "Binary execution time: " << duration.count() << " nanoseconds" << endl;

    return 0;
}