#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include "CSVparser.hpp"

using namespace std;

class BinarySearchTree {
public:
    BinarySearchTree();

    struct Bid {
        string title;
        string bidId; // unique identifier
        string department;
        string fund;
        string closeDate;
        string winningBid;
        string inventoryId;
        string vehicleId;
        string receiptNumber;
        double amount = 0.0;
    };

    struct Node {
        Bid bid{};
        Node *leftChild{};
        Node *rightChild{};

        // To implement AVL balancing, you need the height for child nodes
        int height = 1;

        explicit Node(Bid bid) : bid(std::move(bid)) {
        }
    };

    static int height(Node *);

public:
    Node *root = nullptr;

public:
    void loadBids(const string &csvPath);

    static void displayAllBids(Node *);

    static Node *findMinNode(Node *node);

    void removeBid(const string &bidId);

    static Node *searchNode(Node *, const string &bidId);

    Bid search(const string &bidId) const;

    static void displayBid(const Bid &bid);

    static double strToDouble(const string &str, const char &arg1, const char &arg2);

    static Node *removeNode(Node *node, const string &bidId);

    Node *addNode(Node * &node, const Bid &bid);

    void insert(Bid &bid);

    virtual ~BinarySearchTree() = default;
};

#endif
