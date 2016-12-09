/*File: transaction.h
Monroe Shindelar and JJ Abides
Professor Rob Nash
CSS 342: Data Structures, Algorithms, and Discrete Math
November 23, 2016
Transaction Processing: Transaction Class

This class is meant to be a container for data that represents a transaction.
It has a char operator, which represents the function that we will be performing
on the account (withdraw, deposit, move, view), a string ID that represents the
client whos funds we are modifying, a second string, moveToID, that we need in case
we are trying to move funds from one clients account to another, and an amount that
represents the amount of money we will be withdrawing, depositing, moving.
There is a constructor for this class which takes in a mandatory char for the operation
and a string for the client, but also has two other parameters, a string that is defaluted
to an empty string, and an int that it set to 0. These represent the ID of another client,
to use if we are moving from one clients account to another, and amount repectivly, but they
are not mandatory for every type of transaction, so they are defaulted. there are also getters
for every element inside the transaction object so that they may easily be accessed by other
classes.
*/

#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>

using namespace std;

class Transaction {
	friend ostream& operator<<(ostream&, const Transaction&); //operator to output data inside a transaction


private:
	const char op; //char that holds the operation we will perform
	const string ID; //string that holds the ID of the client as well as the clients account we will be modifying (last digit)
	const string moveToID; //string that holds the ID of the clients we are moving funds to
	const int amount; //amount of money we will be adding/subtracting/moving

public:
	Transaction(char, string, string = "", int = 0); //constructor for a transaction object. Every transaction must have an operation in the form of a char and an ID number of the client we are looking at
	~Transaction(); //destructor for the Transaction object
	char getOp() const; //returns the operator that is stored in the transaction object
	string getID() const; //returns the ID that is stored in the transaction object
	string getMoveToID() const; //returns the ID of the account/client we are trying to move funds to
	int getAmount() const; //returns the amount that is stored in the transaction object
};
#endif