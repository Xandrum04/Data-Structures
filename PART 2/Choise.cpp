#include <iostream>

using namespace std;

void displayMenu() {
    cout << "Select the data structure type for loading the file:" << endl;
    cout << "1. Binary Search Tree (BST)" << endl;
    cout << "2. Hashing with chaining" << endl;
    cout << "Choice: ";
}

void loadIntoBST() {
    int choice;
    cout << "Select the type of Binary Search Tree (BST):" << endl;
    cout << "1. Load based on REGION" << endl;
    cout << "2. Load based on the NUMBER OF BIRTHS per day" << endl;
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Loading into Binary Search Tree (BST) based on REGION..." << endl;
            // Here you can place the code for loading into BST based on REGION
            break;
        case 2:
            cout << "Loading into Binary Search Tree (BST) based on BIRTH COUNT..." << endl;
            // Here you can place the code for loading into BST based on NUMBER OF BIRTHS
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

void loadIntoHashing() {
    cout << "Loading into Hashing with chaining..." << endl;
    // Here you can place the code for loading into Hashing (Γ)
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
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice < 1 || choice > 2);

    return 0;
}
