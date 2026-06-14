#include <iostream>
using namespace std;
#include<queue>
//****************** Node ***********************
struct Node {
	int data;
	Node* left;
	Node* right;
	Node(int val) {
		data = val;
		left = right = nullptr;
	}
};
//****************** Binary Search Tree ***********************
class BTS {
private:
	Node* root;
public:
	BTS() {
		root = nullptr;
	}
	//insertion new node
	void insert(const int& key) {
		//1
		if (root == nullptr) {
			root = new Node(key);
			return;
		}
		//2
		Node* current = root;
		Node* parent = nullptr;
		//search the Pos of new node
		while (current != nullptr) {

			if (key == current->data) {
				cout << "Value " << key << "already exists!\n";
				return;// no duplicates
			}
			//
			if (key < current->data) {
				parent = current;
				current = current->left;// move from root to the left

			}
			else//key > current->data
			{
				parent = current;
				current = current->right;

			}
		}///in the end of loop, parent -> the parent of new node , current -> null"the place of new node"
		if (parent->data > key) {
			parent->left = new Node(key);// the newnode be the left child of parent
		}
		else//parent->data > key
			parent->right = new Node(key);// the newnode be the right child of parent

	}
	//searching
	Node* search(const int& key)const {
		Node* ptr = root;
		while (ptr != nullptr) {
			if (ptr->data == key)
				return ptr;//found
			else if (ptr->data > key)
				ptr = ptr->left;
			else //ptr->data < key
				ptr = ptr->right;
		}
		return nullptr;
	}
	//Deletion
	void deleteByCopying(Node*& node) {
		Node* prev;
		Node* tmp = node;
		if (node->right == nullptr) {//node no has right child
			node = node->left;
		}
		else if (node->left == nullptr) {//node no has left child
			node = node->right;
		}
		else {

			tmp = node->left;
			prev = node;
			while (tmp->right != nullptr) {//Predecessor max value in left sub tree
				prev = tmp;
				tmp = tmp->right;
			}
			node->data = tmp->data;
			if (prev == node) {
				prev->left = tmp->left;
			}
			else {
				prev->right = tmp->left;
			}

		}
		delete tmp;
	}
	void deletenode(int key) {
		Node* current = root;
		Node* parent = nullptr;
		while (current != nullptr && current->data != key) {
			parent = current;
			if (key < current->data)
				current = current->left;
			else {
				current = current->right;
			}
		}

		if (current == nullptr) {
			cout << "Value not found!\n";
			return;
		}
		if (current == root)
			deleteByCopying(root);
		else if (parent->left == current)
			deleteByCopying(current->left);
		else
			deleteByCopying(current->right);
		cout << "Done\n";
	}
	//Breadth-First Traversal
	void breadthFirst() {
		// create empty queue
		queue<Node*> q;
		//1-tht Tree is empty
		if (root == nullptr) {
			cout << "الشجرة فارغة!" << endl;
			return;
		}
		// أضف الجذر للطابور
		q.push(root);
		cout << "BFS (Level-Order): ";
		// exits elements
		while (!q.empty()) {
			//
			Node* current = q.front();
			q.pop();

			//  (visit operation)
			cout << current->data << " ";

			// add left child
			if (current->left != nullptr) {
				q.push(current->left);
			}
			//add right child
			if (current->right != nullptr) {
				q.push(current->right);
			}
		}

		cout << endl;
	}
	// Traversal helpers
	void inOrder(Node* node) {
		//left root right
		if (node == nullptr) return;
		inOrder(node->left);
		cout << node->data << " ";
		inOrder(node->right);
	}

	void preOrder(Node* node) {
		//root left right
		if (node == nullptr) return;
		cout << node->data << " ";
		preOrder(node->left);
		preOrder(node->right);
	}

	void postOrder(Node* node) {
		//left right root
		if (node == nullptr) return;
		postOrder(node->left);
		postOrder(node->right);
		cout << node->data << " ";
	}





	void breadthFirstDetailed() {
		if (root == nullptr) {
			cout << "Empty" << endl;
			return;
		}

		queue<Node*> q;
		q.push(root);

		int step = 0;
		cout << "\n=== BFS detail ===" << endl;
		cout << "step " << step << ": Queue = [" << root->data << "]" << endl;

		while (!q.empty()) {
			step++;

			// اطلع أول عقدة
			Node* current = q.front();
			q.pop();

			// اطبع العقدة
			cout << "\nstep " << step << ":" << endl;
			cout << " enqueue " << current->data << endl;

			// أضف الأطفال
			if (current->left != nullptr) {
				cout << "  add left child " << current->left->data << endl;
				q.push(current->left);
			}

			if (current->right != nullptr) {
				cout << "  add right child " << current->right->data << endl;
				q.push(current->right);
			}

			// اطبع حالة الطابور
			cout << "  Queue : [";
			queue<Node*> temp = q;
			bool first = true;
			while (!temp.empty()) {
				if (!first) cout << ", ";
				cout << temp.front()->data;
				temp.pop();
				first = false;
			}
			cout << "]" << endl;
		}

		cout << "\nend" << endl;
	}
	// للوصول للـ root من الخارج
	Node* getRoot() {
		return root;
	}
};
int main() {
	BTS tree;
	//
	tree.insert(1);
	tree.insert(5);
	tree.insert(15);
	//
	Node* result = tree.search(7);
	if (result != nullptr) {
		cout << "Found: " << result->data << endl;
	}
	else {
		cout << "Not found!" << endl;
	}
	//
	tree.deletenode(100);
	tree.deletenode(5);
	//
	BTS tree1;

	cout << "=== Breadth-First Traversal (BFS) ===" << endl;
	// إنشاء الشجرة من المثال
	tree1.insert(13);
	tree1.insert(10);
	tree1.insert(25);
	tree1.insert(2);
	tree1.insert(12);
	tree1.insert(20);
	tree1.insert(31);
	tree1.insert(29);

	// BFS البسيطة
	cout << " (BFS): ";
	tree1.breadthFirst();

	// BFS المفصلة مع الشرح
	tree1.breadthFirstDetailed();


	return 0;
}