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

 const int MAXROWS = 684;
    Row data[MAXROWS];

 int row_counter=0;

int Read_Data()
{

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

        stringstream ss(line);
        string token;
        string tokens[4];

        int index = 0;
        while (getline(ss, token, ',')) {
            tokens[index++] = token;
            if (index >= 4) {
                break; // Avoid accessing out of bounds
            }
        }

        if (index != 4) {
            cerr << "Error: Invalid data format in line: " << line << endl;
            continue;
        }

        try {
            data[row_counter].Period = stoi(tokens[0]);
            data[row_counter].Birth_Death = (tokens[1] == "Births"); // Set true if "Births", false otherwise
            data[row_counter].Region = tokens[2];
            data[row_counter].Count = stoi(tokens[3]);
        } catch (const exception &e) {
            cerr << "Error: Invalid integer conversion in line: " << line << endl;
            continue;
        }

        row_counter++;

        
    }

    inputFile.close();


}

void Print_Data()
{
    for (int i = 0; i < row_counter; ++i) {
        cout << "Period: " << data[i].Period << ", Birth_Death: " << data[i].Birth_Death << ", Region: " << data[i].Region << ", Count: " << data[i].Count << endl;
    }
}

