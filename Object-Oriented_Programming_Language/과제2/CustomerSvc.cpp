#include "CustomerSvc.h"

CustomerSvc::CustomerSvc() {
	this->nMaxAccNum = 0;
	this->pAccArray = NULL;
}

CustomerSvc::CustomerSvc(Account** acctArray, int nMaxAccountNum) {
	this->nMaxAccNum = nMaxAccountNum;
	this->pAccArray = acctArray;
}

void CustomerSvc::updatePasswdReq() {
	int id;
	string old_pwd, new_pwd;
	
	cout << "--- 비밀번호 변경 ---\n";
	cout << "계좌번호 입력: ";
	cin >> id;
	cout << '\n';
	cout << "기존 비밀번호 입력: ";
	cin >> old_pwd;
	cout << '\n';
	cout << "신규 비밀번호 입력: ";
	cin >> new_pwd;
	cout << '\n';

	for (int i = 0; i < this->nMaxAccNum; ++i) {
		Account* curr = this->pAccArray[i];

		if (curr->getAcctID() != id) {
			continue;
		}
		else {
			bool result = curr->updatePasswd(old_pwd, new_pwd);

			if (result == true) {
				cout << "비밀번호 변경 완료\n";
			}
			else {
				cout << "비밀번호가 일치하지 않습니다.\n";
			}

			return;
		}
	}

	cout << "찾으시는 계좌가 없습니다.\n";
}