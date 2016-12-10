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
	template <typename T2>
	friend ostream& operator<<(ostream&, const BinarySearchTree<T2>&); //ostream operator that prints the status of the tree
	private:
		struct Node {
			TBA data; //data stored in the node. To Be Announced type
			Node* left; //a pointer to the left of this node (smaller data)
			Node* right; //a pointer to the right of this node (larger data)
			Node(TBA d, Node* l, Node* r) : data(d), left(l), right(r) {}
	};
	Node* root; //a pointer to the root node. Where the tree begins
	Node* insert(TBA, Node*); //the real insert function, which takes in the TBA object we are trying to insert and then a pointer to the beginning of the tree
	bool retrieve(TBA&, TBA*&, Node*);
	void clear(Node*);
	string display(Node*) const;
public:
	BinarySearchTree();
	~BinarySearchTree();
	bool isEmpty() const; //returns true if the list is empty, false otherwise
	bool insert(TBA); //inserts a TBA object into the tree (facade)
	bool retrieve(TBA&, TBA*&); //retrieves a TBA item from the list and stores it in the TBA ref we passed in
	void clear(); //kills the tree
	void display() const; //displays the contents of the tree
};
#endif
//-----------------------------------Binary Search Tree-----------------------------------
//Precondition: Need to construct a binary search tree
//Postcondition: Binary tree constructed
/*
BinarySearchTree: This is the defualt constructor for a binary tree. All we do here is 
set the root to NULL. Nothing else needs to be initialized.
*/
template<class TBA>
BinarySearchTree<TBA>::BinarySearchTree() {
	root = NULL; //set root to null
}
//-----------------------------------~Binary Search Tree-----------------------------------
//Precondition: Need to destruct a binary tree
//Postcondition: All the dynamic memory in a binary tree is deleted
/*
~BinarySearchTree: This is the destructor for the binarysearchtree. It calls the clear method
to delete all of the nodes in the tree, which are dynamically allocated. 
*/
template<class TBA>
BinarySearchTree<TBA>::~BinarySearchTree() {
	clear(); //call clear
}
//-----------------------------------Insert (Facade)-----------------------------------
//Precondition: Need to insert an item into the tree
//Postcondition: Item inserted into the tree
/*
Insert: This is a method that a user can call to insert an item in to the tree. It calls
the other implementation of insert, hands it the data the user wanted to insert as well
as the root of the tree. Then it returns the status of the mission.
*/
template<class TBA>
bool BinarySearchTree<TBA>::insert(TBA in) {
	root = insert(in, root);
	return true;
}
//-----------------------------------Insert-----------------------------------
//Precondition: Need to insert an item into the list
//Postcondition: Item inserted into the list
/*
Insert: The goal of this function is to insert an item into its correctly sorted
place in the tree. First it checks to see if the current node(which starts at root)
if NULL, if it is we have found the stop in the tree where we need to insert
so we will make a new node here and pass it the data we wanted to insert, as well as
NULL for the left and right pointers in the node. If we have not found the NULL node
we will check to see if the data we are trying to insert is less than the data of the
current node we are looking at. If so we will set the left pointer of the current node
to whatever is returned by recalling this method with the node that is stored in the left
pointer of the current node. Otherwise we will set the right pointer of the current node
equal to whatever is returned by recalling this fucntion with whatever is present in the
right pointer in the current node. Then we return the node we are working on, which should 
bubble up to the root node.
*/
template<class TBA>
typename BinarySearchTree<TBA>::Node* BinarySearchTree<TBA>::insert(TBA in, Node* subtree) {
	if (subtree == NULL) subtree = new Node(in, NULL, NULL); //check to see if we have found a null node, and if we have make a new node here
	else if (in < subtree->data) subtree->left = insert(in, subtree->left); //if the data in the subtree is greater than what we are trying to insert, set the left pointer of the current node to this function recalled with the subtree to the left
	else subtree->right = insert(in, subtree->right); //otherwise the data is greater than the current data in the subtree so we will set the right pointer of the current node equal to this function recalled with the right pointer of this node
	return subtree; //return the subtreee
}
//-----------------------------------Is Empty-----------------------------------
//Precondition: Need to check if the tree is empty
//Postcondition: Bool returned that shows if the tree is empty
/*
Is Empty: The goal of this function is to check if the list is empty. It does this
by checking to see if the root pointer is NULL.
*/
template<class TBA>
bool BinarySearchTree<TBA>::isEmpty() const {
	return root == NULL; //check to see if the root pointer is NULL
}
//-----------------------------------Retrieve (Facade)-----------------------------------
//Precondition: Need to find and gain access to an element in the list
//Postcondition: toStore returned empty if it didnt find the element, or containing the element if it was found
/*
Retrieve: This is the facade for the retrieve function. it takes in a reference to a TBA object and a reference
to a pointer of a TBA object. It calls the retrieve function and hands it its two parameters as well as the root
*/
template<class TBA>
bool BinarySearchTree<TBA>::retrieve(TBA& toFind, TBA*& toStore) {
	return retrieve(toFind, toStore, root); //call the other retrieve function and hand it your two parameters plus root
}
//-----------------------------------Retrieve-----------------------------------
//Precondition: Need to find and gaiin access to an element in the list
//Postcondition: toStore returned empty if it didnt find the element, or containing the element if it was found
/*
Retrieve: the goal of this function is to find an element in the list and grant access to that element
through the second parameter. First we check to see if we have hit NULL. If we have we didnt find the element so
we will return false. Next we check to see if the current nodes data is what we are looking for, if so then we
set tostore equal to a reference to the subtrees data, and returns true. otherwise we check to see if the data in
the node is greater than the data we are looking for, if so then we recall this function with the node to the left
of the current subtree. Otherwise we go right.
*/
template<class TBA>
bool BinarySearchTree<TBA>::retrieve(TBA& toFind, TBA*& toStore, Node* subtree) {
	if (subtree == NULL) return false; //check to see if we have found the end of the tree
	if (subtree->data == toFind) { //check to see if we have found the element we are looking for
		toStore = &(subtree->data); //set toStore equal to a reference of the subtrees data
		return true; //return true
	}
	else if (subtree->data > toFind) return retrieve(toFind, toStore, subtree->left); //if the current data is too big, call this function again with the left node
	else return retrieve(toFind, toStore, subtree->right); //otherwise call this function again with the right pointer
}
//-----------------------------------Clear (Facade)-----------------------------------
//Precondition: Need to delete all the nodes in the list 
//Postcondition: All nodes in the list deleted
/*
Clear: This is the facade function for the clear method. It calls the other clear method
and hands it the root.
*/
template<class TBA>
void BinarySearchTree<TBA>::clear() {
	clear(root); //call the other clear method and hand it root
}
//-----------------------------------Clear-----------------------------------
//Precondition: Need to delete all the nodes in the list
//Postcondition: All the nodes in teh list deleted
/*
Clear: The goal of this function is to go through the tree and delete every node. There
is an if statement that checks to see if we have reached null. If we havent reached null
we call this function again for both the left and the right subtree, and then delete the 
current subtree.
*/
template<class TBA>
void BinarySearchTree<TBA>::clear(Node* subtree) {
	if (subtree != NULL) { //check to see if we have hit NULL
		clear(subtree->left); //call this method to the left
		clear(subtree->right); //call this method to the right
		delete subtree; //delete the current subtree
	}
}
//-----------------------------------Display (Facade)-----------------------------------
//Precondition: Need to display the contents of the tree
//Postcondition: Contents of the tree displayed
/*
Display: The goal of this function is to be the function the user can call to display the 
contents of the tree. It couts the other display function, ehich is handed root.
*/
template<class TBA>
void BinarySearchTree<TBA>::display() const {
	cout << display(root) << endl;
}
//-----------------------------------Display-----------------------------------
//Precondition: Need to display the contents of the tree
//Postcondition: Contents of the tree displayed
/*
Diplay: The goal of this function is to display the contents of the tree. It first
initialized a string stream that we will use to display the contents. Then it checks
to see if the current subtree is null, and if its not, then it calls the function again
for both the left and right subtree and adds the data of the current subtree into the
string stream, then it returns the string representation of the string stream.
*/
template<class TBA>
string BinarySearchTree<TBA>::display(Node* subtree) const{
	stringstream ss; //initialize a string stram
	if (subtree != NULL) { //keep going while the subtree isnt NULL
		ss << display(subtree->left); //call this function again with the subtree to the left
		ss << subtree->data; //add the data of the current subtree to the string stream 
		ss << display(subtree->right); //call this function again with the subtree to the right
	}
	return ss.str(); //return the string of the string stream
}
//-----------------------------------Operator<<-----------------------------------
//Precondition: Need to output contents of the tree
//Postcondition: Outputs the contents of the tree
/*
Operator<<: The goal of this method is to output the contents of the tree. It does this
by caliing the display method and passing that to an output stream, and returning the output stream
*/
template<typename T2>
ostream& operator<<(ostream& out, const BinarySearchTree<T2>& target) {
	out << target.display(target.root) << endl; //call the display function and give it to the output stream
	return out; //return the output stream
}