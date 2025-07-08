#ifndef ATMMACHINE_H
#define ATMMACHINE_H

#include "Account.h"
#include "CustomerSvc.h"

#define NEGATIVE_ATM_BALANCE -10 // ATM 잔액 부족

class ATMmachine {
private:
	Account** pAcctArray; // 동적 생성된 고객계좌 배열 포인터
	int nMachineBalance; // ATM 잔고
	int nMaxAccountNum; // 동적 생성된 고객계좌 배열 크기
	int nCurrentAccountNum; // 개설된 고객 계좌 수
	string strManagerPassword; // 관리자 비밀번호

public:
	// 계좌 배열크기, ATM 잔고, 관리자 암호 초기화
	ATMmachine(int size, int balance, string password);

	~ATMmachine();

	// ATM 기능 선택 화면
	void displayMenu(); 

	// 계좌 개설
	void createAccount(); 

	// 계좌 조회
	void checkMoney(); 

	// 계좌 해지기능
	void closeAccount();

	// 입금 기능
	void depositMoney();

	// 출금 기능
	void withdrawMoney();

public:
	// 추가 기능1 (계좌 이체 함수)
	void transfer();

	// 추가 기능2 (비밀번호 변경 요청 함수)
	void requestSvc();

private:
	// 추가 기능3 (매니저 암호 확인 함수)
	bool isManager(string password);

	// 추가 기능3 (통계 화면 처리)
	void displayReport();

public:

	// 추가 기능3 (메뉴 8번)
	void managerMode();
};

#endif