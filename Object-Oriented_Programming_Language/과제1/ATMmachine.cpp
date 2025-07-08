#include <random>
#include <iostream>
#include "ATMmachine.h"
using namespace std;

ATMmachine::ATMmachine(int size, int balance, string password) {
	this->nMachineBalance = balance;
	this->nMaxAccountNum = size;
	this->nCurrentAccountNum = 0;
	this->strManagerPassword = password;
	this->pAcctArray = new Account * [size];
}

ATMmachine::~ATMmachine() {
	for (int i = 0; i < this->nCurrentAccountNum; ++i) {
		delete this->pAcctArray[i];
	}
	delete[] this->pAcctArray;
}

void ATMmachine::displayMenu() {
	cout << "----------------\n";
	cout << "- TUKOREA BANK -\n";
	cout << "----------------\n";
	cout << " 1. 계좌 개설\n";
	cout << " 2. 계좌 조회\n";
	cout << " 3. 계좌 해지\n";
	cout << " 4. 계좌 입금\n";
	cout << " 5. 계좌 출금\n";
	cout << " 9. 업무 종료\n";
}

void ATMmachine::createAccount() {
	if (this->nCurrentAccountNum >= this->nMaxAccountNum) {
		cout << "인원이 가득 찼습니다.\n";
		return;
	}

	string temp_name, temp_pwd;

	cout << "-----개설-----\n";
	cout << "이름 입력: ";
	cin >> temp_name;
	cout << '\n';
	cout << "암호 입력: ";
	cin >> temp_pwd;
	cout << '\n';
	
	random_device rd;
	mt19937 rng(rd());

	uniform_int_distribution<int> dist(200, 900);

	Account* new_alloc = new Account;
	new_alloc->create(dist(rng), 0, temp_name, temp_pwd);
	this->pAcctArray[this->nCurrentAccountNum++] = new_alloc;

	cout << temp_name << " 님 " << new_alloc->getAcctID() << " 번 계좌가 개설되었습니다.\n";
}

void ATMmachine::checkMoney() {
	int temp_id;
	string temp_pwd;

	cout << "-----조회-----\n";
	cout << "계좌번호 입력: ";
	cin >> temp_id;
	cout << '\n';
	cout << "암호 입력: ";
	cin >> temp_pwd;
	cout << '\n';

	for (int i = 0; i < this->nCurrentAccountNum; ++i) {
		Account* curr = this->pAcctArray[i];
		int result = curr->check(temp_id, temp_pwd);

		if (result != AUTHENTIFICATION_FAIL) {
			cout << "현재 잔액: " << result << '\n';
			return;
		}
	}
	cout << "찾는 계좌가 없습니다.\n";
}

void ATMmachine::closeAccount() {
	int temp_id;
	string temp_pwd;

	cout << "-----해지-----\n";
	cout << "계좌번호 입력: ";
	cin >> temp_id;
	cout << '\n';
	cout << "암호 입력: ";
	cin >> temp_pwd;
	cout << '\n';

	for (int i = 0; i < this->nCurrentAccountNum; ++i) {
		Account* curr = this->pAcctArray[i];

		int result = curr->close(temp_id, temp_pwd);

		if (result == AUTHENTIFICATION_FAIL) {
			continue;
		}
		else if (result == AUTHENTIFICATION_SUCCESS) {
			cout << curr->getAcctID() << " 계좌가 해지되었습니다.\n";
			return;
		}
		else {
			cout << "현재 계좌에 잔액이 존재합니다\n";
			return;
		}
	}

	cout << "찾는 계좌가 없습니다.\n";;
}

void ATMmachine::depositMoney() {
	string temp_pwd;
	int money, temp_id;

	cout << "-----입금-----\n";
	cout << "계좌번호 입력: ";
	cin >> temp_id;
	cout << '\n';
	cout << "암호 입력: ";
	cin >> temp_pwd;
	cout << '\n';
	cout << "입금액 입력: ";
	cin >> money;
	cout << '\n';

	if (money <= 0) {
		cout << "입금액이 올바르지 않습니다. (1 이상 정수)\n";
		return;
	}

	for (int i = 0; i < this->nCurrentAccountNum; ++i) {
		Account* curr = this->pAcctArray[i];
		int result = curr->deposit(temp_id, temp_pwd, money);

		if (result != AUTHENTIFICATION_FAIL) {
			cout << "현재 잔액: " << result << '\n' << "입금 완료\n";
			this->nMachineBalance += money;
			return;
		}
	}

	cout << "찾는 계좌가 없습니다.\n";
}

void ATMmachine::widrawMoney() {
	string temp_pwd;
	int money, temp_id;

	cout << "-----출금-----\n";
	cout << "계좌번호 입력: ";
	cin >> temp_id;
	cout << '\n';
	cout << "암호 입력: ";
	cin >> temp_pwd;
	cout << '\n';
	cout << "출금액 입력: ";
	cin >> money;
	cout << '\n';

	if (money <= 0) {
		cout << "출금액이 올바르지 않습니다. (1 이상 정수)\n";
		return;
	}
	if (money > this->nMachineBalance) {
		cout << "ATM이 가지고 있는 금액보다 큽니다. " << this->nMachineBalance << " 원 이하로 입력해주세요.\n";
		return;
	}

	for (int i = 0; i < this->nCurrentAccountNum; ++i) {
		Account* curr = this->pAcctArray[i];
		int result = curr->widraw(temp_id, temp_pwd, money);

		if (result == -2) {
			cout << "현재 잔액보다 적은 금액을 입력하세요.\n";
			return;
		}
		else if (result != AUTHENTIFICATION_FAIL) {
			cout << "현재 잔액 : " << result << '\n' << "출금 완료\n";
			this->nMachineBalance -= money;
			return;
		}
	}

	cout << "찾는 계좌가 없습니다.\n";
}
