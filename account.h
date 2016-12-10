/*
Monroe Shindelar and JJ Abides
Professor Rob Nash
CSS 342: Data Structures, Algorithms, and Discrete Math
November 23, 2016
Transaction Processing: Account class

This class is meant to represent an account for anyone banking
with the lose firm. It has a private array that is of size 10
to represent the 10 different types of accounts that every lose
account has. Ther is also an array that keeps track of the initial
balance that they account had before funds were added and withdrawn.
The account has a constructor, which takes in an int pointer to initialize
both of the classes arrays, and a destructor. There are two
functions inside the account class, one that takes in an account number
and an amount and adds that amount to the account, and another which
also takes in an account number and an amount and subtracts that amount
from that specific account.

*/
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
using namespace std;

class Account {
	friend ostream& operator<<(ostream&, const Account&); //friend class operator<<(), used for creating an output text for cout
private:
	int loseAccount[10]; //This is the array to keep track of the current account balance in all ten lose accounts
	int initialBalance[10]; //This is the array to keep track of the inital balance in all ten of the lose accounts
public:
	Account();
	Account(int*); //constructor for an account. Takes in an int array that will initialize the inital balance account as well as the current lose account.
	~Account(); //Destructor for accounts
	bool addToAccount(int acc, int amount); //Takes in an account (index of the array) and an amount and adds that amount to that account
	bool subtractFromAccount(int acc, int amount); //Takes in an account (index of the array) and an amount and subracts that amount from that account
};
#endif