#include <iostream>
#include <algorithm>
#include "BinarySearchTree.h"

using std::cout;
using std::string;
using std::vector;

/**
 * Trims leading and trailing quotes from a given string.
 * Useful for cleaning data extracted from CSV files.
 * @param input The string with potential leading and trailing quotes.
 * @return A string with leading and trailing quotes removed.
 */
std::string trimQuotes(const std::string &input) {
    std::string result = input;
    // Remove leading quotes
    if (!result.empty() && result.front() == '"') {
        result.erase(0, 1);
    }
    // Remove trailing quotes
    if (!result.empty() && result.back() == '"') {
        result.pop_back();
    }
    return result;
}

/**
 * Constructor that initializes a new empty Binary Search Tree.
 */
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

/**
 * Loads bids from a specified CSV file and inserts them into the binary search tree.
 * This method opens the CSV file using the csv::Parser, reads each row to create Bid objects,
 * and then inserts these objects into the tree. It also prints out the header of the CSV file
 * and logs each inserted bid for visibility.
 *
 * @param csvPath The path to the CSV file containing bid data.
 */
void BinarySearchTree::loadBids(const string &csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    auto const file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> const header = file.getHeader();
    for (auto const &c: header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {
            // Create a bid structure and add to the collection of bids
            Bid bid;
            bid.title = file[i][0];
            bid.bidId = file[i][1];
            bid.department = file[i][2];
            bid.closeDate = file[i][3];
            bid.winningBid = file[i][4];
            bid.inventoryId = file[i][5];
            bid.vehicleId = file[i][6];
            bid.receiptNumber = file[i][7];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], ',', '"');
            std::cout << "Inserting bid: " << bid.title << std::endl;
            // push this bid to the end
            this->insert(bid);
        }
    } catch (csv::Error &e)  {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Recursively displays all bids in the tree by performing an in-order traversal.
 * @param node The current node in the traversal (starts with the root).
 */
void BinarySearchTree::displayAllBids(Node* node) {
    if (node == nullptr) {
        return;
    }
    displayAllBids(node->leftChild);
    std::cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << std::endl;
    displayAllBids(node->rightChild);
}

/**
 * Finds the node with the minimum value in the tree.
 * Used primarily in the remove operation to find a new child for a deleted node.
 * @param node The node from which to start the search.
 * @return Node* pointing to the node with the smallest value from the given node.
 */
BinarySearchTree::Node* BinarySearchTree::findMinNode(Node* node) {
    Node* current = node;
    /* loop down to find the leftmost leaf */
    while (current && current->leftChild != nullptr) {
        current = current->leftChild;
    }
    return current;
}

/**
 * Removes a bid from the tree by bidId.
 * @param bidId The ID of the bid to remove.
 */
void BinarySearchTree::removeBid(const string& bidId) {
    this->root = removeNode(root, bidId);
}

/**
 * Searches for a node by bidId.
 * @param node The node to start the search from (typically the root).
 * @param bidId The ID of the bid to find.
 * @return Node* pointing to the found node or nullptr if not found.
 */
BinarySearchTree::Node* BinarySearchTree::searchNode(Node* node, const string& bidId) {
    // Start the traversal from the given node
    Node* currentNode = node;
    // Traverse the tree until the end is reached or the bidId is found
    while (currentNode != nullptr) {
        if (bidId == currentNode->bid.bidId) {
            // The bidId is found, return the current node
            return currentNode;
        }

        if (bidId < currentNode->bid.bidId) {
            // Navigate left if the search bidId is less than the current node's bidId
            return searchNode(currentNode->leftChild, bidId);
        }

        // Navigate right if the search bidId is greater than the current node's bidId
        return searchNode(currentNode->rightChild, bidId);
    }

    // If the loop exits, the bidId was not found in the tree
    return nullptr;
}

/**
 * Public search that initiates a recursive node search from the root.
 * @param bidId The bid ID to search for.
 * @return The found Bid object; if not found, returns an empty Bid with "Not Found" as ID.
 */
BinarySearchTree::Bid BinarySearchTree::search(const string &bidId) const {
    Node* resultNode = searchNode(this->root, bidId);

    // Handle the case where the bid is not found
    if (resultNode != nullptr ) {
        return resultNode->bid;
    }

    Bid notFoundBid;
    notFoundBid.bidId = "Not Found";
    return notFoundBid;
}

/**
 * Displays a single bid's details.
 * @param bid The bid to display.
 */
void BinarySearchTree::displayBid(const Bid& bid) {
    cout << "Bid ID: " << bid.bidId << endl;
    cout << "Title: " << bid.title << endl;
    cout << "Department: " << bid.department << endl;
    cout << "Fund: " << bid.fund << endl;
    cout << "Close Date: " << bid.closeDate << endl;
    cout << "Winning Bid: " << bid.winningBid << endl;
    cout << "Inventory ID: " << bid.inventoryId << endl;
    cout << "Vehicle ID: " << bid.vehicleId << endl;
    cout << "Receipt Number: " << bid.receiptNumber << endl;
    cout << "Amount: $" << bid.amount << endl;
}

/**
 * Converts a string representation of a monetary value to a double, removing unwanted characters.
 * @param str The string to convert.
 * @param arg1 Character to remove, e.g., commas.
 * @param arg2 Additional character to remove or transform, e.g., quotes.
 * @return The numeric value as a double.
 */
double BinarySearchTree::strToDouble(const std::string &str, const char &arg1, const char &arg2) {
    // Remove everything before the dollar sign
    size_t dollarPos = str.find('$');
    if (dollarPos == std::string::npos) {
        // No dollar sign found, treat as invalid
        throw std::invalid_argument("strToDouble: missing dollar sign");
    }

    std::string doubleStr = str.substr(dollarPos + 1);

    // Remove commas and leading/trailing spaces
    doubleStr.erase(std::remove(doubleStr.begin(), doubleStr.end(), arg1), doubleStr.end());
    doubleStr.erase(std::remove(doubleStr.begin(), doubleStr.end(), arg2), doubleStr.end());
    // Remove leading spaces
    doubleStr.erase(doubleStr.begin(), std::find_if(doubleStr.begin(), doubleStr.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    // Remove trailing spaces
    doubleStr.erase(
        std::find_if(
            doubleStr.rbegin(),
            doubleStr.rend(),
            [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(),
            doubleStr.end());
    doubleStr = trimQuotes(doubleStr);

    // Convert the string to a double
    double value;
    std::stringstream ss(doubleStr);
    if (!(ss >> value)) {
        // Conversion failed, treat as invalid
        throw std::invalid_argument("strToDouble: invalid price format");
    }
    return value;
}

/**
 * Inserts a new bid into the tree, maintaining AVL balance.
 * @param bid The bid to insert.
 */
void BinarySearchTree::insert(Bid &bid) {
    if (this->root == nullptr) {
        this->root = new Node  (bid);
    } else {
        addNode(this->root, bid);
    }
}

/**
 * Calculates the height of a node, used in AVL balancing.
 * @param N The node for which to calculate the height.
 * @return The height of the node.
 */
int BinarySearchTree::height(Node *N) {
    if (N == nullptr) return 0;
    return N->height;
}

/**
 * Calculates the balance factor of a node, used in AVL balancing.
 * @param N The node for which to calculate the balance factor.
 * @return The balance factor of the node.
 */
int getBalance(BinarySearchTree::Node *N) {
    if (N == nullptr) return 0;
    return BinarySearchTree::height(N->leftChild) - BinarySearchTree::height(N->rightChild);
}

/**
 * Updates the height of a node based on the heights of its children.
 * @param N The node for which to update the height.
 */
void updateHeight(BinarySearchTree::Node *N) {
    if (N != nullptr) {
        N->height = 1 + std::max(BinarySearchTree::height(N->leftChild), BinarySearchTree::height(N->rightChild));
    }
}

/**
 * Performs a right rotation on a node, used in AVL balancing.
 * @param y The node to rotate.
 * @return The new parent node after rotation.
 */
BinarySearchTree::Node* rightRotate(BinarySearchTree::Node *y) {
    BinarySearchTree::Node *x = y->leftChild;
    BinarySearchTree::Node *T2 = x->rightChild;
    x->rightChild = y;
    y->leftChild = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

/**
 * Performs a left rotation on a node, used in AVL balancing.
 * @param x The node to rotate.
 * @return The new parent node after rotation.
 */
BinarySearchTree::Node* leftRotate(BinarySearchTree::Node *x) {
    BinarySearchTree::Node *y = x->rightChild;
    BinarySearchTree::Node *T2 = y->leftChild;
    y->leftChild = x;
    x->rightChild = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

/**
 * Recursively adds a new node to the tree, maintaining AVL balance.
 * @param node The current node in the recursive call.
 * @param bid The bid to add to the tree.
 * @return The node that has been added or the unchanged node if no addition occurred.
 */
BinarySearchTree::Node* BinarySearchTree::addNode(Node* &node, const Bid &bid) {
    if (node == nullptr) return new Node(bid);

    if (bid.amount < node->bid.amount) {
        node->leftChild = addNode(node->leftChild, bid);
    } else if (bid.amount > node->bid.amount) {
        node->rightChild = addNode(node->rightChild, bid);
    } else {
        return node;
    }

    // Update height of this node
    updateHeight(node);

    // Get the balance factor
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && bid.amount < node->leftChild->bid.amount) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && bid.amount > node->rightChild->bid.amount) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && bid.amount > node->leftChild->bid.amount) {
        node->leftChild = leftRotate(node->leftChild);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && bid.amount < node->rightChild->bid.amount) {
        node->rightChild = rightRotate(node->rightChild);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

/**
 * Recursively removes a node from the tree by bidId, maintaining AVL balance.
 * @param node The current node in the recursive call.
 * @param bidId The ID of the bid to remove.
 * @return The new node replacing the removed node or nullptr if the node was a leaf.
 */
BinarySearchTree::Node* BinarySearchTree::removeNode(Node* node, const string &bidId) {
    if (node == nullptr) return nullptr; // Base case

    // Navigate the tree
    if (bidId < node->bid.bidId) {
        node->leftChild = removeNode(node->leftChild, bidId);
    } else if (bidId > node->bid.bidId) {
        node->rightChild = removeNode(node->rightChild, bidId);
    } else {
        // Node with only one child or no child
        if (node->leftChild == nullptr) {
            Node  * temp = node->rightChild;
            delete node;
            return temp;
        }

        if (node->rightChild == nullptr) {
            Node  * temp = node->leftChild;
            delete node;
            return temp;
        }

        // Node with two children: Get the smallest in the right subtree
        Node  *temp = findMinNode(node->rightChild);

        // Copy the smallest's content to this node
        node->bid = temp->bid;

        node->rightChild = removeNode(node->rightChild, temp->bid.bidId);
    }
    return node;
}
