#ifndef ACCOUNT_H
#define ACCOUNT_H

// string용 헤더 인클루드
#include <iostream>
using namespace std;

#define AUTHENTIFICATION_FAIL -1 // 계정 인증 실패
#define AUTHENTIFICATION_SUCCESS 1 // 계정 인증 성공

class Account {
private:
	int nID; // 계좌 번호 (초기 값 = -1) , 계좌 해지시 초기값으로 변경
	int nBalance; // 잔고 (초기 값 = 0)
	string strAccountName; // 고객 명
	string strPassword; // 계좌 비밀번호

private:
	// 인증 성공 : true(1), 인증 실패 : false(0)
	inline bool authenticate(int id, string passwd); 

public:
	Account();

	// 계좌 개설 함수
	void create(int id, int money, string name, string password);

	// nBalance (잔고) or 인증 실패(AUTHENTIFICATION_FAIL)
	int check(int id, string password);

	// 계좌 번호 읽어오기
	int getAcctID() { return nID; }

	// 계좌 해지 함수 / 인증실패: -1, 해지성공: 계좌번호, 해지실패: 0
	int close(int id, string password);

	// 입금 함수 / 인증실패: -1, 입금성공: 입금 후 잔고
	int deposit(int id, string password, int money);

	// 출금 함수 / 인증실패: -1, 출금성공: 출금 후 잔고, 잔액부족: -2
	int withdraw(int id, string password, int money);

public:
	// 추가 기능1 (계좌 이체 함수) / 송금 성공: true, 송금 실패: false
	bool deposit(int id, int money) { return true; } // 계좌 번호와 이체 금액만으로는 ATMmachine::pAcctArray 에 접근 불가...
	bool deposit(Account* target, int money);

	// 추가 기능2 (비밀번호 변경 함수) / 변경 성공: true, 변경 실패(비밀번호 불일치): false
	bool updatePasswd(string oldPasswd, string newPasswd);

	// 추가 기능3 (잔고 가져오는 함수) / 리턴: 잔고
	int getBalance() {
		return nBalance;
	}

	// 추가 기능3 (이름 가져오는 함수) / 리턴: 이름
	string getAccountName() { return strAccountName; }
};

#endif