#include <random>
#include "ATMmachine.h"
#include "Statistics.h"

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
	cout << " 6. 계좌 이체\n";
	cout << " 7. 고객 센터\n";
	cout << " 8. 고객 관리\n";
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
	uniform_int_distribution<int> dist(200, 900); // 랜덤 디바이스 생성

	int temp_id = dist(rng);
	int flag = 0; // 중복 방지용 플래그 생성

	// 계좌 번호가 중복되지 않도록 계좌 번호를 조정
	while (1) { 
		for (int i = 0; i < this->nCurrentAccountNum; ++i) {
			Account* check = this->pAcctArray[i];

			if (check->getAcctID() == temp_id) {
				flag = 1;
			}
		}

		if (flag == 0) {
			break;
		}
		else {
			flag = 0;
			temp_id = dist(rng);
		}
	}

	Account* new_alloc = new Account;
	new_alloc->create(temp_id, 0, temp_name, temp_pwd);
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
		else if (result == 0) {
			cout << "현재 계좌에 잔액이 존재합니다\n";
			return;
		}
		else {
			cout << result << "번 계좌가 해지되었습니다.\n";
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

void ATMmachine::withdrawMoney() {
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
		int result = curr->withdraw(temp_id, temp_pwd, money);

		if (result == AUTHENTIFICATION_FAIL) {
			continue;
		}
		else if (result == -2) {
			cout << "현재 잔액보다 적은 금액을 입력하세요.\n";
			return;
		}
		else {
			cout << "현재 잔액 : " << result << '\n' << "출금 완료\n";
			this->nMachineBalance -= money;
			return;
		}
	}

	cout << "찾는 계좌가 없습니다.\n";
}

void ATMmachine::transfer() {
	string temp_pwd;
	int money, temp_id, target_id;

	cout << "-----이체-----\n";
	cout << "계좌번호 입력: ";
	cin >> temp_id;
	cout << '\n';
	cout << "암호 입력: ";
	cin >> temp_pwd;
	cout << '\n';
	cout << "이체 계좌 입력: ";
	cin >> target_id;
	cout << '\n';
	cout << "이체 금액 입력: ";
	cin >> money;
	cout << '\n';

	Account* target_acc = nullptr;
	for (int i = 0; i < this->nCurrentAccountNum; ++i) {
		Account* curr = this->pAcctArray[i];

		if (curr->getAcctID() == target_id) {
			target_acc = curr;
		}
	}

	if (target_acc == nullptr) {
		cout << "목표 계좌가 존재하지 않습니다.\n";
		return;
	}

	for (int i = 0; i < this->nCurrentAccountNum; ++i) {
		Account* curr = this->pAcctArray[i];

		// check함수를 이용하여 인증을함 (Account::authenticate 함수가 private이기 때문)
		if (curr->check(temp_id, temp_pwd) == AUTHENTIFICATION_FAIL) {
			continue;
		}
		else {
			bool result = curr->deposit(target_acc, money);

			if (result == true) {
				cout << "현재 금액: " << curr->check(temp_id, temp_pwd) << '\n';
				cout << "이체 성공\n";
			}
			else {
				cout << "잔액 부족\n";
			}

			return;
		}
	}

	cout << "인증이 실패하였습니다.\n";
}

void ATMmachine::requestSvc() {
	CustomerSvc* req = new CustomerSvc(this->pAcctArray, this->nCurrentAccountNum);

	req->updatePasswdReq();

	delete req;
}

bool ATMmachine::isManager(string password) {
	if (password == this->strManagerPassword) {
		return true;
	}
	else {
		return false;
	}
}

void ATMmachine::displayReport() {
	Account** arr = this->pAcctArray;
	int size = this->nCurrentAccountNum;

	cout << "-------------\n";
	cout << "ATM 현재 잔고: " << this->nMachineBalance << '\n';
	
	if (size == 0) {
		cout << "고객이 0명이라 잔고, 총액, 평균, 최소, 최대, 목록이 표시되지 않습니다.\n";
		return;
	}
	else {
		cout << "고객 잔고 총액: " << Statistics::sum(arr, size) << '(' << size << "명)\n";
		cout << "고객 잔고 평균: " << Statistics::average(arr, size) << '\n';
		cout << "고객 잔고 최소: " << Statistics::min(arr, size) << '\n';
		cout << "고객 잔고 최대: " << Statistics::max(arr, size) << '\n';
		cout << "----------------\n";
		cout << "- 고객 계좌 목록 -\n";
		cout << "----------------\n";

		Statistics::sort(arr, size);

		for (int i = 0; i < size; ++i) {
			Account* curr = arr[i];

			cout << i + 1 << ".  " << curr->getAccountName() << "    " << curr->getAcctID() << "    " << curr->getBalance() << "원" << '\n';
		}
	}
}

void ATMmachine::managerMode() {
	string pwd;

	cout << "----- 관리 -----\n";
	cout << "관리자 비밀번호 입력: ";
	cin >> pwd;
	cout << '\n';

	if (isManager(pwd) == true) {
		cout << "관리자 입니다.\n";
		displayReport();
	}
	else {
		cout << "비밀번호가 맞지 않습니다.\n";
	}
}