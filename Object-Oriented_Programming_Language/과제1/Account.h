#ifndef ACCOUNT_H
#define ACCOUNT_H

using std::string;

#define AUTHENTIFICATION_FAIL -1 // 계정 인증 실패
#define AUTHENTIFICATION_SUCCESS 1 // 계정 인증 성공

class Account {
private:
	int nID; // 계좌 번호 (초기 값 = -1) , 계좌 해지시 초기값으로 변경
	int nBalance; // 잔고 (초기 값 = 0)
	string strAccountName; // 고객 명
	string strPassword; // 계좌 비밀번호
private:
	inline bool authenticate(int id, string passwd); // 인증 성공 : true(1), 인증 실패 : false(0)
public:
	Account();
	void create(int id, int money, string name, string password); // 계좌 개설
	int check(int id, string password); // return 값 : nBalance (잔고) or 인증 실패(AUTHENTIFICATION_FAIL)
	int getAcctID() { return nID; } // 계좌 번호 읽어오기
public:
	// 추가기능 1
	int close(int id, string password);
	
	// 추가기능 2
	int deposit(int id, string password, int money);

	// 추가기능 3
	int widraw(int id, string password, int money);
};

#endif