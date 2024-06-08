#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

struct Row {
    int Period;
    bool Birth_Death; // 0=Death, 1=Birth
    string Region;
    int Count;
};

// Hash table class with chaining
class HashTable {
private:
    vector<list<Row>> table;
    int size;

    // Hash function
    int hashFunction(const string& region) {
        int sum = 0;
        for (char ch : region) {
            sum += static_cast<int>(ch);
        }
        return sum % size;
    }

public:
    // Constructor to initialize hash table with given size
    HashTable(int s) : size(s), table(s) {}

    // Function to insert a row into the hash table
    void insert(Row data) {
        if (!data.Birth_Death) return; // Only insert if the data is for births
        int index = hashFunction(data.Region);
        table[index].push_back(data);
    }

    // Function to search for a row in the hash table
    Row* search(int period, const string& region) {
        int index = hashFunction(region);
        for (auto& row : table[index]) {
            if (row.Period == period && row.Region == region) {
                return &row;
            }
        }
        return nullptr;
    }

    // Function to update a row in the hash table
    bool update(int period, const string& region, int newCount) {
        int index = hashFunction(region);
        for (auto& row : table[index]) {
            if (row.Period == period && row.Region == region) {
                row.Count = newCount;
                return true;
            }
        }
        return false;
    }

    // Function to delete rows by region in the hash table
    void deleteByRegion(const string& region) {
        int index = hashFunction(region);
        table[index].remove_if([&region](const Row& row) {
            return row.Region == region;
        });
    }

    // Function to display all entries in the hash table
    void display() {
        for (int i = 0; i < size; ++i) {
            if (!table[i].empty()) {
                cout << "Bucket " << i << ":\n";
                for (const auto& row : table[i]) {
                    cout << "Region: " << row.Region << ", Period: " << row.Period << ", Count: " << row.Count << endl;
                }
                cout << endl;
            }
        }
    }
};

// Function to read data from the file and build the hash table
HashTable buildHashTable(int size) {
    ifstream inputFile("bd-dec22-births-deaths-by-region.txt");
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return HashTable(size);
    }

    string line;
    bool firstLineSkipped = false;
    HashTable hashTable(size);

    while (getline(inputFile, line)) {
        if (!firstLineSkipped) {
            firstLineSkipped = true;
            continue; // Skip the first line
        }

        stringstream ss(line);
        string token;
        string tokens[4];
        int index = 0;

        while (getline(ss, token, ',')) {
            tokens[index++] = token;
            if (index >= 4) break; // Avoid accessing out of bounds
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

            hashTable.insert(rowData);
        } catch (const exception& e) {
            cerr << "Error: Invalid integer conversion in line: " << line << endl;
            continue;
        }
    }

    inputFile.close();
    return hashTable;
}

// Function to display the menu
void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Display all entries in the hash table." << endl;
    cout << "2. Search for the number of births for a specific time period and region." << endl;
    cout << "3. Modify the number of births for a specific time period and region." << endl;
    cout << "4. Delete a record based on the region." << endl;
    cout << "5. Exit the application." << endl;
}

int main() {
    const int tableSize = 11; // Size of the hash table
    HashTable hashTable = buildHashTable(tableSize);

    cout << "Hash Table built successfully." << endl;

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Displaying all entries in the hash table:" << endl;
                hashTable.display();
                break;
            }
            case 2: {
                int searchPeriod;
                string searchRegion;
                cout << "Enter the period to search: ";
                cin >> searchPeriod;
                cin.ignore(); // Ignore newline character
                cout << "Enter the region to search: ";
                getline(cin, searchRegion);

                Row* result = hashTable.search(searchPeriod, searchRegion);
                if (result) {
                    cout << "Number of births for period " << searchPeriod << " in " << searchRegion << ": " << result->Count << endl;
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
                cin.ignore(); // Ignore newline character
                cout << "Enter the region to modify: ";
                getline(cin, modifyRegion);
                cout << "Enter the new count: ";
                cin >> newCount;

                if (hashTable.update(modifyPeriod, modifyRegion, newCount)) {
                    cout << "Number of births for period " << modifyPeriod << " in " << modifyRegion << " modified to " << newCount << endl;
                } else {
                    cout << "Data not found." << endl;
                }
                break;
            }
            case 4: {
                string deleteRegion;
                cout << "Enter the region to delete: ";
                cin.ignore(); // Ignore newline character
                getline(cin, deleteRegion);

                hashTable.deleteByRegion(deleteRegion);
                cout << "All records with region " << deleteRegion << " deleted successfully." << endl;
                break;
            }
            case 5:
                cout << "Exiting the application." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }
    } while (choice != 5);

    return 0;
}
