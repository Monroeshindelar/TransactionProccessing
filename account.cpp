/*
Monroe Shindelar and JJ Abides
Professor Rob Nash
CSS 342: Data Structures, Algorithms, and Discrete Math
December 9, 2016
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
#include "account.h"

/* Overloaded operator<<(): This overloaded operator<<() function creates an output text for the argument
   ostream& out and returns that ostream object for console display. The contents are retrieved from the rhs
   Account object. The Account object is const to prevent any changes. The text that is being inputed into
   the ostream object are the initial balances of the accounts, followed by current balances of the accounts.
   Once all text has been placed into the ostream object, a reference of the ostream object is returned.
   Precondition: The rhs Account is the desired Account object for streaming its data
   Postcondition: The ostream out object contains data of the Account object's balances and has been returned as a reference
*/
ostream& operator<<(ostream& out, const Account& rhs) {
	out << "---Initial balances---" << endl;							//Initial balance header
	out << "Money Market: " << rhs.initialBalance[0] << endl;			//Initilal balance of Money Market
	out << "Prime Money Market: " << rhs.initialBalance[1] << endl;		//Initial balance of Prime Money Market
	out << "Long-Term Bond: " << rhs.initialBalance[2] << endl;			//Initial balance of Long-Term Bond
	out << "Short-Term Bond: " << rhs.initialBalance[3] << endl;		//Initial balance of Short-Term Bond
	out << "500 Index Fund: " << rhs.initialBalance[4] << endl;			//Initial balance of 500 Index Fund
	out << "Capital Value Fund: " << rhs.initialBalance[5] << endl;		//Initial balance of Capital Value
	out << "Growth Equity Fund: " << rhs.initialBalance[6] << endl;		//Initial balance of Growth Equity Fund
	out << "Growth Index Fund: " << rhs.initialBalance[7] << endl;		//Initial balance of Growth Index Fund
	out << "Value Fund: " << rhs.initialBalance[8] << endl;				//Initial balance of Value Fund
	out << "Value Stock Index: " << rhs.initialBalance[9] << endl;		//Initial balance of Value Stock Index
	out << endl;														//New line
	out << "---Current LOSE Account balances---" << endl;				//Current balance header
	out << "Money Market: " << rhs.loseAccount[0] << endl;				//Current balance of Money Market
	out << "Prime Money Market: " << rhs.loseAccount[1] << endl;		//Current balance of Prime Money Market
	out << "Long-Term Bond: " << rhs.loseAccount[2] << endl;			//Current balance of Long-Term Bond
	out << "Short-Term Bond: " << rhs.loseAccount[3] << endl;			//Current balance of Short-Term Bond
	out << "500 Index Fund: " << rhs.loseAccount[4] << endl;			//Current balance of 500 Index Fund
	out << "Capital Value Fund: " << rhs.loseAccount[5] << endl;		//Current balance of Capital Value Fund
	out << "Growth Equity Fund: " << rhs.loseAccount[6] << endl;		//Current balance of Growth Equity Fund
	out << "Growth Index Fund: " << rhs.loseAccount[7] << endl;			//Current balance of Growth Index Fund
	out << "Value Fund: " << rhs.loseAccount[8] << endl;				//Current balance of Value Fund
	out << "Value Stock Index: " << rhs.loseAccount[9] << endl;			//Current balance of Value Stock Index
	return out;															//Returning the formatted data
}

/* Default Account constructor: This default constructor initializes the initial balances and current
   LOSE account balances to 0.
   Precondition: None
   Postcondition: An Account object with empty initial balances and current LOSE account balances has been created
*/
Account::Account() {
	for (int i = 0; i < 10; i++) {			//Looping through every index
		loseAccount[i] = 0;					//Setting the account to 0
		initialBalance[i] = 0;				//Setting the accoun to 0
	}
}

/* Account constructor: This Account constructor takes an int pointer as an argument. This constructor is used primarily
   for inserting an integer array that represents the balances of each market, fund, bond, etc. The LOSE account and inital
   balance account arrays are then assigned to the respective index values of the argument array.
   Precondition: The argument integer pointer is an array which is the desired contain the desired initial balances
   Postcondition: An Account object has been created with loseAccount balances and initialBalances assigned to the passed
   in array's index values.
*/
Account::Account(int* balances) {
	for (int i = 0; i < 10; i++) {
		loseAccount[i] = balances[i];
		initialBalance[i] = balances[i];
	}
}

/* Account destructor: This Account destructor does nothing.
   Precondition: An Account object is currently destructing
   Postcondition: An Account object has finished destructing
*/
Account::~Account() {
}

