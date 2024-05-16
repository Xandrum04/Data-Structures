#include "readFile.h"  //access read_print.h
#include <iostream>
#include <string>

using namespace std;



void Print_Data()
{   
    //for loop to print array of structs data
    for (int i = 0; i < row_counter; ++i) {
        cout << "Period: " << data[i].Period << ", Birth_Death: " << (data[i].Birth_Death ? "Birth" : "Death") << ", Region: " << data[i].Region << ", Count: " << data[i].Count << endl;
    }
}



int main()
{
   
    Read_Data(); //access Read_Data() from read_print.h

    Print_Data(); //access Print_Data() from read_print.h

    return 0;
}


