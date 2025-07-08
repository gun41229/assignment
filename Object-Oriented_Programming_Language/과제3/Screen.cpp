#include <iostream>
#include <string>
#include "Screen.h"
#include "Pay.h"
using namespace std;

Screen::Screen(string name, int price, int row, int col) {
	this->nCurrentReservedId = 100;
	this->strMovieName = name;
	this->nTicketPrice = price;
	this->nRowMax = row;
	this->nColMax = col;

	this->pSeatArray = new Ticket* [row];
	for (int i = 0; i < row; ++i) {
		pSeatArray[i] = new Ticket[col];
	}
}

Screen::~Screen() {
	for (int i = 0; i < this->nRowMax; ++i) {
		delete[] this->pSeatArray[i];
	}
	delete this->pSeatArray;
}

void Screen::showSeatMap() {
	cout << "\n   \t[ 좌석 예약 현황 ]\n";
	cout << "   \t";
	for (int i = 0; i < this->nColMax; ++i) {
		cout << '[' << i + 1 << "] ";
	}
	cout << '\n';

	for (int i = 0; i < this->nRowMax; ++i) {
		cout << '[' << i + 1 << "]\t";
		for (int j = 0; j < this->nColMax; ++j) {
			cout << '[' << this->pSeatArray[i][j].getCheck() << "] ";
		}
		cout << '\n';
	}

	cout << '\n';
}




void CGVScreen::showMovieInfo() {
	cout << "--------------------\n";
	cout << " [ " << this->strMovieName << " ] \n";
	cout << "--------------------\n";
	cout << "영화관: CGV\n";
	cout << "주인공: 로버트 다우니 주니어\n";
	cout << "줄거리: 세계 최강의 무기업체를 이끄는 CEO로 화려한 삶을 살아가던 토니 스타크. 기자회견을 통해 자신이 아이언맨이라고 정체를 밝힌 이후...\n";
	cout << "가격: " << this->nTicketPrice << "\n\n";
}

void CGVScreen::showMovieMenu() {
	cout << "---------------------\n";
	cout << " 메뉴: 아이언맨 2\n";
	cout << "---------------------\n";
	cout << " 1. 영화 정보\n";
	cout << " 2. 예약 현황\n";
	cout << " 3. 예약 하기\n";
	cout << " 4. 예약 결제\n";
	cout << " 7. 메인메뉴 이동\n\n";
}




void LotteCinemaScreen::showMovieInfo() {
	cout << "--------------------\n";
	cout << " [ " << this->strMovieName << " ] \n";
	cout << "--------------------\n";
	cout << "영화관: LotteCinema\n";
	cout << "주인공: 로버트 다우니 주니어, 조시 브롤린, 크리스 에반스, 크리스 햄스워스...\n";
	cout << "줄거리: 어벤져스는 역대 최강의 빌런 타노스에 맞서기 위해 인류의 운명이 걸린 인피니티 스톤을 찾기 위한 험난한 여정을 보내는데...\n";
	cout << "가격: " << this->nTicketPrice << "\n\n";
}

void LotteCinemaScreen::showMovieMenu() {
	cout << "---------------------\n";
	cout << " 메뉴: 어벤져스: 인피니티 워\n";
	cout << "---------------------\n";
	cout << " 1. 영화 정보\n";
	cout << " 2. 예약 현황\n";
	cout << " 3. 예약 하기\n";
	cout << " 4. 예약 결제\n";
	cout << " 7. 메인메뉴 이동\n\n";
}




void MegaboxScreen::showMovieInfo() {
	cout << "--------------------\n";
	cout << " [ " << this->strMovieName << " ] \n";
	cout << "--------------------\n";
	cout << "영화관: Megabox\n";
	cout << "주인공: 로버트 다우니 주니어, 크리스 에반스, 스칼렛 요한슨, 크리스 햄스워스\n";
	cout << "줄거리: 인피니티 워 전쟁 후 남아 있던 어벤저스는 그런 그들의 모습을 보게 된다. 마지막으로 지구를 살리려 모든 것을 건 타노스와 최후의 전쟁을 치른다.\n";
	cout << "가격: " << this->nTicketPrice << "\n\n";
}

void MegaboxScreen::showMovieMenu() {
	cout << "---------------------\n";
	cout << " 메뉴: 어변져스: 엔드게임\n";
	cout << "---------------------\n";
	cout << " 1. 영화 정보\n";
	cout << " 2. 예약 현황\n";
	cout << " 3. 예약 하기\n";
	cout << " 4. 예약 결제\n";
	cout << " 7. 메인메뉴 이동\n\n";
}

