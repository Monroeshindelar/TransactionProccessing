/*
Monroe Shindelar, JJ Abides
Professor Rob Nash
CSS 342: Data Structures, Algorithms, and Discrete Math
November 23, 2016
Transaction Processing: BinarySearchTree class

This class is meant to be a container that holds clients of a 
firm, but it is templatized so that it may be used with other 
things. Inside this class, there is another class which is called
Node. Nodes are used to make up the tree, they contain a piece of 
data, as well as a pointer to another node to the right, and a 
pointer to a node on the left. The binary tree has a root node that
is used to start the tree off, as well as hidden functions to make
insert and retrieve a little easier. This class contains a method to
check and see if the tree is empty, a fucntion that inserts a TBA item
into the tree, a function that retrieves a TBA object from the tree by
storing it in a node that we passed to the retrieve function as parameters,
a clear function which completely kills the tree, and a display function
which displays the contents of the tree. 

*/
#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>
using namespace std;

template <class TBA>
class BinarySearchTree {
    //friend operator<<(ostream&, const BinarySearchTree&);
    private:
        struct Node{
            TBA data; //data stored in the node. To Be Announced type
            Node* left; //a pointer to the left of this node (smaller data)
            Node* right; //a pointer to the right of this node (larger data)
            Node(TBA d, Node* l, Node* r) : data(d), left(l), right(r) {}
        };
        Node* root; //a pointer to the root node. Where the tree begins
		Node* insert(TBA, Node*); //the real insert function, which takes in the TBA object we are trying to insert and then a pointer to the beginning of the tree
        void clear(Node*);
        string display(Node*);
    public:
        BinarySearchTree();
        ~BinarySearchTree();
        bool isEmpty() const; //returns true if the list is empty, false otherwise
        bool insert(TBA); //inserts a TBA object into the tree (facade)
        bool retrieve(TBA, TBA&); //retrieves a TBA item from the list and stores it in the TBA ref we passed in 
        void clear(); //kills the tree
        void display(); //displays the contents of the tree
};
#endif

template<class TBA> 
BinarySearchTree<TBA>::BinarySearchTree() {
	root = NULL;
}

template<class TBA>
BinarySearchTree<TBA>::~BinarySearchTree() {
	clear();
}

template<class TBA>
bool BinarySearchTree<TBA>::insert(TBA in) {
	root = insert(in, root);
	return true;
}

template<class TBA>
typename BinarySearchTree<TBA>::Node* BinarySearchTree<TBA>::insert(TBA in, Node* subtree) {
	if (subtree == NULL) subtree = new Node(in, NULL, NULL);
	else if (in < subtree->data) subtree = insert(in, subtree->left);
	else subtree = insert(in, subtree->right);
	return subtree;
}

template<class TBA>
bool BinarySearchTree<TBA>::isEmpty() const {
	return root == NULL;
}

template<class TBA>
bool BinarySearchTree<TBA>::retrieve(TBA toFind, TBA& toStore) {
	Node* subtree = root;
	bool success = false;
	while (subtree != NULL) {
		if (subtree->data < toFind) subtree = subtree->right;
		else if (subtree->data > toFind) subtree = subtree->left;
		else {
			*&toStore = subtree->data;
			success = true;
		}
	}
	return success;
}

template<class TBA>
void BinarySearchTree<TBA>::clear() {
	clear(root);
}

template<class TBA>
void BinarySearchTree<TBA>::clear(Node* subtree) {
	if (subtree != NULL) {
		clear(subtree->left);
		clear(subtree->right);
		delete subtree;
	}
}

template<class TBA>
void BinarySearchTree<TBA>::display() {
	cout << display(root) << endl;
}

template<class TBA>
string BinarySearchTree<TBA>::display(Node* subtree) {
	stringstream ss;
	if (subtree != NULL) {
		ss << display(subtree->left);
		ss << subtree->data;
		ss << display(subtree->right);
	}
	return ss.str();
}




