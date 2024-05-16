#include "read_print.h" //access read_print.h
#include <iostream>
#include <string>
<<<<<<< HEAD
#include <chrono> // Include chrono for time measurements
=======
#include <chrono> // library for time calculation
#include <vector>
#include <algorithm>

>>>>>>> 4ab77642f2d3be70fa9f1682d87760a6839fc5d3

using namespace std;
using namespace chrono;

// Function to calculate birth sums for each region between 2005 and 2022
void CalculateBirthSums() {
    // Initialize array to store summed counts for each region
    

    // Initialize summed counts for each region to zero
    for (int i = 0; i < MAXSUMS; ++i) {
        Summedcounts[i].Region = data[i].Region;
        Summedcounts[i].Sum = 0;
    }

    // Calculate summed counts for each region between 2005 and 2022
    for (int i = 0; i < row_counter; ++i) {
        if (data[i].Period >= 2005 && data[i].Period <= 2022 && data[i].Birth_Death) {
            // Find the index of the region in Summedcounts array
            int regionIndex = -1;
            for (int j = 0; j < MAXROWS; ++j) {
                if (Summedcounts[j].Region == data[i].Region) {
                    regionIndex = j;
                    break;
                }
            }
            // Add birth count to the summed count for the corresponding region
            if (regionIndex != -1) {
                Summedcounts[regionIndex].Sum += data[i].Count;
            }
        }
    }
}


// Partition function for QuickSort
int partition(SummedCount arr[], int low, int high) {
    SummedCount pivot = arr[high]; // Choose the pivot element
    int i = low - 1; // Index of smaller element

    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j].Sum <= pivot.Sum) {
            i++; // Increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Main QuickSort function
void quickSort(SummedCount arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


<<<<<<< HEAD

=======
void Print_Data() {
    string current_region = "";
    int total_birth_count = 0;

    // Create a vector of pairs to store region and total birth count
    vector<pair<string, int>> region_counts;

    for (int i = 0; i < MAXROWS; ++i) {
        if (data[i].Birth_Death) {
            if (data[i].Region != current_region) {
                if (current_region != "") {
                    region_counts.push_back(make_pair(current_region, total_birth_count));
                }
                current_region = data[i].Region;
                total_birth_count = 0;
            }
            total_birth_count += data[i].Count;
        }
    }

    // Add the last region and its total birth count to the vector
    if (current_region != "") {
        region_counts.push_back(make_pair(current_region, total_birth_count));
    }

    // Sort the vector based on total birth count
    sort(region_counts.begin(), region_counts.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second < b.second;
    });

    // Print the sorted regions and their total birth counts
    for (const auto& pair : region_counts) {
        cout << "Region: " << pair.first << ", Total Birth Count: " << pair.second << endl;
    }
}
>>>>>>> 4ab77642f2d3be70fa9f1682d87760a6839fc5d3



int main() {

    Read_Data(); //access Read_Data() from read_print.h

    CalculateBirthSums(); // Calculate and store summed birth counts for each region between 2005 and 2022

     // Start measuring time
    auto start_time = high_resolution_clock::now();

    // Sort Summedcounts based on the total sum of each region using QuickSort
    quickSort(Summedcounts, 0, MAXSUMS - 1);

    // Stop measuring time
    auto end_time = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<nanoseconds>(end_time - start_time);

    // Print the contents of Summedcounts array
    PrintSummedCounts(Summedcounts, MAXSUMS);
    
// Print the execution time
    cout << "MergeSort execution time: " << duration.count() << " nanoseconds" << endl;
    
    return 0;
}
