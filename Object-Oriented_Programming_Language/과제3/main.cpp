#include <iostream>
#include <string>
#include "Screen.h"
#include "TicketBox.h"
#include "Pay.h"
#include "admin.h"
#include "statistics.h"
using namespace std;

/*

screen.h(추가기능2) -> 추가기능2 디버그 -> admin.h(추가기능 3) -> 추가기능 3 디버그 -> static.h(추가기능4) -> 추가기능4 디버그 -> 전체 디버그

todo - admin 헤더 구현 (좌석 배치와 로그)


Row -> 세로줄 개수
Column -> 가로줄 개수
*/

int main() {
	TUKoreaTBox tBox;
	Screen* screen = NULL;

	bool bScreenMenu = true;
	int select = 0;
	tBox.Initialize(); // 3개의 스크린 객체 생성

	admin_class* admin = NULL;
	log_data* data = NULL;

	while (1) {
		if (bScreenMenu) {
			screen = tBox.selectMenu();
			bScreenMenu = false;

			if (!screen) {
				return 0;
			}
			
			if (admin) {
				delete admin;
			}
			admin = new admin_class(screen, "admin");
		}

		screen->showMovieMenu();
		cout << "메뉴를 선택하세요: ";
		cin >> select; cout << endl;

		switch (select) {
		case 1: // 영화 정보
			screen->showMovieInfo();
			break;
		case 2: // 좌석 현황
			screen->showSeatMap();
			break;
		case 3: // 예약 하기
			data = screen->reserveTicket();

			if (data) {
				admin->data_push(data);
			}
			break;
		case 4: // 예약 결제
			data = screen->Payment();

			if (data) {
				admin->data_push(data);
			}
			break;
		case 7: // 스크린 메인 메뉴
			bScreenMenu = true;
			break;
		case 0: // 사용자 정의 기능
			admin->access();
			break;
		}
	}

	return 0;
}