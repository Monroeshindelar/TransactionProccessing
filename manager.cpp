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

#include "manager.h"

//-----------------------------------Manager Constructor-----------------------------------
//Precondition: Need to construct a manager object.
//Postcondition: Manager object constructed and intialized.
/*
Manager: This is the default constructer for the manager class. It doesnt do anything because
everything that the manager holds can be intitialized on the stack. This is just here because
we dont trust the default constructor given to us.
*/
Manager::Manager() {}
//-----------------------------------Manager Constructor-----------------------------------
//Precondition: Need to destruct a manager object
//Postcondition: Manager object destructed.
/*
~Manager: This is the default destructor for the manager class. It doesnt delete anything because
nothing is made in dynamic memory. We dont need to delete anything but we dont trust what is given
to us for free
*/
Manager::~Manager() {}
//-----------------------------------Generate Firm-----------------------------------
//Precondition: Need to intitalize a bank with clients from a file
//Postcondition: File read and banks data structe is filled with its clients.
/*
Generate Firm: The goal of this method is to take a file full of the information of banking
clients and store them in managers tree. It takes in a reference to the file that it reads.
A string to store the last name, the first name and the id are intialized, and then it makes
an array of integers that will store the intital balance of the clients bank accounts. Then the
program loops and stores the data items that are in the file into the proper strings and all of
the intial balances into the array (This assumes a properly formatted file). The while loop is a
little messy, but its done this way to decrease complexity. After it takes in all the information
from the line on the file and uses it to initialize a new client, then the client is inserted into
the array. Then we return true.
*/
bool Manager::generateFirm(ifstream& file) {
	//These are the variables that store the temporary
	//data that represents the client. These are 
	//initialized in the order they are expected.
	string l; //make a string to store the last name
	string f; //make a string to store the first name
	string i; //make a string to store the ID
	int account[10]; //make an array to store the intitial balances of the account
	//loop while we can put all these items into the initialized variables
	while (file >> l >> f >> i >> account[0] >> account[1] >> account[2] >> account[3] >> account[4] >> account[5] >> account[6] >> account[7] >> account[8] >> account[9]) {
		Client newClient(l, f, i, account); //make a new client with the information taken from the line
		firm.insert(newClient); //insert the client into the firm
	}
	return true; //return success
}
//-----------------------------------Take Transactions-----------------------------------
//Precondition: Need to take transactions to perform on clients bank accounts from a file
//Postcondition: Transactions stored in a queue to be performed later.
/*
Take Transactions: The goal of this method is to take a file and read transaction commands
from it. It stores the transaction commands in the queue to be performed later using a different
function call. It takes in a file and reads each line. First we initialize temporary variables to 
store the data from the file so we can craft a transaction object to store in the queue. We make
a char to store the operator, a string that represents the ID of the client. Another string that
we set to an empty string that we use just in case the transaction is a move command, and an int
that represents the amount of money we will be working with. These are initialized in the order
we expect to see them in the (Assuming correct input from the file). Since the smallest number of
elements that we can see is 2 (View History with command and ID), we take in the command and the ID
of the user. Then we check the operator to see if we need to read more data. If it is a D or a W 
then we read the amount from the file. If it is an M then we read the amount and then the second
ID from the file. Then we create a transaction object and give it all of the information necessary
and push it to the transaction queue. Then we return true.
*/
bool Manager::takeTransactions(ifstream& file) {
	//These are the variables that store the temporary
	//data that represents the transaction. These are 
	//initialized in the order they are expected.
	char operation; //char to store the operation
	string i; //string to store the ID of the client
	string i2 = ""; //second string for move operations
	int amount = 0; //int to store the amount
	while (file >> operation >> i) { //while we can still have operators and IDs in the file
		if (operation == 'D' || operation == 'W') file >> amount; //check the operator, if its d or w then we need the amount as well 
		else if (operation == 'M') file >> amount >> i2; //check the operator, if its m then we need the amount and then another ID for the account to move to
		Transaction newTrans(operation, i, i2, amount); //make a new transaction object that has the information from the file
		transactionQueue.push(newTrans); //push the new transaction to the queue
	}
	return true; //return true
}
//-----------------------------------Perform Transactions-----------------------------------
//Precondition: Need to perform all the transactions waiting in the queue
//Postcondition: All transactions from the queue are popped and performed
/*
Perform Transactions: The goal of this methods is to perform all of the transactions that have
been stored in the queue by the take transactions function. We loop while there are still transactions
that need to be performed. We make a reference to a transaction object that will represents the current
transaction at the front of the queue. First we pull the ID out of the account, but since the last digit
is the specific account we need to modify, so we modify the string so that is just the first four digits
that represent the client. Then we get the account we need to modify by taking the last char of the string
and subtracting the value of the char 0 to get its actual value. Then we check the operator of the transaction
to see what operations we need to perform. If it is a D we will call buyshares, if its a w we will call the sell
shares fucntion. If its a m then we will call the move shares function, and if its an h we will call the view
history function. Then if the operator is D or W we will push it to the undo stack (Move functions are processed
as a buy function and a sell function, so a move function will be represented as a buy and a sell in the undo 
stack). At the end we pop off the transaction queue.
*/
void Manager::performTransactions() {
	while (!transactionQueue.empty()) { //loop while the transaction queue still has transactions to process
		Transaction& current = transactionQueue.front(); //make a new transaction that represents the transaction at the front of the queue
		string clientID = current.getID().substr(0, 4); //get the 4 digit client ID
		int account = (current.getID().at(current.getID().length() - 1)) - '0'; //get the last digit on the end of the 5 digit client ID that represents the account to modify
		switch (current.getOp()) { //switch on the operator
		case 'D': //if the operator is D
			buyShares(clientID, account, current.getAmount()); //call buy shares with the proper information
			break; //break from the switch
		case 'W': //if the operator is W
			sellShares(clientID, account, current.getAmount()); //call sell shares with the proper information
			break; //break
		case 'M': //if the operator is M
			moveShares(clientID, account , current.getMoveToID(), current.getAmount()); //call move shares with the proper information
			break; //break from the switch 
		case 'H': //if the operator is H
			viewHistory(clientID); //view the history with the client of the same ID
			break; //break from the loop
		default: //otherwise
			cout << "Incorrect operation" << endl; //incorrect operator
			break; //break from the switch
		}
		if (current.getOp() == 'D' || current.getOp() == 'W' || current.getOp() == 'M') undo.push(current);
		transactionQueue.pop(); //pop off from the queue
	}
}
//-----------------------------------Buy Shares-----------------------------------
//Precondition: Need to deposit money into a clients account
//Postcondition: Funds added to correct clients account
/*
Buy Shares: The goal of this method is to deposit money into a clients account.
It takes in an ID to represent the client we are modifying, an account that 
represents the specific lose accout that we will be adding funds to, and then
the amount of money that we will be adding to the account. First we initialize 
a temp array, this is just so that we can craft a client to compare to other 
clients in the list. Then we craft basically an empty client so that we can use
it to search for the client which has that ID (Clients are compared by ID). Then
we make a ponter to a client, which is not initialized to have any values. This
will be used to store the information from the actual client that we find in the
bank. Then we call the retrieve function of the banks tree and pass it the empty
client, that just contains the ID of the client we are looking for. If we have
found the client we are looking for in the tree, then we will call the clients 
add to account function and passing it the account and the amount of money we 
are working with, and then we add this transaction to the history of the client.
We return a boolean that represents the success of buying shares.
*/
bool Manager::buyShares(string ID, int acc, int amount) {
	//Initializations
	int temp[10]; //this is just so we can satisfy the client constructor
	Client toFind("", "", ID, temp); //make an empty client with the ID of the client we are supposed to be modifying
	Client* theClient; //make a pointer to a client that we will use to store the reference to the client we want to modify
	bool success = firm.retrieve(toFind, theClient); //Search the bank tree for the client we want
	if (success) { //if we find it
		success = theClient->addToAccount(acc, amount); //add the money to the account
		if(success) theClient->addToHistory(ID, acc, "", amount, 'D'); //add the transaction to the clients history
	}
	return success; //return the status of the function
}
//-----------------------------------Sell Shares-----------------------------------
//Precondition: Need to remove funds from a clients account
//Postcondition: Funds removed from a clients account
/*
Sell Shares: The goal of this method is to withdraw money from a clients account.
It takes in an ID to represent the client we are modifying,, an account that
represents the specific lose account that we will be adding funds to, and then the 
amount of money that we will be adding to the account. First we initialize a temp
array, this is just so that we can craft a client to compare to other clients in the
list. Then we craft basically an empty client so that we can use it to search for the
client which has the ID of the client we are looking for. If we have foudn the client we
are looking form in the tree, then we will call the clients subtract from account 
method and then add this transaction to the history of the client. We return a boolean that
represents the success of selling shares.
*/
bool Manager::sellShares(string ID, int acc, int amount) {
	//initializations
	int temp[10]; //this is just so we can satisfy the client constructor
	Client toFind("", "", ID, temp); //empty client with the ID of the client we want to modify. used for searching the tree
	Client* theClient; //pointer to a client that we will use to store the ref to the client in the tree that we are looking to modify
	bool success = firm.retrieve(toFind, theClient); //search the tree for the client, store it in the pointer
	if (success) { //if we found it
		success = theClient->subtractFromAccount(acc, amount); //subtract from the account
		if(success) theClient->addToHistory(ID, acc, "", amount, 'W'); //add it to the client history
	}
	return success; //return the status of the function.
}
//-----------------------------------Move Shares-----------------------------------
//Precondition: Need to move shares between two clients or two accounts of one client
//Postcondition: shares moved between two clients or two accounts of one client
/*
Move Shares: The goal of this function is to move shares between either two clients
or two accounts of the same client. It takes in a string that represents the ID
of the first client, an account number that represents the account we will be moving
shares from. It takes in a 5 digit string that represents both the client we will 
be moving the funds to (first 4 digits) and then the account we will be moving to, 
(the last digit), and finally the amount we will be moving. We need to parse the 
second string we have taken in as parameters so that we can get the correct client ID
and account number. After that we will call sell shares method passing it in the first
ID and account number, to remove the funds from that account, and then we will call buy
shares on the new account ID and account number, and push the transaction to the undo 
stack. Then we will return the mission status
*/
bool Manager::moveShares(string ID, int acc, string moveToID, int amount) {
	string otherClientID = moveToID.substr(0, 4); //get the move to Client ID
	int otherAcc = (moveToID.at(moveToID.length() - 1)) - '0'; //get the move to Client account
	int temp[10];
	Client toFind("", "", ID, temp);
	Client* theClient;
	bool success = firm.retrieve(toFind, theClient);
	if (success) success = sellShares(ID, acc, amount); //remove the shares from the first account
	if (success) { //if we could remove the shares from the first account
		
		buyShares(otherClientID, otherAcc, amount); //add thes shares to the other account
		theClient->addToHistory(ID, acc, moveToID, amount, 'M');
	}
	return success; //return the status of our mission
}
//-----------------------------------View History-----------------------------------
//Precondition: Need to view the history of a client
//Postcondition: Client history viewed
/*
View History: The goal of this function is to view the history of a client. First we make 
a temp array so that we can satisfy the condition of the Client constructor. Then we make
and empty client with the ID of the client we are trying to view. After that we make a pointer
to a client that will store the actual client from the tree that we will modify. We will search
the tree for the client and if we have found the client we are looking for then we will show
their history. Then we will return mission status
*/
bool Manager::viewHistory(string ID) {
	//initializations to traverse the tree
	//in search for our client.
	int temp[10]; //array to satisfy the client constructor
	Client toFind("", "", ID, temp); //construct an empty client with the ID of the client we are looking for
	Client* theClient; //pointer to the client in the tree
	bool success = firm.retrieve(toFind, theClient); //traverse the tree in search of the chosen one
	if (success) theClient->showHistory(); //if we have found the chosen one we will show its history
	return success; //return the mission status
}
//-----------------------------------Undo Last Transaction-----------------------------------
//Precondition: Need to undo the last performed transaction
//Postcondition: Last performed transaction undone
/*
Undo Last Transaction: The goal of this function is to undo the last performed transaction.
First we check to see if the stack that stores the undos is empty, if it is we will return false;
Otherwise we will pull a transaction off the top of the undo stack, we will get the client ID
out of the transaction that we pulled out, parse it so we get the 4 digit client ID number as well
a the account that we had modified. Then we perform switch on the operator that was performed and
do the exact opposite of the thing that was previously done. Then we push the undone transaction to 
the redo stack and pop it off the undo stack.
*/
bool Manager::undoLastTransaction() {
	if (undo.empty()) return false; //check if the undo stack is empty, return false if it is
	Transaction currentUndo = undo.top(); //pull the transaction off the to top the stack
	string clientID = currentUndo.getID().substr(0, 4); //get the 4 digit client ID
	int account = (currentUndo.getID().at(currentUndo.getID().length() - 1)) - '0'; //get the account we need to modify
	string clientID2 = "";
	int account2 = 0;
	switch (currentUndo.getOp()) { //switch depending on the operator
		case 'D':
			sellShares(clientID, account, currentUndo.getAmount());
			break;
		case 'W':
			buyShares(clientID, account, currentUndo.getAmount());
			break;
		case 'M':
			clientID2 = currentUndo.getMoveToID().substr(0, 4);
			account2 = (currentUndo.getMoveToID().at(currentUndo.getID().length() - 1)) - '0';
			moveShares(clientID2, account2, currentUndo.getID(), currentUndo.getAmount());
			break;
	}
	redo.push(undo.top()); //add the transaction the redo stack
	undo.pop(); //pop the transaction off the undo stack
	return true; //return the status of the mission
}
//-----------------------------------Redo Last Transaction-----------------------------------
//Precondition: Need to redo the last undone transaction
//Postcondition: last transaction redone
/*
Redo Last Transaction: The goal of this function is to redo a transaction that was undone by
the undo stack. First we check to see if the redo stack is empty, and if it is we will return
false. Otherwise we will pull a transaction out of the stack. Then we will pull the client ID 
out of the transaction, and parse it to get the 4 digit client ID and the 1 digit that represents
the account we will be modifying. Then we switch on the operation, and perform the same transaction
that we pulled out of the stack. Then we will push the current transaction to the top of the undo
stack and pop it off the top of the redo stack
*/
bool Manager::redoLastTransaction() {
	if (redo.empty()) return false; //check the redo stack to see if there is anything there
	Transaction current = redo.top(); //pull the transaction off the top of the stack
	string clientID = current.getID().substr(0, 4); //get the 4 digit client ID
	int account = (current.getID().at(current.getID().length() - 1)) - '0'; //get the account we need to modify
	switch (current.getOp()) { //switch on the transaction operator
		case 'D':
			buyShares(clientID, account, current.getAmount());
			break;
		case 'W':
			sellShares(clientID, account, current.getAmount());
			break;
		case 'M':
			moveShares(clientID, account, current.getMoveToID(), current.getAmount());
			break;
	}
	undo.push(undo.top()); //push the current transaction to the undo stack
	redo.pop(); //pop the transaction off the top of the redo stack
	return true; //return true
}
//-----------------------------------Operator<<-----------------------------------
//Precondition: Need to print the status of the Manager
//Postcondition: Manager status printed
/*
Operator<<: The goal of this method is to print out the status of the bank. It calls 
the operator<< of the tree.
*/
ostream& operator<<(ostream& out, const Manager& target) {
	out << target.firm; //output the operator<< of the tree
	return out; //return the out.
}