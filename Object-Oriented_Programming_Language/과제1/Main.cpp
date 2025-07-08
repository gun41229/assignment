#include <iostream>
#include "ATMmachine.h"

int main() {

	int select;
	// 고객 수(100명), ATM 잔금 초기화, 관리자 암호

	ATMmachine atm(100, 50000, "admin");
	while (1) {
		atm.displayMenu();
		cout << "메뉴를 선택하세요 : ";
		cin >> select;
		cout << endl;

		switch (select) {
		case 1:
			atm.createAccount();
			break;
		case 2:
			atm.checkMoney();
			break;
		case 3:
			atm.closeAccount();
			break;
		case 4:
			atm.depositMoney();
			break;
		case 5:
			atm.widrawMoney();
			break;
		case 9:
			cout << "업무를 종료합니다.\n";
			return 0;
		default:
			cout << "번호 확인 후 다시 입력하세요." << endl;
		}
	}
}