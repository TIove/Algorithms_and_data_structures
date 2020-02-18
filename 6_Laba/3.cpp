#include <fstream>
#include <memory>
#include <string>

using namespace std;

class BinSearchTree {
private:
    struct Node {
        int key;
        shared_ptr<Node> leftChild;
        shared_ptr<Node> rightChild;
        Node(int key, shared_ptr<Node> leftChild, shared_ptr<Node> rightChild) {
            this->key = key;
            this->leftChild = leftChild;
            this->rightChild = rightChild;
        }
    };

    static shared_ptr<Node> createNode(int key) {
        shared_ptr<Node> newNode = make_shared<Node> (key, nullptr, nullptr);
        return newNode;
    }

    shared_ptr<Node> bin_tree = nullptr;

    static shared_ptr<Node> insertIntoTree(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return createNode(key);
        if (currentNode->key > key)
            currentNode->leftChild = insertIntoTree(currentNode->leftChild, key);
        else if (currentNode->key < key)
            currentNode->rightChild = insertIntoTree(currentNode->rightChild, key);
        return currentNode;
    }

    static bool is_found(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return false;
        if (currentNode->key == key)
            return true;
        if (currentNode->key < key)
            return is_found(currentNode->rightChild, key);
        else
            return is_found(currentNode->leftChild, key);
    }

    static shared_ptr<Node> findNode(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return nullptr;
        if (currentNode->key == key)
            return currentNode;
        if (currentNode->key < key)
            return findNode(currentNode->rightChild, key);
        else
            return findNode(currentNode->leftChild, key);
    }

    static shared_ptr<Node> getNextNode(shared_ptr<Node> currentNode) {
        if (currentNode->rightChild == nullptr)
            return nullptr;
        currentNode = currentNode->rightChild;
        while (currentNode->leftChild != nullptr)
            currentNode = currentNode->leftChild;
        return currentNode;
    }

    static int getNextKey(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return INT32_MAX;
        if (currentNode->key > key && currentNode->leftChild == nullptr)
            return currentNode->key;
        if (currentNode->key > key) {
            int result = getNextKey(currentNode->leftChild, key);
            if (result != INT32_MAX)
                return result;
            return currentNode->key;
        }
        else
            return getNextKey(currentNode->rightChild, key);
    }

    static int getPrevKey(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return INT32_MAX;
        if (currentNode->key < key && currentNode->rightChild == nullptr)
            return currentNode->key;
        if (currentNode->key < key) {
            int result = getPrevKey(currentNode->rightChild, key);
            if (result != INT32_MAX)
                return result;
            return currentNode->key;
        }
        else
            return getPrevKey(currentNode->leftChild, key);
    }

    shared_ptr<Node> findAndDelete(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return nullptr;
        if (currentNode->key == key){
            if (currentNode->leftChild == nullptr && currentNode->rightChild == nullptr) {
                currentNode.reset();
                return nullptr;
            }
            if (currentNode->rightChild == nullptr) {
                shared_ptr<Node> temp = currentNode->leftChild;
                currentNode.reset();
                return temp;
            }
            currentNode->key = getNextNode(currentNode)->key;
            currentNode->rightChild = findAndDelete(currentNode->rightChild, getNextNode(currentNode)->key);
            return currentNode;
        }
        if (currentNode->key > key)
            currentNode->leftChild = findAndDelete(currentNode->leftChild, key);
        else
            currentNode->rightChild = findAndDelete(currentNode->rightChild, key);
        return currentNode;
    }

public:
    void insert(const int key) {
        bin_tree = insertIntoTree(bin_tree, key);
    }

    void remove(const int key) {
        bin_tree = findAndDelete(bin_tree, key);
    }

    bool exists(const int key) {
        return is_found(bin_tree, key);
    }

    int next(const int key) {
        return getNextKey(bin_tree, key);
    }

    int prev(const int key) {
        return getPrevKey(bin_tree, key);
    }

};

int main() {
    ifstream in("bstsimple.in");
    ofstream out("bstsimple.out");
    string cmd;
    int operand;
    BinSearchTree tree;

    while (!in.eof()) {
        cmd = "";
        in >> cmd >> operand;
        if (cmd == "insert")
            tree.insert(operand);
        else if (cmd == "delete")
            tree.remove(operand);
        else if (cmd == "exists") {
            if (tree.exists(operand))
                out << "true" << endl;
            else
                out << "false" << endl;
        }
        else if (cmd == "next") {
            int next = tree.next(operand);
            if (next < 1000000000)
                out << next << endl;
            else
                out << "none" << endl;
        }
        else if (cmd == "prev") {
            int prev = tree.prev(operand);
            if (prev < 1000000000)
                out << prev << endl;
            else
                out << "none" << endl;
        }
    }
    in.close();
    out.close();
}