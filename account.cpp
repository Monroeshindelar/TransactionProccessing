#include "stdafx.h"
#include "account.h"


ostream& operator<<(ostream& out, const Account& rhs) {
	out << "---Initial balances---" << endl;
	out << "Money Market: " << rhs.initialBalance[0] << endl;
	out << "Prime Money Market: " << rhs.initialBalance[1] << endl;
	out << "Long-Term Bond: " << rhs.initialBalance[2] << endl;
	out << "Short-Term Bond: " << rhs.initialBalance[3] << endl;
	out << "500 Index Fund: " << rhs.initialBalance[4] << endl;
	out << "Capital Value Fund: " << rhs.initialBalance[5] << endl;
	out << "Growth Equity Fund: " << rhs.initialBalance[6] << endl;
	out << "Growth Index Fund: " << rhs.initialBalance[7] << endl;
	out << "Value Fund: " << rhs.initialBalance[8] << endl;
	out << "Value Stock Index: " << rhs.initialBalance[9] << endl;
	out << endl;
	out << "---Current LOSE Account balances---" << endl;
	out << "Money Market: " << rhs.loseAccount[0] << endl;
	out << "Prime Money Market: " << rhs.loseAccount[1] << endl;
	out << "Long-Term Bond: " << rhs.loseAccount[2] << endl;
	out << "Short-Term Bond: " << rhs.loseAccount[3] << endl;
	out << "500 Index Fund: " << rhs.loseAccount[4] << endl;
	out << "Capital Value Fund: " << rhs.loseAccount[5] << endl;
	out << "Growth Equity Fund: " << rhs.loseAccount[6] << endl;
	out << "Growth Index Fund: " << rhs.loseAccount[7] << endl;
	out << "Value Fund: " << rhs.loseAccount[8] << endl;
	out << "Value Stock Index: " << rhs.loseAccount[9] << endl;
	return out;
}

Account::Account() {}

Account::Account(int* balances) {
	for (int i = 0; i < 10; i++) {
		loseAccount[i] = balances[i];
		initialBalance[i] = balances[i];
	}
}

Account::~Account() {
}

bool Account::subtractFromAccount(int acc, int amount) {
	if (acc < 0 || acc > 9) return false;
	switch (acc) {
	case 0:
		if (loseAccount[0] < amount && loseAccount[1] > amount - loseAccount[0]) {
			loseAccount[1] -= amount - loseAccount[0];
			loseAccount[0] = 0;
			return true;
		}
		else if (loseAccount[0] < amount && loseAccount[1] < amount - loseAccount[0]) return false;
		else {
			loseAccount[0] -= amount;
			return true;
		}
	case 1:
		if (loseAccount[1] < amount && loseAccount[0] > amount - loseAccount[1]) {
			loseAccount[0] -= amount - loseAccount[1];
			loseAccount[1] = 0;
			return true;
		}
		else if (loseAccount[1] < amount && loseAccount[0] < amount - loseAccount[1]) return false;
		else {
			loseAccount[1] -= amount;
			return true;
		}
	case 2:
		if (loseAccount[2] < amount && loseAccount[3] > amount - loseAccount[2]) {
			loseAccount[3] -= amount - loseAccount[2];
			loseAccount[2] = 0;
			return true;
		}
		else if (loseAccount[2] < amount && loseAccount[3] < amount - loseAccount[2]) return false;
		else {
			loseAccount[2] -= amount;
			return true;
		}
	case 3:
		if (loseAccount[3] < amount && loseAccount[2] > amount - loseAccount[3]) {
			loseAccount[2] -= amount - loseAccount[3];
			loseAccount[3] = 0;
			return true;
		}
		else if (loseAccount[3] < amount && loseAccount[2] < amount - loseAccount[3]) return false;
		else {
			loseAccount[3] -= amount;
			return true;
		}
	default:
		if (loseAccount[acc] < amount) return false;
		else {
			loseAccount[acc] -= amount;
			return true;
		}
	}
}

bool Account::addToAccount(int acc, int amount) {
	if (acc < 0 || acc > 9) return false;
	else loseAccount[acc] += amount;
	return true;
}
