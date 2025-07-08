#include "Account.h"

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

// 실질적인 생성자. 꼭 해당 함수를 호출해서 계좌 초기화를 해줘야함
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
	if (this->authenticate(id, password) == false) {
		return AUTHENTIFICATION_FAIL;
	}

	if (this->nBalance == 0) {
		int id = this->nID;
		this->nID = -1;

		return id;
	}
	else {
		return 0;
	}
}

int Account::deposit(int id, string password, int money) {
	if (this->authenticate(id, password)) {
		this->nBalance += money;
		return this->nBalance;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::withdraw(int id, string password, int money) {
	if (this->authenticate(id, password)) {

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

bool Account::deposit(Account* target, int money) {
	if (this->nBalance < money) {
		return false;
	}
	else {
		this->nBalance -= money;
		target->nBalance += money;
		return true;
	}
}

bool Account::updatePasswd(string oldPasswd, string newPasswd) {
	if (this->strPassword == oldPasswd) {
		this->strPassword = newPasswd;
		return true;
	}
	else {
		return false;
	}
}