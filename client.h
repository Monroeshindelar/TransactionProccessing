/*
Monroe Shindelar, JJ Abides
Professor Rob Nash
CSS 342: Data Structures, Algorithms, and Discrete Math
November 23, 2016
Transaction Processing: Client class

This class is meant to represent a client of the lose firm.
The client has a last name, a firts name, an ID, an Account,
and an account history. THis class has functions that allow
you to access the last name of the client, the first name of
the client, and the ID of the client. There is no accessor
method for the account of the client to ensure it cannot be
tampered with. This class has a function called addToAccount,
which takes in an int that represents the specific lose sub-
account and an amount and adds that amount to the account, and
it also has a subtractFromAccount method that takes in an int
that represents the specific lose sub-account and an amount and
subtracts that amount from the account. showHistory is used to
display the contents of the clients history stack. The operators <,>, and
== are overriden so that comparisons can be made about clients,
and the operator = is overriden so that you can make better copies
of clients.
*/

#include <string>
#include "account.h"
#include <stack>
#include "transaction.h"
#include <iostream>

using namespace std;


class Client {
	friend ostream& operator<<(ostream&, const Client&); //override the << operator so that data about clients can be output easier
private:
	string last; //represents the last name of the client
	string first; //represents the first name of a client
	string ID; //represents the ID of a client
	Account lose; //represents the account of a client
	stack<Transaction> history; //represents the transaction history of the client
public:
	Client();
	Client(string, string, string, int*); //constructor that takes in a last name, first name, and an int array that represents the account.
	~Client(); //destructor for the client 
	string getLast(); //returns the last name of the client
	string getFirst(); //return the first name of the client 
	string getID(); //returns the ID of the client 
	void showHistory(); //displays the transaction history of the client
	bool addToAccount(int acc, int amount); //takes in an int to represent the account number and another int to represent the amount, and adds the amount to the specified account 
	bool subtractFromAccount(int acc, int amount); //takes in an int to represnt the account number and then an int to represent an amount and then s ubtrats that amount from the specified account
	bool operator<(Client&); //overridden < operator to compare if one client is bigger or smaller than another
	bool operator>(Client&); //overridden > operator to compare if one client is bigger or smaller than another
	bool operator==(Client&); //overridden == operator to compare clients and see if they are equal
	Client& operator=(Client&); //overridden = operator to better make copies of clients 
};