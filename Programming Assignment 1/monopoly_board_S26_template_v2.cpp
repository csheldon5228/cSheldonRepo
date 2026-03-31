#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// -------------------------------
// Data class (NOT a struct)
// -------------------------------
class MonopolySpace {
public:
    string propertyName;
    string propertyColor;
    int value;
    int rent;

    MonopolySpace() {
        propertyName = "Empty Space";
        propertyColor = "None";
        value = 0;
        rent = 0;
    }

    MonopolySpace(string propertyName, string propertyColor, int value, int rent) {
        this->propertyName = propertyName;
        this->propertyColor = propertyColor;
        this->value = value;
        this->rent = rent;
    }

    bool isEqual(MonopolySpace other) { // Only on the basis of name
        if (other.propertyName == this->propertyName ) {
            return true;
        }
        return false;
    }

    void print() {
        cout << "Name: " << this->propertyName << ", Color: " << this->propertyColor << ", Value: $" <<
            this->value << ", Rent: $" << this->rent << endl;
    }
};

// -------------------------------
// Template Node class (NOT a struct)
// -------------------------------
template <typename T>
class Node {
public:
    T data;
    Node<T>* nextNode;

    Node(T value) {
        data = value;
        nextNode = nullptr;
    }
};

// -------------------------------
// Template Circular Linked List class
// Spring 2026 version: traversable board
// -------------------------------
template <typename T>
class CircularLinkedList {
private:
    Node<T>* headNode;
    Node<T>* tailNode;

    // player cursor for traversal-based gameplay
    Node<T>* playerNode;

    int nodeCount;
    const int MAX_SPACES = 40;
    int passGoCount;

public:
    CircularLinkedList() {
        headNode = nullptr;
        tailNode = nullptr;
        playerNode = nullptr;

        nodeCount = 0;
        passGoCount = 0;
    }

    // -------------------------------
    // Board Construction Policy (Reminder)
    // -------------------------------
    // Spaces are added during board construction BEFORE gameplay.
    // You choose how to construct the board:
    // - hardcode spaces, read from file, or generate programmatically
    // The only non-negotiable requirement:
    // - enforce MAX_SPACES
    // - maintain circular integrity
    // -------------------------------

    // -------------------------------
    // Core A: Add a Space with Capacity Enforcement
    // -------------------------------
    bool addSpace(T value) { // basically just appends
        if (isFull()) {
            cout << "Board is full!" << endl;
            return false;
        }

        Node<T> *newNode = new Node<T>(value);
        if (isEmpty()) {
            headNode = newNode;
            tailNode = newNode;
            playerNode = newNode;
            newNode->nextNode = headNode; // circularity
        }
        else {
            tailNode->nextNode = newNode;
            tailNode = newNode;
            tailNode->nextNode = headNode; // circularity
        }
        // - nodeCount++
        nodeCount++;
        return false;
    }

    bool isEmpty() {  return nodeCount == 0; }         // Checks if list is empty :)
    bool isFull() { return nodeCount == MAX_SPACES; }  // Checks if list is full/at capacity

    // -------------------------------
    // Core B: Add Multiple Spaces at Once
    // -------------------------------
    int addMany(vector<T> values) {
        if (isFull() || values.size() == 0) {
            return 0;
        }
        int i = 0;
        while (nodeCount < MAX_SPACES && i < values.size()) {
            addSpace(values[i]);
            i++;
        }
        return i + 1;
    }

    // -------------------------------
    // Core C: Traversal-Based Player Movement
    // -------------------------------
    void movePlayer(int steps) {
        if (isEmpty()) {
            return;
        }

        for (int i = 0; i < steps; i++) {
            playerNode = playerNode->nextNode; //move player, THEN check
            if (playerNode == headNode) {
                passGoCount++;
            }
        }
    }

    int getPassGoCount() {
        return passGoCount;
    }

    // -------------------------------
    // Core D: Controlled Board Display
    // -------------------------------
    void printFromPlayer(int count) {
        // if amt of spaces is short, don't iterate back over player
        if (isEmpty()) {
            return;
        }
        if (nodeCount == 1) {
            playerNode->data.print();
            return;
        }
        Node<T> *traverse = playerNode->nextNode;
        int i = 0;
        while (i < count && traverse != playerNode) {
            traverse->data.print();
            traverse = traverse->nextNode;
            i++;
        }
    }

    // Optional helper: print full board once (one full cycle)
    void printBoardOnce() {
        if (isEmpty()) {
            return;
        }
        Node<T> *traverse = headNode;
        traverse->data.print();
        traverse = traverse->nextNode;
        while (traverse != headNode) {
            traverse->data.print();
            traverse = traverse->nextNode;
        }
    }

