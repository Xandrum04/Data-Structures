#include <iostream>
#include <cstdlib> // For system() function

using namespace std;

// Function prototypes
void displayMenu();
void loadIntoBST();
void loadIntoHashing();

// Function to display the main menu
void displayMenu() {
    cout << "Select the data structure type for loading the file:" << endl;
    cout << "1. Binary Search Tree (BST)" << endl;
    cout << "2. Hashing with chaining" << endl;
    cout << "3. Exit Program" << endl; // Option to exit the program
    cout << "Choice: ";
}

// Function to load data into Binary Search Tree (BST)
void loadIntoBST() {
    int choice;
    cout << "Select the type of Binary Search Tree (BST):" << endl;
    cout << "1. Load based on REGION" << endl;
    cout << "2. Load based on BIRTH COUNT" << endl;
    cout << "3. Back to main menu" << endl; // Option to go back to main menu
    cout << "4. Exit Program" << endl; // Option to exit the program
    cout << "Choice: ";
    cin >> choice;

    string filename;
    switch (choice) {
        case 1:
            filename = "makeBST-A.exe"; // Assuming the executable file is named makeBST-A.exe
            break;
        case 2:
            filename = "makeBST-B.exe"; // Assuming the executable file is named makeBST-B.exe
            break;
        case 3:
            return; // Return to main menu
        case 4:
            exit(0); // Exit the program
        default:
            cout << "Invalid choice. Please try again." << endl;
            return;
    }

    // Execute the selected file
    cout << "Executing " << filename << "..." << endl;
    system(filename.c_str());
}

// Function to load data into Hashing with chaining
void loadIntoHashing() {
    string filename = "Hashing.exe"; // Assuming the executable file is named Hashing.exe

    // Execute the selected file
    cout << "Executing " << filename << "..." << endl;
    system(filename.c_str());
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                loadIntoBST();
                break;
            case 2:
                loadIntoHashing();
                break;
            case 3:
                exit(0); // Exit the program
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 3);

    return 0;
}
