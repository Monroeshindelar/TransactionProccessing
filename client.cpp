#include "client.h"
#include "transaction.h"

Client::Client() {}

Client::Client(string l, string f, string i, int* la) {
	last = l;
	first = f;
	ID = i;
	Account temp(la);
	lose = temp;
}

Client::~Client() {

}

string Client::getLast() {
	return last;
}

string Client::getFirst() {
	return first;
}

string Client::getID() {
	return ID;
}

void Client::showHistory() {
	stack<Transaction> temp;
	stack <Transaction> temp2;
	cout << "Transaction history for " + getID() << endl;
	cout << "-------------------------------" << endl;
	while (!history.empty()) {
		Transaction current = history.top();
		cout << history.top();
		temp.push(history.top());
		history.pop();
	}
	cout << endl << endl << endl;;
	while (!temp.empty()) {
		temp2.push(temp.top());
		temp.pop();
	}
	while (!temp2.empty()) {
		history.push(temp2.top());
		temp2.pop();
	}
	
}

bool Client::addToAccount(int acc, int amount) {
	return lose.addToAccount(acc, amount);
}

bool Client::subtractFromAccount(int acc, int amount) {
	return lose.subtractFromAccount(acc, amount);
}


bool Client::addToHistory(string id, int acc, string id2, int amount, char op) {
	ostringstream oss;
	oss << id << acc;
	string realID = oss.str();
	Transaction tran(op, realID, id2, amount);
	history.push(tran);
	return true;
}

bool Client::operator<(Client& toCompare) {
	if (getID() < toCompare.getID()) return true;
	else return false;
}

bool Client::operator>(Client& toCompare) {
	return !operator<(toCompare);
}

bool Client::operator==(Client& toCompare) {
	if (getID() == toCompare.getID()) return true;
	else return false;
}

Client& Client::operator=(Client& toCopy) {
	if (this != &toCopy) {
		last = toCopy.getLast();
		first = toCopy.getFirst();
	}
	return *this;
}

ostream& operator<<(ostream& out, const Client& target) {
	out << target.last << " " << target.first << " " << target.ID << " " << endl << target.lose;
	out << endl;
	return out;
}