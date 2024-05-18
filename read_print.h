#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Row {
    int Period;
    bool Birth_Death;   //0=Death , 1=Birth
    string Region;
    int Count;
};

    const int MAXROWS = 648; //max number of rows
    const int MAXSUMS = 17; //max number of summedCount Regions

    Row data[MAXROWS]; //make array of Row structs

    int row_counter=0;


struct SummedCount {
    string Region;
    int Sum;
};

SummedCount Summedcounts[MAXSUMS]; // Make array of summed count Regions



int Read_Data()
{


    //open the file and check for errors
     ifstream inputFile("bd-dec22-births-deaths-by-region.txt");
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }



    string line;

    bool FirstLineSkipped = false;  // Flag to track whether the first line has been skipped

    while (getline(inputFile, line) && row_counter < MAXROWS) {
        if (!FirstLineSkipped) {
            FirstLineSkipped = true;
            continue;          // skip first line
        }

        stringstream ss(line); //read and write in string line
        string token; // data from file to be read
        string tokens[4]; 

        int index = 0; //number of commas to be read

        while (getline(ss, token, ',')) {   //read row of file and return data(token) until it reaches a comma
            tokens[index++] = token;   //store data from between the commas of each row in tokens[]
            if (index >= 4) {
                break; // Avoid accessing out of bounds
            }
        }

        if (index != 4) {
            cerr << "Error: Invalid data format in line: " << line << endl;
            continue;   //incorrect amount of commas
        }

        try {
            //store read data into the array of structs
            data[row_counter].Period = stoi(tokens[0]); 
            data[row_counter].Birth_Death = (tokens[1] == "Births"); // Set true if "Births", false otherwise
            data[row_counter].Region = tokens[2];
            data[row_counter].Count = stoi(tokens[3]);
        } catch (const exception &e) {
            cerr << "Error: Invalid integer conversion in line: " << line << endl;
            continue; //catch errors when converting to integers
        }

        row_counter++;  //go to the next row

        
    }

    inputFile.close();   //close file


}

// Function to calculate birth sums for each region between 2005 and 2022
void CalculateBirthSums() {
    

    // Initialize summed counts for each region to zero
    for (int i = 0; i < MAXSUMS; ++i) {
        Summedcounts[i].Region = data[i].Region;
        Summedcounts[i].Sum = 0;
    }

    // Calculate summed counts for each region between 2005 and 2022
    for (int i = 0; i < row_counter; ++i) {
        if (data[i].Period >= 2005 && data[i].Period <= 2022 && data[i].Birth_Death) { // if data[1].Birth_Detah == 1
            // Find the index of the region in Summedcounts array
            int regionIndex = -1;
            for (int j = 0; j < MAXROWS; ++j) {
                if (Summedcounts[j].Region == data[i].Region) { //make a copies of the regions in data[] that have births
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

// Function to calculate death sums for each region between 2005 and 2022
void CalculateDeathSums() {

    

    // Initialize summed counts for each region to zero
    for (int i = 0; i < MAXSUMS; ++i) {
        Summedcounts[i].Region = data[i].Region;
        Summedcounts[i].Sum = 0;
    }

    // Calculate summed counts for each region between 2005 and 2022
    for (int i = 0; i < row_counter; ++i) {
        if (data[i].Period >= 2005 && data[i].Period <= 2022 && (!data[i].Birth_Death)) { // if data[1].Birth_Detah == 0
            // Find the index of the region in Summedcounts array
            int regionIndex = -1;
            for (int j = 0; j < MAXROWS; ++j) {
                if (Summedcounts[j].Region == data[i].Region) { //make a copies of the regions in data[] that have deaths
                    regionIndex = j;
                    break;
                }
            }
            // Add death count to the summed count for the corresponding region
            if (regionIndex != -1) {
                Summedcounts[regionIndex].Sum += data[i].Count;
            }
        }
    }
}



void PrintSummedCounts(SummedCount Summedcounts[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << "Region: " << Summedcounts[i].Region << ", Sum: " << Summedcounts[i].Sum << endl;
    }
}