    // -------------------------------
    // Advanced Option A (Level 1): removeByName
    // -------------------------------
    bool removeByName(string name) {

        // find node via checking if curr->next.name = name, check for head/tail, delete node accordingly
        if (isEmpty()) {
            return false;
        }

        Node<T> *temp = headNode;
        if (nodeCount == 1) {
            if (headNode->data.propertyName == name) {
                tailNode = nullptr;
                headNode = nullptr;
                playerNode = nullptr;
                delete temp;
                return true;
            }
            else {
                return false;
            }
        }

        int i = 0;
        while (temp->nextNode->data.propertyName != name) {
            temp = temp->nextNode;
            if (i > nodeCount) {
                return false;
            }
            i++;
        }
        if (temp->nextNode == headNode) {
            headNode = temp->nextNode->nextNode;
            tailNode->nextNode = headNode;
            rescuePlayer(temp->nextNode);
            temp = temp->nextNode;
            delete temp;
        }
        else if (temp->nextNode == tailNode) {
            tailNode = temp;
            temp = temp->nextNode;
            tailNode->nextNode = temp->nextNode;
            rescuePlayer(temp);
            delete temp;
        }
        else {
            Node<T> *temp2 = temp->nextNode;
            temp->nextNode = temp2->nextNode;
            rescuePlayer(temp2);
            delete temp2;
        }
        return true;
    }

    void rescuePlayer(Node<T> *temp) {
        if (temp == playerNode) {
            playerNode = temp->nextNode;
        }
    }

    // -------------------------------
    // Advanced Option A (Level 1): findByColor
    // -------------------------------
    vector<string> findByColor(string color) {
        vector<string> matches;
        Node<T> *traverse = headNode;
        for (int i = 0; i < nodeCount; i++) {
            if (traverse->data.propertyColor == color) {
                matches.push_back(traverse->data.propertyName);
            }
            traverse = traverse->nextNode;
        }
        return matches;
    }

    /* ////// OPTED FOR OPTION A //////
    // -------------------------------
    // Advanced Option B (Level 2): Mirror the Board (Circular Reversal)
    // -------------------------------
    void mirrorBoard() {
        // TODO:
        // - Reverse the direction of the circular list by reversing next pointers
        // - Preserve circular structure
        // - Correctly handle empty list and single-node list
        // - Player cursor must remain on the same logical space after reversal
        cout << "mirrorBoard unwritten" << endl;
    }
    */

    // -------------------------------
    // Edge-case helper: countSpaces O(n)
    // -------------------------------
    int countSpaces() {
        if (headNode == nullptr) {
            return 0;
        }
        int count = 1;
        Node<T> *traverse = headNode->nextNode;
        while (traverse != headNode) {
            count++;
            traverse = traverse->nextNode;
        }
        return count;
    }

    // -------------------------------
    // Cleanup
    // -------------------------------
    void clear() {
        if (isEmpty()) {
            return;
        }
        tailNode->nextNode = nullptr;
        while (headNode->nextNode != nullptr) {
            Node<T> *temp = headNode;
            headNode = headNode->nextNode;
            delete temp;
        }
        Node<T> *temp = headNode;
        headNode = nullptr;
        tailNode = nullptr;
        playerNode = nullptr;
        delete temp;
    }
};

// -------------------------------
// Main: playable loop demo
// -------------------------------
int rollDice2to12() {
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    CircularLinkedList<MonopolySpace> board;

    // -------------------------------
    // Board Construction Phase
    // -------------------------------
    // You decide how to build the board:
    // - hardcode spaces, load from file, or generate spaces programmatically
    // The only requirement: never exceed MAX_SPACES and keep the list circular.
    //
    // Example (hardcoded) usage:
    // vector<MonopolySpace> spaces;
    // spaces.push_back(MonopolySpace("GO","None",0,0));
    // ...
    // board.addMany(spaces);
    //
    // NOTE: This starter calls addSpace once to show the intended API,
    // but your final submission should build a meaningful board.

    ifstream inputFile("MonopolySpaces.csv");
    vector<MonopolySpace> spaces;

    string line;
    string name;
    string color;
    int value;
    string valuestr;
    int rent;
    string rentstr;

    while (!inputFile.eof()) {

        getline(inputFile, line);
        istringstream iss(line);

        getline(iss, name, ',');
        getline(iss, color, ',');
        getline(iss, valuestr, ',');
        getline(iss, rentstr, ',');

        value = std::stoi(valuestr);
        rent = std::stoi(rentstr);

        spaces.push_back(MonopolySpace(name, color, value, rent));
    }

    board.addMany(spaces);
    inputFile.close();

    // -------------------------------
    // Playable Traversal Loop
    // -------------------------------
    for (int turn = 1; turn <= 10; turn++) {
        int roll = rollDice2to12();
        cout << "\nTurn " << turn << " | Rolled: " << roll << endl;

        board.movePlayer(roll);

        cout << "Board view from player (next 5 spaces):" << endl;
        board.printFromPlayer(5);

        cout << "Times passed GO so far: " << board.getPassGoCount() << endl;
    }

    // -------------------------------
    // Advanced Feature Demos (students choose path)
    // -------------------------------
    // Option A examples:
    // board.removeByName("Baltic Avenue");
    // vector<string> brownProps = board.findByColor("Brown");
    //
    // Option B example:
    // board.mirrorBoard();

    return 0;
}
