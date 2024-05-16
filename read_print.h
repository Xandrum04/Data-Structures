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
    const int MAXSUMS = 17; //max number of summedCounts

    Row data[MAXROWS]; //make array of Row structs

    int row_counter=0;


struct SummedCount {
    string Region;
    int Sum;
};

SummedCount Summedcounts[MAXROWS]; // Make array of summed counts



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


void PrintSummedCounts(SummedCount Summedcounts[], int size) {
    cout << "Summed Birth Counts for Each Region between 2005 and 2022:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "Region: " << Summedcounts[i].Region << ", Sum: " << Summedcounts[i].Sum << endl;
    }
}

