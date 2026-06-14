#include <iostream>
#include <queue>
#include <algorithm> // for max()
using namespace std;

// ====================
// Node Structure
// ====================
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// ====================
// BST Class
// ====================
class BST {
private:
    Node* root;

    // 1. Recursive Insert helper
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }

        return node;
    }

    // 2. Recursive Search helper
    bool search(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }

        if (value == node->data) {
            return true;
        }

        if (value < node->data) {
            return search(node->left, value);
        }
        else {
            return search(node->right, value);
        }
    }

    // 3. Recursive Remove helper
    Node* remove(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->data) {
            node->left = remove(node->left, value);
        }
        else if (value > node->data) {
            node->right = remove(node->right, value);
        }
        else {
            // Case 1: Leaf node
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: One child (right)
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            // Case 3: One child (left)
            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 4: Two children
            Node* minNode = node->right;
            while (minNode->left != nullptr) {
                minNode = minNode->left;
            }

            node->data = minNode->data;
            node->right = remove(node->right, minNode->data);
        }

        return node;
    }

    // Traversal helpers
    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    void preOrder(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void postOrder(Node* node) {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

    void levelOrder(Node* node) {
        if (node == nullptr) return;
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";
            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }

    Node* findMin(Node* node) {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) node = node->left;
        return node;
    }

    Node* findMax(Node* node) {
        if (node == nullptr) return nullptr;
        while (node->right != nullptr) node = node->right;
        return node;
    }

    int height(Node* node) {
        if (node == nullptr) return -1;
        return 1 + max(height(node->left), height(node->right));
    }

    int countNodes(Node* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

public:
    BST() { root = nullptr; }

    void insert(int value) {
        root = insert(root, value);
        cout << "Inserted: " << value << endl;
    }

    bool search(int value) {
        return search(root, value);
    }

    void remove(int value) {
        root = remove(root, value);
        cout << "Removed: " << value << endl;
    }

    void printInOrder() {
        cout << "In-Order: ";
        inOrder(root);
        cout << endl;
    }

    void printPreOrder() {
        cout << "Pre-Order: ";
        preOrder(root);
        cout << endl;
    }

    void printPostOrder() {
        cout << "Post-Order: ";
        postOrder(root);
        cout << endl;
    }

    void printLevelOrder() {
        cout << "Level-Order: ";
        levelOrder(root);
        cout << endl;
    }

    void printTreeInfo() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }

        cout << "\n===== Tree Information =====" << endl;
        cout << "Minimum value: " << findMin(root)->data << endl;
        cout << "Maximum value: " << findMax(root)->data << endl;
        cout << "Tree height: " << height(root) << endl;
        cout << "Total nodes: " << countNodes(root) << endl;
        cout << "============================" << endl;
    }
};