// 추가기능1 - 예약하기
log_data* Screen::reserveTicket() {
	int t_row, t_col;

	cout << "\n  [ 좌석 예약 ]\n";
	cout << "좌석 행 번호 입력(1 ~ " << this->nRowMax << ") : ";
	cin >> t_row;
	cout << "좌석 열 번호 입력(1 ~ " << this->nColMax << ") : ";
	cin >> t_col;

	if (!(1 <= t_row && t_row <= this->nRowMax && 1 <= t_col && t_col <= this->nColMax)) {
		cout << "범위 안의 정수를 입력하세요\n";
		return NULL;
	}

	--t_row; --t_col; // 0-base_index로 맞추기

	if (this->pSeatArray[t_row][t_col].getCheck() != SEAT_EMPTY_MARK) {
		cout << "자리가 비어있지 않습니다.\n";
		return NULL;
	}

	cout << "행 [ " << t_row + 1 << " ] 열 [ " << t_col + 1 << " ] " << this->nCurrentReservedId << " 예약 번호로 접수되었습니다.\n";
	this->pSeatArray[t_row][t_col].setSeat(t_row, t_col);
	this->pSeatArray[t_row][t_col].setReservedID(this->nCurrentReservedId);
	this->pSeatArray[t_row][t_col].setCheck(SEAT_RESERVED_MARK);

	// 추가기능 3을 위한 데이터 반출 작업
	log_data* data = new log_data;
	data->set(this->nCurrentReservedId, 0, 0, "", t_col, t_row);

	++nCurrentReservedId;

	return data;
}

// 추가기능2 - 결제하기
log_data* Screen::Payment() {
	int t_rsrv_num;

	cout << "예약 번호 입력: ";
	cin >> t_rsrv_num;

	int t_col, t_row = -1;

	for (int i = 0; i < this->nRowMax; ++i) {
		for (int j = 0; j < this->nColMax; ++j) {
			if (this->pSeatArray[i][j].getReservedID() == t_rsrv_num) {

				if (this->pSeatArray[i][j].getCheck() == SEAT_RESERVED_MARK) { // 예약한 경우
					t_col = j;
					t_row = i;
				}
				else { // 예약 번호는 같은데 결제한 경우
					t_row = -2;
				}
				
				break;
			}
		}
	}

	if (t_row == -1) {
		cout << "예약 번호가 존재하지 않습니다.\n";
		return NULL;
	}
	else if (t_row == -2) {
		cout << "이미 결제된 자리입니다.\n";
		return NULL;
	}

	int paymethod;

	cout << "----------------------------\n";
	cout << "        결제 방식 선택\n";
	cout << "----------------------------\n";
	cout << " 1. 모바일 결제\n";
	cout << " 2. 은행 이체 결제\n";
	cout << " 3. 카드 결제\n\n";
	cout << " 결제 방식 입력(1~3): ";
	cin >> paymethod;

	string t_identification_num;
	string t_name;
	int t_paymethod;
	Pay* t_payptr;

	switch (paymethod) {
	case 1:
		cout << " [ 모바일 결제 ]\n";
		cout << "핸드폰 번호 입력(11자리수 ): ";
		cin >> t_identification_num;
		cout << "이름 입력: ";
		cin >> t_name;

		t_paymethod = MOBILE_PHONE_PAYMENT;
		t_payptr = new MobilePay(MOBILE_PHONE_INTEREST_RATE);

		cout << "TUKOREA 모바일 결제가 완료되었습니다. :";
		break;
	case 2:
		cout << " [ 은행 결제 ]\n";
		cout << "은행 번호 입력(12자리 수): ";
		cin >> t_identification_num;
		cout << "이름 입력: ";
		cin >> t_name;

		t_paymethod = BANK_TRANSFER_PAYMENT;
		t_payptr = new BankTransfer(BANK_TRANSFER_INTEREST_RATE);

		cout << "TUKOREA 은행 결제가 완료되었습니다. :";
		break;
	case 3:
		cout << " [ 신용카드 결제 ]\n";
		cout << "카드 번호 입력(12자리 수): ";
		cin >> t_identification_num;
		cout << "이름 입력: ";
		cin >> t_name;

		t_paymethod = CREDIT_CARD_PAYMENT;
		t_payptr = new CardPay(CREDIT_CARD_INTEREST_RATE);

		cout << "TUKOREA 신용카드 결제가 완료되었습니다. :";
		break;
	default:
		cout << "범위가 올바르지 않습니다.\n";
		return NULL;
	}

	int t_price = t_payptr->charge(this->getTicketPrice());
	cout << t_price << '\n';

	// 추가기능 3을 위한 데이터 반출작업
	Ticket* t_seat = &this->pSeatArray[t_row][t_col];
	t_seat->setCheck(SEAT_COMPLETION_MARK);
	t_seat->setPayAmount(t_price);
	t_seat->setPayMethod(t_paymethod);

	log_data* data = new log_data;
	data->set(0, t_price, t_paymethod, t_name, t_col, t_row); // 결제작업은 예약번호 0으로 처리

	return data;
}

