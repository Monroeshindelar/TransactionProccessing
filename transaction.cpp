/*File: transaction.cpp
Monroe Shindelar and JJ Abides
Professor Rob Nash
CSS 342: Data Structures, Algorithms, and Discrete Math
December 7, 2016
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

#include "transaction.h"
#include <string>

/* overloaded operator<<(): This overloaded operator<<() is used to return an ostream reference
object that contains a string with the op, ID, moveToID, and amount. The values in string-type
are placed into ostream object and then returned.
Precondition: The given ostream object and transaction object are the desired objects for handling
Postcondition: The ostream object contains a proper output from the rhs Transaction object and the ostream is returned
*/
/*ostream& operator<<(ostream& out, const Transaction& rhs) {
//Placing all instance variables inside ostream object
out << rhs.getOp() << " " << rhs.getID() << " " << rhs.getID() << " " << rhs.getMoveToID() << " " << rhs.getAmount() << endl;
return out; //Returning the ostream object
}*/

/* Transaction constructor: This constructor takes in a char for the command, a string for the ID, another string
for the account to move to, and the amount that is being handled.
Precondition: None
Postcondition: A Transaction object exists with the inputed value.
*/
Transaction::Transaction(char o, string i, string mtd, int a) : op(o), ID(i), moveToID(mtd), amount(a) {}

/* Transaction destructor: This destructor does not do anything
Precondition: A Transaction object needs to be destructed
Postcondition: A Transaction object has been destructed
*/
Transaction::~Transaction() {
}

/* getOp() method: This is a getter method for returning the private op char. It is const to
prevent any values from being changed within 'this' Transaction object.
Precondition: A Transaction object is in need of access to the op variable
Postcondition: A copy of the op's value is returned
*/
char Transaction::getOp() const {
	return op;				//Returning the private op char
}

/* getID() method: This getter method is used to return the private string ID variable. It is const
to prevent any changes made to 'this' Transaction object's instance variables.
Precondition: A Transaction object is needs access to it's ID's value
Postcondition: A copy of the ID's value is returned
*/
string Transaction::getID() const {
	return ID;				//Returning the ID value
}

/* getMoveToID() method: This getter method is used to return the private moveToID's value. It is
const to prevent any changes to 'this' Transaction object's instance variables.
Precondition: A Transaction object needs access to it's moveToID's value
Postcondition: A copy of the moveToID's value is returned
*/
string Transaction::getMoveToID() const {
	return moveToID;		//Returning the value of moveToID
}

/* getAmount() method: This getter method is used to return the private amount variable's value. It is
const to prevent any changes to 'this' Transaction object's instance variables.
Precondition: A Transaction object needs access to it's amount variables value
Postcondition: A copy of the amount variable's value is returned
*/
int Transaction::getAmount() const {
	return amount;				//Returning the amount's value
}

ostream& operator<<(ostream& out, const Transaction&) {
	return out;
}