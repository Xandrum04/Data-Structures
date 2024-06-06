
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Row {
    int Period;
    bool Birth_Death;   // 0=Death , 1=Birth
    string Region;
    int Count;
};

// Structure of a BST node
struct Node {
    Row data;
    Node* left; //pointer to left subtree
    Node* right;  //pointer to right subtree
};

// Function to create a new node that returns itself
Node* createNode(Row data) {
    Node* newNode = new Node();   //make newNode that points to struct Node
    newNode->data = data;         // copy elements of struct row and transfer them to struct newNode
    newNode->left = newNode->right = nullptr;      //make left and right subtree pointer null
    return newNode;               //return new node
}

// Function to insert a new node into the BST
void insertNode(Node*& root, Row data) {

    // Only insert if the data is for births
    if (!data.Birth_Death) {
        return;
    }

    if (root == nullptr) {    //if there is no root create one
        root = createNode(data);
        return;
    }

    // Compare the new count with the current node's count to decide where to insert
    if (data.Count < root->data.Count) {     // if the count I want to insert is  < than the root's 
        insertNode(root->left, data);        // then insert it as a left child of the root

    } else if (data.Count > root->data.Count) {  // if the count I want to insert is > than the root's 
        insertNode(root->right, data);           // then insert it as a right child of the root


    } else {
        // If region is the same, decide based on period
        if (data.Period < root->data.Period) { // if the period of the region I want to insert is < than the root's 
            insertNode(root->left, data);      // then insert it as a left child of the root

        } else {                                // if the period of the region I want to insert is > than the root's
            insertNode(root->right, data);      // then insert it as a right child of the root
        }
    }
}

// Function to read data from the file and build the BST
Node* buildBST() {

    //open the file and check for errors
    ifstream inputFile("bd-dec22-births-deaths-by-region.txt");
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return nullptr;
    }

    string line;
    bool FirstLineSkipped = false;     // Flag to track whether the first line has been skipped
    Node* root = nullptr;              // root that points to the struct Node is given null value

    while (getline(inputFile, line)) {
        if (!FirstLineSkipped) {
            FirstLineSkipped = true;
            continue;           // skip first line
        }

        stringstream ss(line);     //read and write in string line
        string token;              // data from file to be read
        string tokens[4];

        int index = 0;    //number of commas to be read

        while (getline(ss, token, ',')) {  //read row of file and return data(token) until it reaches a comma
            tokens[index++] = token; //store data from between the commas of each row in tokens[]
            if (index >= 4) {
                break;  // Avoid accessing out of bounds
            }
        }

        if (index != 4) {
            cerr << "Error: Invalid data format in line: " << line << endl;
            continue;   //incorrect amount of commas
        }

        try {
            //store read data in struct rowdata
            Row rowData;
            rowData.Period = stoi(tokens[0]);
            rowData.Birth_Death = (tokens[1] == "Births"); // Set true if "Births", false otherwise
            rowData.Region = tokens[2];
            rowData.Count = stoi(tokens[3]);

            insertNode(root, rowData);   //insert the read data into a new node
        } catch (const exception& e) {
            cerr << "Error: Invalid integer conversion in line: " << line << endl;
            continue;  //catch errors when converting to integers
        }
    }

    inputFile.close();   //close file
    return root;  //return root that points to struct Node 
}

void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Search for Period/Periods with the minimum Count of Births." << endl;
    cout << "2. Search for Period/Periods with the maximum Count of Births." << endl;
    cout << "3. Exit." << endl;
}

// Function to find the minimum count in the tree
Row findMin(Node* root) {
    if (root == nullptr) {
        throw runtime_error("Tree is empty");   // If the root is null, print error: tree is empty
    }

    Node* current = root;            // set the root to be the current root
    while (current->left != nullptr) {     // while the left sub tree of the current root points somewhere
        current = current->left;           // set the root of the left subtree as current root
    } 
    return current->data;                  //return the data of the node with the min count
}

// Function to find the maximum count in the tree
Row findMax(Node* root) {
    if (root == nullptr) {
        throw runtime_error("Tree is empty");   // If the root is null, throw error
    }

    Node* current = root;            // set the root to be the current root
    while (current->right != nullptr) {     // while the right sub tree of the current root points somewhere
        current = current->right;           // set the root of the right subtree as current root
    } 
    return current->data;                  //return the data of the node with the max count
}


int main() {
    Node* root = buildBST();     //Read file and create BST
    if (root != nullptr) {       //if tree not empty 
        cout << "Binary Search Tree built successfully." << endl;

        int choice;
        do {
            displayMenu();        // Display menu options
            cout << "Enter your choice: ";
            cin >> choice;

            //switch case for menu options
            switch (choice) {
                case 1: {
                    try {
                        Row minRow = findMin(root); //give minRow the return value of findMin

                        //print the data of the node with the min count
                        cout << "Period with minimum Count of Births: " << minRow.Period << endl;
                        cout << "Region: " << minRow.Region << endl;
                        cout << "Count: " << minRow.Count << endl;

                    } catch (const runtime_error& e) {  // if there is runtime error print that error
                        cerr << e.what() << endl;
                    }
                    break;
                }
                case 2: {
                    try {
                        Row maxRow = findMax(root);  //give maxRow the return value of findMax

                        //print the data of the node with the max count
                        cout << "Period with maximum Count of Births: " << maxRow.Period << endl;
                        cout << "Region: " << maxRow.Region << endl;
                        cout << "Count: " << maxRow.Count << endl;

                    } catch (const runtime_error& e) {  // if there is runtime error print that error
                        cerr << e.what() << endl;
                    }
                    break;
                }
                case 3:
                    cout << "Exiting the application." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            }
        } while (choice != 3);
    } else {
        cerr << "Failed to build Binary Search Tree." << endl;      //if tree is empty print error
    }
    return 0;
}
