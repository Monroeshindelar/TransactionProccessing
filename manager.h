/*
Monroe Shindelar, JJ Abides
Professor Rob Nash
CSS 342: Data Structures, Algorithms, and Discrete Math
November 23, 2016
Transaction Processing: Manager Class

This class is used to manage the rest of the classes in the
transaction processing homework and to do all of the high
level operations. It contains a binary search tree that
represents a bank firm, where each node in the tree represents
a different client. This class also contains a queue that holds
transaction objects that are waiting to be processed. This class
also contains functions that are used to buy shares, sell shares,
move shares, and view the transaction history of a client. However,
these are private and they are only to be used by the performTransactions
class. The public methods in this class are generateFirm, which takes in
a text file and makes a client using the data of each line, then it adds
the client to the tree. takeTransaction is a function that takes transaction
commands from a file and then packages them as transaction objects and stores
them in the queue so they they may be processed later. Perform transactions
performs every transaction in the transaction queue. Each transaction that is
performed is then pushed to the stack. undoLastTransaction pops the last element
off the stack and then undoes it. redoLastTransaction is similar to undo, but instead
of reversing the transaction, it does the same transaction again.
*/
#include <string>
#include <stdio.h>
#include <iostream>
#include "client.h"
#include "transaction.h"
#include "binarysearchtree.h"
#include <queue>
#include <stack>
#include <fstream>
#include <ostream>

class Manager {
	friend ostream& operator<<(ostream&, const Manager&); //operator to print the contents of the firm
private:
	BinarySearchTree<Client> firm; //The tree that represents the firm and stores the clients
	queue<Transaction> transactionQueue; //the queue that holds transactions that need to be processed
	stack<Transaction> undo; //the stack that holds completed transactions so they can be redone or undone
	stack<Transaction> redo;
	bool buyShares(string, int, int); //Function allows the manager to deposit funds into a clients account
	bool sellShares(string, int, int); //Function allows the manager to withdraw funds from a clients account
	bool moveShares(string, int, string, int); //Function allows the manager to move funds from one of the clients accounts into another
	bool viewHistory(string); //Function that allows the manager to look at the transaction history of a client       
public:
	Manager(); //Default constructor for a manager object
	~Manager(); //Destructor for a manager object
	bool generateFirm(ifstream&); //Function that populates a binary tree with clients, to represent a firm
	bool takeTransactions(ifstream&); //Function that takes transactions from a file and stores them in a queue to be processed later
	void performTransactions(); //Function that performs all the transactions that are stored in the transaction queue
	bool undoLastTransaction(); //Function that undoes the last performed transaction
	bool redoLastTransaction(); //Function that redoes the last performed  transaction
};