/* subtractFromAccount() method: This method subtracts a given amount from a specified account. In the
   case that the given account number is out of bounds, false is returned. Otherwise, the method will check
   which account is being accessed first. Then, if the account is a money market (0 or 1), or a bond (2 or 3),
   then we check if the account has sufficient funds. If the chosen account does not have sufficient funds for
   withdrawing, we take the remainder funds from the other market or other bond account and return true. If both 
   accounts do not have enough funds, then false is returned. If the account does have enough funds, then those
   funds in the specified account are reduced by the amount. If another account is chosen (instead of 0, 1, 2, 3),
   the method checks if the account has enough funds. If it does, the account is reduced and true is returned.
   Otherwise, false is returned.
   Precondition: The client needs to withdraw money from an account.
   Postcondition: The specified account has had money withdrawn from it and true is returned, or money has not been
   withdrawn and false is returned.
*/
bool Account::subtractFromAccount(int acc, int amount) {
	if (acc < 0 || acc > 9) return false;														//If acc is out-of-bounds, return false
	switch (acc) {																				//Switch case
	case 0:	//Money Market
		//If account 0 has less money than the amount, AND the other market account has enough funds for the remainder...
		if (loseAccount[0] < amount && loseAccount[1] > amount - loseAccount[0]) {
			loseAccount[1] -= amount - loseAccount[0];											//Withdraw the remainder from the next account
			loseAccount[0] = 0;																	//The chosen account is now 0
			return true;																		//Return true
		}
		//Else, if account 0 has less money than the amount, AND the other market account DOES NOT have enough funds for the remainder...
		else if (loseAccount[0] < amount && loseAccount[1] < amount - loseAccount[0]) return false;		//Return false
		//Otherwise, the chosen account has enough funds for withdrawal
		else {
			loseAccount[0] -= amount;				//Withdraw the given amount
			return true;							//Return true
		}
	case 1:	//Prime Money Market
		//If account 1 has less money than the amount, AND the other market account has enough funds for the remainder...
		if (loseAccount[1] < amount && loseAccount[0] > amount - loseAccount[1]) {
			loseAccount[0] -= amount - loseAccount[1];											//Withdraw the remainder from the other account
			loseAccount[1] = 0;																	//The chosen account is now 0
			return true;																		//Return true
		}
		//Else, if account 1 has less money than the amount, AND the other market account DOES NOT have enough funds for the remainder...
		else if (loseAccount[1] < amount && loseAccount[0] < amount - loseAccount[1]) return false;		//Return false
		//Otherwise, the chosen account has enough funds for withdrawal
		else {
			loseAccount[1] -= amount;				//Withdraw the given amount
			return true;							//Return true
		}
	case 2:	//Long-Term Bond
		//If account 2 has less money than the amount, AND the other bond account has enough funds for the remainder...
		if (loseAccount[2] < amount && loseAccount[3] > amount - loseAccount[2]) {
			loseAccount[3] -= amount - loseAccount[2];											//Withdraw the remainder from the other account
			loseAccount[2] = 0;																	//The chosen account's balance is 0
			return true;																		//Return true
		}
		//Else, if account 2 has less money than the amount, AND the other bond account DOES NOT have enough funds for the remainder...
		else if (loseAccount[2] < amount && loseAccount[3] < amount - loseAccount[2]) return false;		//Return false
		//Otherwise, the chosen account has enough funds for withdrawal
		else {
			loseAccount[2] -= amount;				//Withdraw the given amount
			return true;							//Return true
		}
	case 3: //Short-Term Bond
		//If account 3 has less money than the amount, AND the other bond account has enough funds for the remainder...
		if (loseAccount[3] < amount && loseAccount[2] > amount - loseAccount[3]) {
			loseAccount[2] -= amount - loseAccount[3];										//Withdraw the remainder from the other account
			loseAccount[3] = 0;																//The chosen account's balance is 0
			return true;																	//Return true
		}
		//Else, if account 3 has less money than the amount, AND the other bond account DOES NOT have enough funds for the remainder...
		else if (loseAccount[3] < amount && loseAccount[2] < amount - loseAccount[3]) return false;		//Return false
		//Otherwise, the chosen account has enough funds for withdrawal
		else {
			loseAccount[3] -= amount;				//Withdraw the given amount
			return true;							//Return true
		}
	default:	//For every other account
		if (loseAccount[acc] < amount) return false;		//If the amount is too much, return false
		else {
			loseAccount[acc] -= amount;						//Otherwise, withdraw the given amount
			return true;									//and return true
		}
	}
}

/* addToAccount method: This method takes an account number and an amount and adds the given amount to the chosen 
   account. If the account number is out of the bounds, false is returned. Otherwise, the transaction is performed
   and true is returned.
   Precondition: The client needs to add money to an account, and the given account number and amount are the desired
   account and amount.
   Postcondition: The client has added the given money to the specified account and true is returned, or no money was
   added and false is returned.
*/
bool Account::addToAccount(int acc, int amount) {
	if (acc < 0 || acc > 9) return false;					//If the account number is out-of-bounds, return false
	else loseAccount[acc] += amount;						//Otherwise, add the amount to the account
	return true;											//and return true
}

/* Overloaded operator=(): This operator=() is used to copy balance values from one account to 'this' account.
   The values are reassigned in a for-loop and then the 'this' object is returned. The argument is const to
   prevent any changes.
   Precondition: The rhs Account is the desired account for assigning from
   Postcondition: 'this' Account now contains the same balances as the rhs account
*/
Account& Account::operator=(const Account& rhs) {
	if (this != &rhs) {
		for (int i = 0; i < 10; i++) {
			initialBalance[i] = rhs.initialBalance[i];
			loseAccount[i] = rhs.loseAccount[i];
		}
	}
	return *this;
}