#include <iostream>
#include "Account.h"
using namespace std;

inline bool Account::authenticate(int id, string passwd) {
	if (this->nID == id && this->strPassword == passwd) {
		return true;
	}
	else {
		return false;
	}
}

Account::Account() {
	this->nID = -1;
	this->nBalance = 0;
}

void Account::create(int id, int money, string name, string password) {
	this->nID = id;
	this->nBalance = money;
	this->strAccountName = name;
	this->strPassword = password;
}

int Account::check(int id, string password) {
	if (this->authenticate(id, password)) {
		return this->nBalance;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::close(int id, string password) {
	if (this->authenticate(id, password)) {
		return AUTHENTIFICATION_FAIL;
	}

	if (this->nBalance == 0) {
		this->nID = -1;
		return AUTHENTIFICATION_SUCCESS;
	}
	else {
		return 0;
	}
}

int Account::deposit(int id, string password, int money) {
	if (authenticate(id, password)) {
		this->nBalance += money;
		return this->nBalance;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::widraw(int id, string password, int money) {
	if (authenticate(id, password)) {

		if (this->nBalance < money) {
			return -2;
		}

		this->nBalance -= money;
		return this->nBalance;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}