// ====================
// Main Program
// ====================
//int main() {
//    BST tree;
//
//    cout << "=== Binary Search Tree Operations ===" << endl << endl;
//
//    cout << "--- Insertion ---" << endl;
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//    tree.insert(10);
//    tree.insert(25);
//
//    cout << endl;
//
//    cout << "--- Traversals ---" << endl;
//    tree.printInOrder();
//    tree.printPreOrder();
//    tree.printPostOrder();
//    tree.printLevelOrder();
//
//    tree.printTreeInfo();
//
//    cout << "--- Search ---" << endl;
//    int searchVal = 40;
//    if (tree.search(searchVal)) {
//        cout << "Found: " << searchVal << endl;
//    }
//    else {
//        cout << "Not Found: " << searchVal << endl;
//    }
//
//    cout << endl;
//
//    cout << "--- Deletion ---" << endl;
//    tree.remove(20);    // Leaf
//    tree.remove(30);    // One child
//    tree.remove(50);    // Root (two children)
//
//    cout << endl;
//
//    cout << "--- After Deletion ---" << endl;
//    tree.printInOrder();
//    tree.printTreeInfo();
//
//    return 0;
//}
/*========================================================================*/
//#include <iostream>
//using namespace std;
//
//class BSTNode {
//public:
//    int data;
//    BSTNode* left, * right;
//    BSTNode() : data(0), left(nullptr), right(nullptr) {}
//    BSTNode(int d, BSTNode* l = nullptr, BSTNode* r = nullptr) {
//        this->data = d;
//        left = l;
//        right = r;
//    }
//};
//
//class BST {
//public:
//    BSTNode* root;
//    BST() : root(nullptr) {}
//
//    // 1) Insertion
//    BSTNode* insert(BSTNode* key, int item) {
//        if (key == nullptr) {
//            return new BSTNode(item);
//        }
//        if (item < key->data)
//            key->left = insert(key->left, item);
//        else
//            key->right = insert(key->right, item);
//
//        return key;
//    }
//
//    void insert(int data) {
//        root = insert(root, data);
//    }
//
//    // 2) Size (تم إصلاح الخطأ هنا بإضافة return 0)
//    int size(BSTNode* r) {
//        if (r == nullptr)
//            return 0;
//        return size(r->left) + 1 + size(r->right);
//    }
//
//    // 3) Traversal
//    void Preorder(BSTNode* r) {
//        if (r == nullptr) return;
//        cout << r->data << "\t";
//        Preorder(r->left);
//        Preorder(r->right);
//    }
//
//    void Inorder(BSTNode* r) {
//        if (r == nullptr) return;
//        Inorder(r->left);
//        cout << r->data << "\t";
//        Inorder(r->right);
//    }
//
//    void Postorder(BSTNode* r) {
//        if (r == nullptr) return;
//        Postorder(r->left);
//        Postorder(r->right);
//        cout << r->data << "\t";
//    }
//
//    // 4) Search
//    BSTNode* Search(BSTNode* r, int key) {
//        if (r == nullptr) return nullptr;
//        if (r->data == key) return r;
//        if (key < r->data) return Search(r->left, key);
//        return Search(r->right, key);
//    }
//
//    // 5) Find Min/Max
//    BSTNode* findmin(BSTNode* r) {
//        if (r == nullptr) return nullptr;
//        if (r->left == nullptr) return r;
//        return findmin(r->left);
//    }
//
//    BSTNode* findmax(BSTNode* r) {
//        if (r == nullptr) return nullptr;
//        if (r->right == nullptr) return r;
//        return findmax(r->right);
//    }
//
//    // 6) Delete (تم تحسين المنطق هنا ليكون أكثر أماناً)
//    BSTNode* Delete(BSTNode* r, int key) {
//        if (r == nullptr) return nullptr;
//
//        if (key < r->data)
//            r->left = Delete(r->left, key);
//        else if (key > r->data)
//            r->right = Delete(r->right, key);
//        else {
//            // الحالة 1: عقدة ورقية (Leaf)
//            if (r->left == nullptr && r->right == nullptr) {
//                delete r;
//                return nullptr;
//            }
//            // الحالة 2: عقدة لها ابن واحد
//            else if (r->left == nullptr) {
//                BSTNode* temp = r->right;
//                delete r;
//                return temp;
//            }
//            else if (r->right == nullptr) {
//                BSTNode* temp = r->left;
//                delete r;
//                return temp;
//            }
//            // الحالة 3: عقدة لها ابنان
//            else {
//                BSTNode* maxNode = findmax(r->left); // نأخذ أكبر قيمة من اليسار
//                r->data = maxNode->data;
//                r->left = Delete(r->left, maxNode->data);
//            }
//        }
//        return r;
//    }
//
//    void clear(BSTNode* node) {
//        if (node == nullptr) return;
//        clear(node->left);
//        clear(node->right);
//        delete node;
//    }
//
//    void clear() {
//        clear(root);
//        root = nullptr;
//    }
//};
//
//int main() {
//    BST b1;
//    b1.insert(45);
//    b1.insert(15);
//    b1.insert(75);
//    b1.insert(90);
//    b1.insert(10);
//    b1.insert(55);
//    b1.insert(12);
//    b1.insert(20);
//    b1.insert(50);
//
//    cout << "Tree Size: " << b1.size(b1.root) << endl;
//
//    cout << "Inorder Display:" << endl;
//    b1.Inorder(b1.root);
//    cout << endl;
//
//    cout << "\nDeleting 45 (Root)..." << endl;
//    b1.root = b1.Delete(b1.root, 45);
//
//    cout << "Inorder After Deletion:" << endl;
//    b1.Inorder(b1.root);
//    cout << endl;
//
//    return 0;
//}