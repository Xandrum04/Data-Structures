#include "heapsort.h"
#include <iostream>
#include <string>
#include <chrono>
#include <math.h>

using namespace std;
using namespace chrono;

int InterpolationBinarySearch(SummedCount Summedcounts[], int size, int key) {
    int left = 0, right = size - 1;

    while (key != Summedcounts[left].Sum && key != Summedcounts[right].Sum) {
        int size = right - left + 1;
        int next = left + ((size * (key - Summedcounts[left].Sum)) / (Summedcounts[right].Sum - Summedcounts[left].Sum));
        
        if (key > Summedcounts[next].Sum) {
            int i = 1;
            while (key > Summedcounts[next + i * (int)sqrt(size) - 1].Sum) {
                i++;
            }
            right = next + i * (int)sqrt(size);
            left = next + (i - 1) * (int)sqrt(size);
        } else if (key < Summedcounts[next].Sum) {
            int i = 1;
            while (key < Summedcounts[next - i * (int)sqrt(size) + 1].Sum) {
                i++;
            }
            right = next - (i - 1) * (int)sqrt(size);
            left = next - i * (int)sqrt(size);
        } else {
            return next;
        }
    }
    
    if (key == Summedcounts[left].Sum) {
        return left;
    } else if (key == Summedcounts[right].Sum) {
        return right;
    } else {
        return -1; // Not found
    }
}

int main() {
    Read_Data();
    CalculateBirthSums();

    auto start_time = high_resolution_clock::now();

    int b1, b2;
    cout << "Enter the lower bound (b1) and upper bound (b2) for the birth counts range: ";
    cin >> b1 >> b2;

    int leftIndex = InterpolationBinarySearch(Summedcounts, MAXSUMS, b1);
    int rightIndex = InterpolationBinarySearch(Summedcounts, MAXSUMS, b2);

    cout << "Regions with summed birth counts in the range [" << b1 << ", " << b2 << "]:" << endl;
    
    if (leftIndex == -1 || rightIndex == -1) {
        cout << "No regions found with summed birth counts in the given range." << endl;
    } else {
        for (int i = leftIndex; i <= rightIndex; ++i) {
            cout << "Region: " << Summedcounts[i].Region << ", Sum: " << Summedcounts[i].Sum << endl;
        }
    }

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end_time - start_time);

    cout << "Binary execution time: " << duration.count() << " nanoseconds" << endl;

    return 0;
}