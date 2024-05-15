#include "read_print.h" // Include the header file for function declarations
#include <iostream>
#include <string>
#include <chrono> // Library for time calculation
#include <vector> // For sorting
#include <algorithm> // For sort function

using namespace std;
using namespace chrono;

// Custom comparison function for sorting rows based on count of deaths and alphabetical order of regions
bool compareRows(const Row& a, const Row& b) {
    if (a.Count != b.Count) {
        return a.Count < b.Count; // Sort by count of deaths in ascending order
    } else {
        return a.Region < b.Region; // If counts are equal, sort by region name in alphabetical order
    }
}

// Heapify function to maintain heap property
void heapify(Row arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && !arr[l].Birth_Death && arr[l].Count < arr[largest].Count)
        largest = l;

    if (r < n && !arr[r].Birth_Death && arr[r].Count < arr[largest].Count)
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap Sort algorithm
void heapSort(Row arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }

    // Remove duplicate entries
    int uniqueIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i].Count != arr[uniqueIndex].Count || arr[i].Region != arr[uniqueIndex].Region) {
            uniqueIndex++;
            if (i != uniqueIndex) {
                arr[uniqueIndex] = arr[i];
            }
        }
    }
}

int main() {
    Read_Data(); // Populate the array with data from the file

    auto start_time = high_resolution_clock::now(); // Start the clock
    heapSort(data, row_counter); // Call the Heap Sort algorithm to sort the data
    auto end_time = high_resolution_clock::now(); // Stop the clock

    // Sort the data using custom comparison function
    vector<Row> sortedData(data, data + row_counter);
    sort(sortedData.begin(), sortedData.end(), compareRows);

    // Print the sorted data (only counts of deaths)
    for (const auto& row : sortedData) {
        if (!row.Birth_Death) {
            cout << "Count of Deaths in Region " << row.Region << ": " << row.Count << endl;
        }
    }

    auto duration = duration_cast<nanoseconds>(end_time - start_time); // Calculate the duration of execution
    cout << "Heap Sort execution time: " << duration.count() << " nanoseconds" << endl; // Display the execution time

    return 0;
}
