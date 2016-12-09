#include "stdafx.h"
#include "manager.h"


Manager::Manager() {

}

Manager::~Manager() {

}

bool Manager::generateFirm(ifstream& file) {
	string l;
	string f;
	string i;
	int account[10];
	while (file >> l >> f >> i >> account[0] >> account[1] >> account[2] >> account[3] >> account[4] >> account[5] >> account[6] >> account[7] >> account[8] >> account[9]) {
		Client newClient(l, f, i, account);
		firm.insert(newClient);
	}
	return true;
}

bool Manager::takeTransactions(ifstream& file) {
	char operation;
	string i;
	string i2 = "";
	int amount;
	while (!file.eof()) {
		file >> operation >> i >> amount;
		if (operation == 'M') file >> i2;
		Transaction newTrans(operation, i, i2, amount);
		transactionQueue.push(newTrans);
	}
	return true;
}

void Manager::performTransactions() {
	while (!transactionQueue.empty()) {
		Transaction& current = transactionQueue.front();
		string clientID = current.getID().substr(0, 4);
		int account = (current.getID().at(current.getID().length() - 1)) - '0';
		switch (current.getOp()) {
			case 'D':
				buyShares(clientID, account, current.getAmount());
				break;
			case 'W':
				sellShares(clientID, account, current.getAmount());
				break;
			case 'M':
				moveShares(clientID, account, current.getMoveToID(), current.getAmount());
				break;
			case 'H':
				viewHistory(clientID);
				break;
			default: 
				cout << "Incorrect operation" << endl;
				break;
		}
		char check = current.getOp();
		if (check == 'H') undo.push(current);
		transactionQueue.pop();
	}
}

bool Manager::buyShares(string ID, int acc, int amount) {
	int temp[10];
	Client toFind("", "", ID, temp);
	Client theClient;
	bool success = firm.retrieve(toFind, theClient);
	theClient.addToAccount(acc, amount);
	return success;
}

bool Manager::sellShares(string ID, int acc, int amount) {
	int temp[10];
	Client toFind("", "", ID, temp);
	Client theClient;
	bool success = firm.retrieve(toFind, theClient);
	theClient.subtractFromAccount(acc, amount);
	return success;
}

bool Manager::moveShares(string ID, int acc, string moveToID, int amount) {
	string otherClientID = moveToID.substr(0, 4);
	int otherAcc = (moveToID.at(moveToID.length() - 1)) - '0';
	bool success = sellShares(ID, acc, amount);
	if (success) buyShares(otherClientID, otherAcc, amount);
	return success;
}

bool Manager::viewHistory(string ID) {
	int temp[10];
	Client toFind("", "", ID, temp);
	Client theClient;
	bool success = firm.retrieve(toFind, theClient);
	theClient.showHistory();
	return success;
}

bool Manager::undoLastTransaction() {
	if (undo.empty()) return false;
	Transaction currentUndo = undo.top();
	string clientID = currentUndo.getID().substr(0, 4);
	int account = (currentUndo.getID().at(currentUndo.getID().length() - 1)) - '0';
	string clientID2;
	int account2;
	switch (currentUndo.getOp()) {
	case 'D':
		 sellShares(clientID, account, currentUndo.getAmount());
		 break;
	case 'W':
		 buyShares(clientID, account, currentUndo.getAmount());
		 break;
	case 'M':
		clientID2 = currentUndo.getMoveToID().substr(0, 4);
		account2 = (currentUndo.getID().at(currentUndo.getID().length() - 1)) - '0';
		moveShares(clientID2, account2, currentUndo.getID(), currentUndo.getAmount());
		break;
	}
	redo.push(undo.top());
	undo.pop();
	return true;
}

bool Manager::redoLastTransaction() {
	if (redo.empty()) return false;
	Transaction current = undo.top();
	string clientID = current.getID().substr(0, 4);
	int account = (current.getID().at(current.getID().length() - 1)) - '0';
	switch (current.getOp()) {
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
	undo.push(undo.top());
	redo.pop();
	return true;
}

ostream& operator<<(ostream& out, const Manager& target) {
	return out;
}