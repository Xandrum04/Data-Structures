#include "read_print.h" // Access read_print.h
#include <iostream>
#include <string>
#include <chrono> // Include chrono for time measurements

using namespace std;
using namespace chrono;

// Merge function to merge two sorted arrays
void merge(SummedCount arr[], int l, int m, int r) {
    int n1 = m - l + 1; // Number of elements in the left subarray
    int n2 = r - m; // Number of elements in the right subarray

    // Create temporary arrays
    SummedCount L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    int i = 0; // Initial index of the first subarray
    int j = 0; // Initial index of the second subarray
    int k = l; // Initial index of the merged subarray
    while (i < n1 && j < n2) {
        if (L[i].Sum <= R[j].Sum) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main function of merge sort
void mergeSort(SummedCount arr[], int l, int r) {
    if (l < r) {
        // Find the middle point to divide the array into two halves
        int m = l + (r - l) / 2;

        // Call mergeSort for the first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the two halves sorted in the previous steps
        merge(arr, l, m, r);
    }
}

int main()
{
    Read_Data(); // Call Read_Data() to read the data

    CalculateBirthSums(); // Calculate and store summed birth counts for each region between 2005 and 2022

    // Start measuring time
    auto start_time = high_resolution_clock::now();

    // Sort Summedcounts based on the total sum of each region in ascending order using MergeSort
    const int iterations = 1000; // Number of iterations for averaging
    for (int i = 0; i < iterations; ++i) {
        mergeSort(Summedcounts, 0, MAXSUMS - 1);
    }

    // Stop measuring time
    auto end_time = high_resolution_clock::now();

    // Calculate the duration of the sorting
    auto duration = duration_cast<microseconds>(end_time - start_time);  // Calculate the duration in microseconds

    // Print the contents of the Summedcounts array
    cout << "Summed Birth Counts for each region between 2005 and 2022 :" << endl << endl;
    PrintSummedCounts(Summedcounts, MAXSUMS);
    
    // Print the execution time of the merge sort
    cout << "Average MergeSort execution time: " << duration.count() / iterations << " microseconds" << endl;

    return 0;
}
