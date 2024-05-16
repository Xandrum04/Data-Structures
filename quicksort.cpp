#include "readFile.h" // access read_print.h
#include <iostream>
#include <string>
#include <chrono> // library for time calculation



using namespace std;
using namespace chrono;

bool compareRows(const Row &a, const Row &b) {
    if (a.Region != b.Region) // sort based on Region, if Regions are different return false or true
        return a.Region < b.Region;
    else // If Regions are the same, sort based on Count
        return a.Count < b.Count;
}

// Partition function for Quick Sort
int partition(Row arr[], int low, int high) {
    Row pivot = arr[high]; // pivot element
    int i = low - 1; // index of smaller element

    for (int j = low; j < high; j++) {
        if (compareRows(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]); // swap elements
        }
    }
    swap(arr[i + 1], arr[high]); // swap the pivot element with the element at i+1
    return i + 1;
}

// QuickSort function
void quickSort(Row arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // partitioning index
        quickSort(arr, low, pi - 1); // sort the elements before partition
        quickSort(arr, pi + 1, high); // sort the elements after partition
    }
}

void Quicksort() {
    quickSort(data, 0, row_counter - 1); // send all rows from the file to the quicksort function
}

void Print_Data()
{   
    //for loop to print array of structs data
    for (int i = 0; i < row_counter; ++i) {
        if(data[i].Birth_Death)
        cout << "Period: " << data[i].Period << ", Birth_Death: " << data[i].Birth_Death <<  "Birth"  << ", Region: " << data[i].Region << ", Count: " << data[i].Count << endl;
    }
}


int main() {
    Read_Data(); // access Read_Data() from read_print.h

    auto start_time = high_resolution_clock::now(); // start the clock
    Quicksort();
    auto end_time = high_resolution_clock::now(); // stop the clock

    Print_Data(); // access Print_Data() from read_print.h

    auto duration = duration_cast<nanoseconds>(end_time - start_time);
    cout << "Quick Sort execution time: " << duration.count() << " nanoseconds" << endl;

    return 0;
}
