#include <iostream>
#include "Screen.h"
#include "TicketBox.h"
#include "statistics.h"
using namespace std;

TUKoreaTBox::TUKoreaTBox() {
	this->Initialize();
}

Screen* TUKoreaTBox::selectMenu() {
	cout << "-------------------\n";
	cout << "  상영관 메인 메뉴\n";
	cout << "-------------------\n";
	cout << "1. CJ CGV 솔로 1관\n";
	cout << "2. 롯데시네마 영화 2관\n";
	cout << "3. 메가박스 영화 3관\n";
	cout << "9. 통계 관리\n\n";
	cout << "선택(1~3, 9) 그외 종료\n\n";

	int num;
	cin >> num;

	switch (num) {
	case 1:
		return this->pCGVScreen;
	case 2:
		return this->pLotteCinemaScreen;
	case 3:
		return this->pMegaBoxScreen;
	case 9:
		this->manage();

		return NULL;
	default:
		return NULL;
	}
}

void TUKoreaTBox::Initialize() {
	// Screen(영화제목, 티켓가격, 좌석(nRowMax), 좌석(nColMax))
	this->pCGVScreen = new CGVScreen("아이언맨 2", 15000, 8, 8);
	this->pLotteCinemaScreen = new LotteCinemaScreen("어벤져스: 인피니티워", 12000, 10, 10);
	this->pMegaBoxScreen = new MegaboxScreen("어벤져스: 엔드게임", 20000, 8, 8);
}

TUKoreaTBox::~TUKoreaTBox() {
	delete this->pCGVScreen;
	delete this->pLotteCinemaScreen;
	delete this->pMegaBoxScreen;
}

void TUKoreaTBox::manage() {
	cout << "-------------------\n";
	cout << " 관리자 메뉴\n";
	cout << "-------------------\n";
	cout << "관리자 비밀번호 입력: ";

	string password;
	cin >> password;
	cout << "\n";

	if (password == TICKETBOX_MANAGER_PWD) {
		cout << "1. CJ CGV 솔로 1관 결제 금액: " << Statistics::totalRevenue(this->pCGVScreen) << '\n';
		cout << "2. 롯데시네마 상영관 결제 금액: " << Statistics::totalRevenue(this->pLotteCinemaScreen) << '\n';
		cout << "3. 메가박스 상영관 결제 금액: " << Statistics::totalRevenue(this->pMegaBoxScreen) << '\n';
		cout << "4. 전체 티켓 판매량: " << Statistics::totalSalesCount(this->pCGVScreen) + Statistics::totalSalesCount(this->pLotteCinemaScreen) + Statistics::totalSalesCount(this->pMegaBoxScreen) << '\n';
	}
	else {
		cout << "비밀번호가 틀렸습니다.\n";
		return;
	}
}