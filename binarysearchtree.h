/*
Monroe Shindelar and JJ Abides
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

#include <string>
#include <stdio.h>
#include <iostream>

template <class TBA>
class BinarySearchTree {
    friend operator<<(ostream&, const BinarySearchTree&);
    private:
        struct Node {
            TBA data; //data stored in the node. To Be Announced type
            Node* left; //a pointer to the left of this node (smaller data)
            Node* right; //a pointer to the right of this node (larger data)
        };
        Node* root; //a pointer to the root node. Where the tree begins
        void insert(TBA, Node*); //the real insert function, which takes in the TBA object we are trying to insert and then a pointer to the beginning of the tree
        void retrieve(TBA, TBA&, Node*); //the real retrieve function, which takes in a TBA that we are supposed to look for an a TBA ref that we are going to store the data in, as well as a pointer to the start of the tree
    public:
        bool isEmpty() const; //returns true if the list is empty, false otherwise
        bool insert(TBA); //inserts a TBA object into the tree (facade)
        bool retrieve(TBA, TBA&); //retrieves a TBA item from the list and stores it in the TBA ref we passed in 
        void clear(); //kills the tree
        void display(); //displays the contents of the tree
};
