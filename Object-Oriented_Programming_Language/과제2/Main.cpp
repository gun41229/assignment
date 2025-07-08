#include "ATMmachine.h"

/*

todo

프로젝트 시작전: atm1번 가져오기, 주석달기
0: 기본기능 정비하기 --- (해결)
1: 계좌 이체 기능 구현하기 --- (함수 수정하여 완료)
2: 비밀번호 변경기능 구현하기 --- (완료)
3: atm현금 관리기능, 고객 잔고 총액, 고객 잔고 평균, 최소값, 최대값 출력 --- (심층 디버그 필요)
4: 고객별 잔고별로 정렬하여 출력하기 --- (심층 디버그 필요)

*/

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
			atm.withdrawMoney();
			break;
		case 6:
			atm.transfer();
			break;
		case 7:
			atm.requestSvc();
			break;
		case 8:
			atm.managerMode();
			break;
		case 9:
			cout << "업무를 종료합니다.\n";
			return 0;
		default:
			cout << "번호 확인 후 다시 입력하세요." << endl;
		}
	}
}