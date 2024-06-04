
//minimum και maximum ασαφη η εκφωνηση
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

struct Node {
    Row data;
    Node* left;
    Node* right;
};

Node* createNode(Row data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

void insertNode(Node*& root, Row data) {
    if (!data.Birth_Death) {
        return;
    }
    if (root == nullptr) {
        root = createNode(data);
        return;
    }
    if (data.Count < root->data.Count) {
        insertNode(root->left, data);
    } else if (data.Count > root->data.Count) {
        insertNode(root->right, data);
    } else {
        if (data.Period < root->data.Period) {
            insertNode(root->left, data);
        } else {
            insertNode(root->right, data);
        }
    }
}

Node* buildBST() {
    ifstream inputFile("bd-dec22-births-deaths-by-region.txt");
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return nullptr;
    }

    string line;
    bool FirstLineSkipped = false;
    Node* root = nullptr;

    while (getline(inputFile, line)) {
        if (!FirstLineSkipped) {
            FirstLineSkipped = true;
            continue;
        }

        stringstream ss(line);
        string token;
        string tokens[4];
        int index = 0;

        while (getline(ss, token, ',')) {
            tokens[index++] = token;
            if (index >= 4) {
                break;
            }
        }

        if (index != 4) {
            cerr << "Error: Invalid data format in line: " << line << endl;
            continue;
        }

        try {
            Row rowData;
            rowData.Period = stoi(tokens[0]);
            rowData.Birth_Death = (tokens[1] == "Births");
            rowData.Region = tokens[2];
            rowData.Count = stoi(tokens[3]);

            insertNode(root, rowData);
        } catch (const exception& e) {
            cerr << "Error: Invalid integer conversion in line: " << line << endl;
            continue;
        }
    }

    inputFile.close();
    return root;
}

void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Search for Period/Periods with the minimum Count of Births." << endl;
    cout << "2. Search for Period/Periods with the maximum Count of Births." << endl;
    cout << "3. Exit." << endl;
}

Row findMin(Node* root) {
    if (root == nullptr) {
        throw runtime_error("Tree is empty");
    }
    Node* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->data;
}

Row findMax(Node* root) {
    if (root == nullptr) {
        throw runtime_error("Tree is empty");
    }
    Node* current = root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->data;
}

int main() {
    Node* root = buildBST();
    if (root != nullptr) {
        cout << "Binary Search Tree built successfully." << endl;

        int choice;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    try {
                        Row minRow = findMin(root);
                        cout << "Period with minimum Count of Births: " << minRow.Period << endl;
                        cout << "Region: " << minRow.Region << endl;
                        cout << "Count: " << minRow.Count << endl;
                    } catch (const runtime_error& e) {
                        cerr << e.what() << endl;
                    }
                    break;
                }
                case 2: {
                    try {
                        Row maxRow = findMax(root);
                        cout << "Period with maximum Count of Births: " << maxRow.Period << endl;
                        cout << "Region: " << maxRow.Region << endl;
                        cout << "Count: " << maxRow.Count << endl;
                    } catch (const runtime_error& e) {
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
        cerr << "Failed to build Binary Search Tree." << endl;
    }
    return 0;
}
