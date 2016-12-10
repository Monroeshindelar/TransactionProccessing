/*
Monroe Shindelar, JJ Abides
Professor Rob Nash
CSS 342: Data Structures, Algorithms, and Discrete Math
December 9, 2016
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
#include "stdafx.h"
#include "client.h"
#include "transaction.h"

/* Default Client constructor: This default Client constructor initializes the last, first and ID
   string variables to empty strings. lose Account object and history are left unassigned.
   Precondition: None
   Postcondition: A Client object has been created with empty data
*/
Client::Client() {
	last = "";			//Initialize to empty string
	first = "";			//Initialize to empty string
	ID = "";			//Initialize to empty string
}

/* Client constructor: This constructor takes in a string for the last name, a string for the first name, and a
   for the 5-digit LOSE account ID. It also takes an integer pointer which is used for passing integer arrays.
   These arguments are then assigned to their respective instance variables.
   Precondition: The arguments are the desired items for assignment
   Postcondition: A Client object has been created with the instance variable assigned to the given arguments
*/
Client::Client(string l, string f, string i, int* la) {
	last = l;					//Assigning l to last
	first = f;					//Assigning f to first
	ID = i;						//Assigning i to ID
	lose = Account(la);			//Assigning lose to an Account with the given int array
}

/* Client Destructor: This destructor does nothing.
   Precondition: A Client object is destructing
   Postcondtion: A Client object has finished destructing
*/
Client::~Client() {
}

/* getLast() getter method: This method is a getter method that returns the last name of the Client
   Precondition: The last name needs to be accessed
   Postcondition: The value of the last name has been returned
*/
string Client::getLast() {
	return last;					//Return the last name
}

/* getFirst() getter method: This method is a getter method that returns the first name of the Client.
   Precondition: The first name needs to be accessed
   Postcondition: The value of the first name has been returned
*/
string Client::getFirst() {
	return first;					//Return the first name
}

/* getID() getter method: This method is a getter method that returns the first name of the Client.
	Precondition: The ID of the client needs to be accessed
	Postcondition: The value of the ID has been returned
*/
string Client::getID() {
	return ID;						//Return the ID
}

/*  showHistory() method: This method displays the transaction history for 'this Client. This method uses
	a STL stack object of Transaction type for handling the Transaction objects from the history stack of 
	Transaction objects. The method loops until the history stack is empty, cout-ing Transaction's data from the
	top of the stack, then popping off the Transaction object from history into the temp stack. Once that's done,
	another while loop pops Transactin objects from temp, back into the history stack.
	Precondition: The transaction history of a client needs to be shown.
	Postcondition: The transaction history of a client has been shown and all Transaction objects are placed back
	where they were
*/
void Client::showHistory() {
	stack<Transaction> temp;								//Temporary stack used for holding the Transaction objects from history
	cout << "Transaction history for " + getID() << endl;	//Transaction history header
	cout << "-------------------------------" << endl;		//Header line
	while (!history.empty()) {								//Looping until history stack is empty
		cout << history.top();								//Outputing the Transaction object at the top of the history stack
		temp.push(history.top());							//Pushing the top Transaction object into the temp stack
		if (history.top().getOp() == 'M') history.pop();	//pops the extra transaction off thats not necessary
		history.pop();										//Removing the top Transaction object from the history stack
	}
	cout << endl << endl << endl;							//Adding spaces
	while (!temp.empty()) {									//Looping until the temp stack is empty
		history.push(temp.top());							//Pushing the top Transaction object back into the history stack
		temp.pop();											//Removing the top Transaction object from the temp stack
	}
}

/* addToAccount() method: This method is an assisting method that helps call the lose account object's addToAccount() method,
   which adds the given amount to the specified account. The method returns whatever lose's addToAccount() method returns.
   Precondition: The Client needs to add money to the specified account
   Postcondition: Money has been added to the account and true is returned, or no money was added to the account and false is returned
*/
bool Client::addToAccount(int acc, int amount) {
	return lose.addToAccount(acc, amount);			//Return the value of lose's addToAccount(), inputing the given arguments
}

