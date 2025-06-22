#include <iostream>
#include <vector>
#include <list>
using namespace std;

// Account Structure
struct Account {
    int accountNumber;
    double balance;
};

// Hash Table with Chaining
class HashTableChaining {
    vector<list<Account>> table;
    int size;

    int hashFunction(int accountNumber) {
        return accountNumber % size;
    }

public:
    HashTableChaining(int tableSize) : size(tableSize) {
        table.resize(size);
    }

    void insert(Account account) {
        int hashIndex = hashFunction(account.accountNumber);
        table[hashIndex].push_back(account);
    }

    Account* search(int accountNumber) {
        int hashIndex = hashFunction(accountNumber);
        for (auto& acc : table[hashIndex]) {
            if (acc.accountNumber == accountNumber)
                return &acc;
        }
        return nullptr;
    }
};

// Hash Table with Linear Probing
class HashTableLinearProbing {
    vector<Account> table;
    int size;
    const Account EMPTY_ACCOUNT = {-1, 0.0}; // Sentinel value for empty slots

    int hashFunction(int accountNumber) {
        return accountNumber % size;
    }

public:
    HashTableLinearProbing(int tableSize) : size(tableSize) {
        table.resize(size, EMPTY_ACCOUNT);
    }

    void insert(Account account) {
        int hashIndex = hashFunction(account.accountNumber);
        int originalIndex = hashIndex;

        while (table[hashIndex].accountNumber != -1) {
            hashIndex = (hashIndex + 1) % size;
            if (hashIndex == originalIndex) {
                cout << "Hash table is full!" << endl;
                return;
            }
        }

        table[hashIndex] = account;
    }

    Account* search(int accountNumber) {
        int hashIndex = hashFunction(accountNumber);
        int originalIndex = hashIndex;

        while (table[hashIndex].accountNumber != -1) {
            if (table[hashIndex].accountNumber == accountNumber)
                return &table[hashIndex];
            hashIndex = (hashIndex + 1) % size;
            if (hashIndex == originalIndex) break;
        }

        return nullptr;
    }
};

// Hash Table with Double Hashing
class HashTableDoubleHashing {
    vector<Account> table;
    int size;
    const Account EMPTY_ACCOUNT = {-1, 0.0}; // Sentinel value for empty slots

    // Primary hash function
    int hashFunction(int accountNumber) {
        return accountNumber % size;
    }

    // Secondary hash function
    int secondHashFunction(int accountNumber) {
        return (hashFunction(accountNumber) + (8 - (accountNumber % 8)))%11;
    }

public:
    HashTableDoubleHashing(int tableSize) : size(tableSize) {
        table.resize(size, EMPTY_ACCOUNT);
    }

    void insert(Account account) {
        int hashIndex = hashFunction(account.accountNumber);
        int stepSize = secondHashFunction(account.accountNumber);
        int originalIndex = hashIndex;

        while (table[hashIndex].accountNumber != -1) {
            hashIndex = (hashIndex + stepSize) % size;
            if (hashIndex == originalIndex) { // Table is full
                cout << "Hash table is full!" << endl;
                return;
            }
        }

        table[hashIndex] = account;
    }

    Account* search(int accountNumber) {
        int hashIndex = hashFunction(accountNumber);
        int stepSize = secondHashFunction(accountNumber);
        int originalIndex = hashIndex;

        while (table[hashIndex].accountNumber != -1) {
            if (table[hashIndex].accountNumber == accountNumber)
                return &table[hashIndex];
            hashIndex = (hashIndex + stepSize) % size;
            if (hashIndex == originalIndex) break; // Full cycle
        }

        return nullptr;
    }
};

int main() {
    // Example: Chaining
    cout << "Using Chaining:" << endl;
    HashTableChaining hashTableChaining(10);
    hashTableChaining.insert({101, 5000.0});
    hashTableChaining.insert({103, 2000.0});
    hashTableChaining.insert({102, 7000.0});
    Account* foundChaining = hashTableChaining.search(103);
    if (foundChaining)
        cout << "Found Account (Chaining): " << foundChaining->accountNumber << ", Balance: " << foundChaining->balance << endl;
    else
        cout << "Account not found (Chaining)!" << endl;

    // Example: Linear Probing
    cout << "\nUsing Linear Probing:" << endl;
    HashTableLinearProbing hashTableLinear(10);
    hashTableLinear.insert({101, 5000.0});
    hashTableLinear.insert({103, 2000.0});
    hashTableLinear.insert({102, 7000.0});
    Account* foundLinear = hashTableLinear.search(103);
    if (foundLinear)
        cout << "Found Account (Linear Probing): " << foundLinear->accountNumber << ", Balance: " << foundLinear->balance << endl;
    else
        cout << "Account not found (Linear Probing)!" << endl;

    // Example: Double Hashing
    cout << "\nUsing Double Hashing:" << endl;
    HashTableDoubleHashing hashTableDouble(11);
    hashTableDouble.insert({101, 5000.0});
    hashTableDouble.insert({103, 2000.0});
    hashTableDouble.insert({102, 7000.0});
    Account* foundDouble = hashTableDouble.search(103);
    if (foundDouble)
        cout << "Found Account (Double Hashing): " << foundDouble->accountNumber << ", Balance: " << foundDouble->balance << endl;
    else
        cout << "Account not found (Double Hashing)!" << endl;

    return 0;
}
