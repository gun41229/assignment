#ifndef ATMMACHINE_H
#define ATMMACHINE_H

#include <iostream>
#include "Account.h"
using namespace std;

#define NEGATIVE_ATM_BALANCE -10 // ATM 잔액 부족

class ATMmachine {
private:
	Account** pAcctArray; // 동적 생성된 고객계좌 배열 포인터
	int nMachineBalance; // ATM 잔고
	int nMaxAccountNum; // 동적 생성된 고객계좌 배열 크기
	int nCurrentAccountNum; // 개설된 고객 계좌 수
	string strManagerPassword; // 관리자 비밀번호
public:
	ATMmachine(int size, int balance, string password); // 계좌 배열크기, ATM 잔고, 관리자 암호 초기화
	~ATMmachine();
	void displayMenu(); // ATM 기능 선택 화면
	void createAccount(); // 계좌 개설
	void checkMoney(); // 계좌 조회
public:
	// 추가기능 1
	void closeAccount();

	// 추가기능 2
	void depositMoney();

	// 추가기능 3
	void widrawMoney();
};

#endif