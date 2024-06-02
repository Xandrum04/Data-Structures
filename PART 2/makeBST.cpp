#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
    newNode->left = newNode->right = nullptr;      // left and right subtree point to nothing
    return newNode;               //return new node
}

// Function to insert a new node into the BST
void insertNode(Node*& root, Row data) {

// Only insert if the data is for births
    if (!data.Birth_Death) {
        return;
    }



    if (root == nullptr) {          //if there is no root create one
        root = createNode(data);
        return;
    }

    // Compare the new region with the current node's region to decide where to insert
    if (data.Region < root->data.Region) {   // if the region i want to insert is alphabetically < than the root's 
        insertNode(root->left, data);        // then insert it as a left child of the root

    } else if (data.Region > root->data.Region) {  // if the region i want to insert is alphabetically > than the root's 
        insertNode(root->right, data);             // then insert it as a right child of the root



    } else {
        // If region is the same, decide based on period
        if (data.Period < root->data.Period) { // if the period of the region i want to insert is < than the root's 
            insertNode(root->left, data);      // then insert it as a left child of the root

        } else {                                // if the period of the region i want to insert is > than the root's
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
    bool FirstLineSkipped = false;  // Flag to track whether the first line has been skipped
    Node* root = nullptr;     // root that points to the struct Node is given null value

    while (getline(inputFile, line)) {
        if (!FirstLineSkipped) {
            FirstLineSkipped = true;
            continue;   // skip first line
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

// Function to traverse and print the BST in inorder
void inorderTraversal(Node* root) {
    if (root != nullptr) {      //if tree not empty
        inorderTraversal(root->left);   // tranverse left subtree
        cout << "Region: " << root->data.Region << ", Period: " << root->data.Period << ", Count: " << root->data.Count << endl;  // print root (father) node
        inorderTraversal(root->right);  //tranverse right subtree
    }
}

// Function to search for the number of births for a specific time period and region
int searchBirthCount(Node* root, int period, const string& region) {
    
    // Compare the period and region with the current node's data
    if (root->data.Region == region && root->data.Period == period) {
        // If found, return the count
        return root->data.Count;
    } else if (root->data.Region > region || (root->data.Region == region && root->data.Period > period)) {
        // If the target period and region are smaller, search in the left subtree
        return searchBirthCount(root->left, period, region);
    } else {
        // If the target period and region are greater, search in the right subtree
        return searchBirthCount(root->right, period, region);
    }
}


// Function to modify the number of births for a specific time period and region
void modifyBirthCount(Node* root, int period, const string& region, int newCount) {
    // Base case: If the root is null, the data doesn't exist
    if (root == nullptr) {
        cout << "Data not found." << endl;
        return;
    }

    // Compare the period and region with the current node's data
    if (root->data.Region == region && root->data.Period == period) {
        // If found, modify the count
        root->data.Count = newCount;
        cout << "Number of births for period " << period << " in " << region << " modified to " << newCount << endl;
    } else if (root->data.Region > region || (root->data.Region == region && root->data.Period > period)) {
        // If the target period and region are smaller, search in the left subtree
        modifyBirthCount(root->left, period, region, newCount);
    } else {
        // If the target period and region are greater, search in the right subtree
        modifyBirthCount(root->right, period, region, newCount);
    }
}


// Function to display the menu
void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Display the BST with inorder traversal." << endl;
    cout << "2. Search for the number of births for a specific time period and region." << endl;
    cout << "3. Modify the number of births for a specific time period and region." << endl;
    cout << "4. Delete a record based on the region." << endl;
    cout << "5. Exit the application." << endl;
}




int main() {
    Node* root = buildBST();   //Read file and create BST
    if (root != nullptr) {   //if tree not empty 
        cout << "Binary Search Tree built successfully." << endl;  

        int choice;
        do {
            displayMenu(); // Display menu options
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Inorder Traversal:" << endl;   //print the inorder trsaversal of the current tree
                    inorderTraversal(root);
                    break;
                case 2:{
                    int searchPeriod, searchCount;
                    string searchRegion;
                    cout << "Enter the period to search: ";
                    cin >> searchPeriod;
                    cin.ignore(); // Ignore newline character
                    cout << "Enter the region to search: ";
                    getline(cin, searchRegion);
                    searchCount = searchBirthCount(root, searchPeriod, searchRegion);
                    if (searchCount != -1) {
                    cout << "Number of births for period " << searchPeriod << " in " << searchRegion << ": " << searchCount << endl;
                    } else {
                    cout << "Data not found." << endl;
                    }
                    break;
                }
                    
                case 3: {
                    int modifyPeriod, newCount;
                    string modifyRegion;
                    cout << "Enter the period to modify: ";
                    cin >> modifyPeriod;
                    cin.ignore(); // Αγνόηση του χαρακτήρα νέας γραμμής
                    cout << "Enter the region to modify: ";
                    getline(cin, modifyRegion);
                    cout << "Enter the new count: ";
                    cin >> newCount;
                    modifyBirthCount(root, modifyPeriod, modifyRegion, newCount);
                    break;
                }
                   
                
                        
                case 4:
                    // Implement deletion functionality
                    break;
                case 5:
                    cout << "Exiting the application." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            }
        } while (choice != 5);

        
    } else {
        cerr << "Failed to build Binary Search Tree." << endl;   //if tree is empty print error
    }
    return 0;
}
