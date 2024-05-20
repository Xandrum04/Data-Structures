#include "heapsort.h"
#include <iostream>
#include <string>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

void BinaryInterpolationSearch(SummedCount Summedcounts[], int size, int b1, int b2) {
    heapSort(Summedcounts, size);

    int low = 0, high = size - 1;
    int leftBoundary = -1;
    bool countsFound = false;

    // Exponential search to find the range
    int step = sqrt(size);
    int next = low;

    while (next < high && Summedcounts[next].Sum < b1) {
        next += step;
        step *= 2;
    }

    // Determine the correct high boundary after exponential search
    int expLow = next / 2;
    int expHigh = min(next, high);

    // Perform binary search within the found range
    while (expLow <= expHigh) {
        int mid = expLow + (expHigh - expLow) / 2;
        
        if (Summedcounts[mid].Sum == b1) {
            leftBoundary = mid;
            break;
        }
        if (Summedcounts[mid].Sum < b1) {
            expLow = mid + 1;
        } else {
            expHigh = mid - 1;
        }
    }

    if (leftBoundary == -1) {
        leftBoundary = expLow;
    }

    cout << "Regions with summed birth counts in the range [" << b1 << ", " << b2 << "]:" << endl;

    for (int i = leftBoundary; i < size && Summedcounts[i].Sum <= b2; ++i) {
        cout << "Region: " << Summedcounts[i].Region << ", Sum: " << Summedcounts[i].Sum << endl;
        countsFound = true;
    }

    if (!countsFound) {
        cout << "No regions found with summed birth counts in the given range." << endl;
    }
}

int main() {
    Read_Data(); 
    CalculateBirthSums(); 

    auto start_time = high_resolution_clock::now();

    int b1, b2;
    cout << "Enter the lower bound (b1) and upper bound (b2) for the birth counts range: ";
    cin >> b1 >> b2;

    BinaryInterpolationSearch(Summedcounts, MAXSUMS, b1, b2);
    
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end_time - start_time);

    cout << "Binary execution time: " << duration.count() << " nanoseconds" << endl;

    return 0;
}