/* subtractFromAccount() method: This method is an assisting method that helps call the lose account object's subtractFromAccount
   method, which subtracts the given amount from the specified account. The method returns whatever the lose's addToAccount() method
   returns.
   Precondition: The Client needs to withdraw money from a specified account
   Postcondition: Money has been withdrawn from the specified account and true is returned, or no money has been withdrawn and false is returned
*/
bool Client::subtractFromAccount(int acc, int amount) {
	return lose.subtractFromAccount(acc, amount);	//Return the value of the lose's addToAccount(), inputing the given arguments
}

/* addToHistory() method: This method adds Transaction data of the client to the client's history stack of transactions. 
   The method takes in the 4-digit ID, the account number, another string for a 5-digit LOSE accoutn in case the Transaction 
   involved moving money from one account to another, an integer amount, and the operation that was performed. All of these
   data are placed into a statically-allocated Transaction object and placed into the history stack. Then true is returned.
*/
bool Client::addToHistory(string id, int acc, string id2, int amount, char op) {
	string realID = id + to_string(acc);					//Forming the 5-digit LOSE account ID
	Transaction tran(op, realID, id2, amount);				//Creating a Transaction object with the given inputs
	history.push(tran);										//Pushing the current transaction into the history stack
	return true;											//Returning true
}

/* Overloaded operator<(): This operator<() method compares two client's IDs. If 'this' ID is smaller than the comparing Client's
   ID, return true. Otherwise, return false.
   Precondition: The rhs Client is the desired Client for comparing.
   Postcondition: The two clients have been compared. The 'this' client's ID is smaller than the other client's ID and true is returned,
   or the statement is false and false is returned.
*/
bool Client::operator<(Client& toCompare) {
	if (getID() < toCompare.getID()) return true;			//If 'this' ID is smaller than the other Client's ID
	else return false;										//Otherwise, return false
}

/* Overloaded operator>(): This operator>() uses the operator<() to compare two client's ID's. In this case, we are checking if 'this'
   client's ID is greater than the rhs client's ID by putting a ! (NOT) before the operator<() call.
   Precondition: The rhs Client is the desired Client for comparing.
   Postcondition: The two clients have been compared. The 'this' client's ID is greater than the other client's ID and true is returned.
*/
bool Client::operator>(Client& toCompare) {
	return !operator<(toCompare);							//Return the negative of operator<(), with the argument as input
}

/* Overloaded operator==(): This operator==() compares if two client's ID's are equal. If equal, true is returned, and false is returned
   otherwise.
   Precondition: The argument client is the desired client for comparing.
   Postconditino: The Client objects have been compared and true is returned, or false is returned because they're not equal
*/
bool Client::operator==(Client& toCompare) {
	if (getID() == toCompare.getID()) return true;				//If 'this' client's ID is greater than the other client's ID, return true
	else return false;											//Otherwise return false
}

/* Overloaded operator=(): This operator=() is used to copy the last and first names of the rhs Client, as well as the ID and lose
   account balances. However, history is not kept. After the copying, 'this' object is returned.
   Precondition: The rhs Client is the desired Client to copy from
   Postcondition: 'this' Client now contains the same values as the argument Client and 'this' object has been returned
*/
Client& Client::operator=(Client& toCopy) {
	if (this != &toCopy) {						//If it's not the same object we're assigning to
		last = toCopy.getLast();				//copy the last name
		first = toCopy.getFirst();				//copy the first name
		ID = toCopy.getID();					//copy the ID
		lose = toCopy.lose;						//copy the account balances
	}
	return *this;								//Return 'this' object 
}

/* Overloaded operator<<(): This operator<<() is used to create formatted data for output, placed into an ostream& object and returned
   as a reference. The data is organized in last, first, ID, and accounts.
   Precondition: The argument Client is the desired client for outputing into the ostream object
   Postcondition: The argument Client's data has been properly formatted into strings, streamed into the ostream object and returned
*/
ostream& operator<<(ostream& out, const Client& target) {
	out << target.last << " " << target.first << " " << target.ID << " " << endl << target.lose; //The formatting the Client's data
	out << endl;
	return out;				//Returning the formatted ostream object
}