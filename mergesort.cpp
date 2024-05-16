#include "readFile.h" //access read_print.h
#include <iostream>
#include <string>
#include <chrono> // library for time calculation
#include <vector>
#include <algorithm>

using namespace std;
using namespace chrono; 


bool compareRows(const Row &a, const Row &b) {
    if (a.Region != b.Region) //sort based on Region, if Regions are different return false or true
        return a.Region < b.Region;  
    else // If Regions are the same, sort based on Count
        return a.Count < b.Count;
}

// Merge function for Merge Sort
void merge(Row arr[], int l, int m, int r) {
    int n1 = m - l + 1; //number of rows from top to mid
    int n2 = r - m;     //number of rows from mid to bottom

    Row L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];    //copy rows from top to median, from array of structs to L[]
    for (int j = 0; j < n2; j++)  
        R[j] = arr[m + 1 + j];    //copy rows from median to bottom, from array of structs to R[]

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (compareRows(L[i], R[j])) { 
            arr[k] = L[i];  // if a < b is true put region or count at the higher row
            i++;
        } else {
            arr[k] = R[j];  //if a < b is false put region or count at the lower row
            j++;
        }
        k++;
    }

    while (i < n1) {   //if i reached n1 sort only high to mid 
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {  //if j reached n2 sort only mid to low
        arr[k] = R[j];
        j++;
        k++;
    }
}

// mergesort function
void mergeSort(Row arr[], int l, int r) {  
    if (l >= r) {   //compare higher row with lower row to stop loop
        return;
    }
    int m = l + (r - l) / 2; //find median
    mergeSort(arr, l, m);    //sort from high to median 
    mergeSort(arr, m + 1, r); //sort from median to lower
    merge(arr, l, m, r);      
}


void Mergesort() {
    mergeSort(data, 0, row_counter - 1);  //send all rows from the file to the mergesort function
}


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

int main()
{
   
    Read_Data(); //access Read_Data() from read_print.h

    auto start_time = high_resolution_clock::now(); //start the clock
    Mergesort();
    auto end_time = high_resolution_clock::now();   //stop the clock
    
    Print_Data(); 

    auto duration = duration_cast<nanoseconds>(end_time - start_time);
    cout << "Merge Sort execution time: " << duration.count() << " nanoseconds" << endl;

    return 0;
}

