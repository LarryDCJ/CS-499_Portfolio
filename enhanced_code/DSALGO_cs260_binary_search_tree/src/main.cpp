#include <cassert>
#include <ctime>
#include <iostream>
#include "BinarySearchTree.h"
#include <cmath>   // For std::abs()

using std::string;
using std::cout;
using std::endl;
using std::vector;

// Assuming height function exists and calculates the height of a node
// If not, implement it based on the structure of your Node class.
int height(BinarySearchTree::Node *node) {
    if (node == nullptr) {
        return 0; // Height of a null tree is 0
    }
    return node->height; // Assuming each node stores its height
}

// Helper function to check AVL balance for each node
bool isAVLBalanced(BinarySearchTree::Node *node) {
    if (node == nullptr) {
        return true; // A null tree is balanced
    }

    int leftHeight = height(node->leftChild);
    int rightHeight = height(node->rightChild);

    // Check if current node is balanced and recurse for children
    return std::abs(leftHeight - rightHeight) <= 1
           && isAVLBalanced(node->leftChild)
           && isAVLBalanced(node->rightChild);
}

void testAVLBalance() {
    // Step 1: Setup
    BinarySearchTree bst;
    std::string testCsvPath = "../testBids.csv"; // Adjust path as needed

    // Step 2: Invoke
    bst.loadBids(testCsvPath);

    // Step 3: Verify AVL Balance
    assert(isAVLBalanced(bst.root) && "The tree is not AVL balanced.");

    std::cout << "AVL balance test passed.\n";
}

void testLoadBids() {
    BinarySearchTree bst;
    std::string testCsvPath = "../testBids.csv"; // Ensure this test CSV exists with known contents
    bst.loadBids(testCsvPath);
    // display all bids to verify contents
    BinarySearchTree::displayAllBids(bst.root);

    // List of known bid IDs from your test CSV
    std::vector<std::string> knownBidIds = {"98077", "97988", "98245", "98319", "98233"};
    std::vector<double> knownBidAmounts = {1.00, 48.00, 3125.60, 530.00, 19.00};
    // Corresponding bid amounts for verification

    for (size_t i = 0; i < knownBidIds.size(); i++) {
        cout << "SEARCHING FOR: " << knownBidIds[i] << endl;

        // Search for each bid ID
        auto searchResult = bst.search(knownBidIds[i]);

        // Verify search result is not "Not Found" and the amount matches
        cout << "LOCATED BID ID: " << searchResult.bidId << endl;
        assert(searchResult.bidId != "Not Found" && "Bid ID should exist in the tree.");
        assert(searchResult.amount == knownBidAmounts[i] && "Bid amount should match the known value.");

        if (searchResult.bidId != "Not Found" && searchResult.amount == knownBidAmounts[i]) {
            std::cout << "Test Passed: Found bid " << knownBidIds[i] << " with correct amount $" << knownBidAmounts[i]
                    << std::endl;
        } else {
            std::cout << "Test Failed: Bid " << knownBidIds[i] << " not found or amount incorrect." << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    testLoadBids();
    testAVLBalance();
    // process command line arguments
    std::string csvPath;
    std::string bidId;
    auto *bst = new BinarySearchTree{};

    // Define a timer variable
    clock_t ticks;

    switch (argc) {
        case 2:
            csvPath = argv[1];
            bidId = "98109";
            break;

        case 3:
            csvPath = argv[1];
            bidId = argv[2];
            break;

        default:
            csvPath = "../Dec2021eBidSales.csv";
            bidId = "98109";
    }

    int choice = 0;

    while (choice != 9) {
        std::cout << "Menu:" << std::endl;
        std::cout << "  1. Load Bids" << std::endl;
        std::cout << "  2. Display All Bids" << std::endl;
        std::cout << "  3. Find Bid" << std::endl;
        std::cout << "  4. Remove Bid" << std::endl;
        std::cout << "  9. Exit" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Initialize a timer variable before loading bids
                ticks = clock();
                bst->loadBids(csvPath);

            // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                std::cout << "time: " << ticks << " clock ticks" << std::endl;
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                break;

            case 2:
                BinarySearchTree::displayAllBids(bst->root); // Call the InOrder function to display all bids
                break;

            case 3:
                std::cout << "Please enter a valid bid ID: " << std::endl;
                std::cin >> bidId;
                ticks = clock();
                ticks = clock() - ticks;

                if (bidId.empty()) {
                    bidId = "98109";
                }

                if (!bst->search(bidId).bidId.empty()) {
                    BinarySearchTree::displayBid(bst->search(bidId));
                } else {
                    std::cout << "Bid Id " << bidId << " not found." << std::endl;
                }
                std::cout << "time: " << ticks << " clock ticks" << std::endl;
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                break;

            case 4:
                bst->removeBid(bidId);
                break;

            default:
                std::cout << "No selection made. Please select 1-4.";
        }
    }
    delete(bst);

    std::cout << "Good bye." << std::endl;

    return 0;
}
