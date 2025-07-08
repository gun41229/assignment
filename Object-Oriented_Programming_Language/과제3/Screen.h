#ifndef SCREEN_H
#define SCREEN_H
#include "Ticket.h"
#include <iostream>

using namespace std;

class admin_class; // 추가기능 3 전방선언 (구현은 admin.cpp)
class log_data { // 추가기능 3용 로그데이터 클래스

	int reserved_id;

	int pay_amount;

	int pay_method;

	string name;

	int col, row;

public:

	void set(int rsrved_id, int pay_amnt, int pay_mthd, string set_name, int col, int row) {
		this->reserved_id = rsrved_id;
		this->pay_amount = pay_amnt;
		this->pay_method = pay_mthd;
		this->name = set_name;
		this->col = col;
		this->row = row;
	}

	inline int get_rsrv_id() { return this->reserved_id; };

	inline int get_payamnt() { return this->pay_amount; };

	inline int get_paymthd() { return this->pay_method; };

	inline string get_name() { return this->name; };

	inline int get_col() { return this->col; };

	inline int get_row() { return this->row; };
};

class Screen {
protected:

	// 티켓 가격
	int nTicketPrice;

	// 좌석 행(세로)최대 값
	int nRowMax;

	// 좌석 열(가로)최대 값
	int nColMax;

	// 발급된 마지막 예약 번호
	int nCurrentReservedId;

	// 스크린 좌석에 대한 티켓 배열
	Ticket** pSeatArray;

	// 스크린 상영중인 영화 제목
	string strMovieName;

public:
	Screen(string name, int price, int row, int col);
	~Screen();

	// 좌석 예약 여부 출력
	void showSeatMap();

	// 영화 예매 메뉴
	virtual void showMovieMenu() = 0;

	// 영화 소개 정보
	virtual void showMovieInfo() = 0;

public:

	// 추가기능1 - 좌석 예약하기
	log_data* reserveTicket();


public:

	// 추가기능2 - 영화의 티켓가격 가져오기
	int getTicketPrice() { return this->nTicketPrice; }

	// 추가기능2 - 결제하기
	log_data* Payment();

public:

	// 추가기능3, 4겸용 - admin 클래스에게 정보를 제공하는 함수
	Ticket** return_arrptr() { return this->pSeatArray; };

	int return_row() { return this->nRowMax; };

	int return_col() { return this->nColMax; };

};

class CGVScreen : public Screen {
public:
	CGVScreen(string name, int price, int row, int col) : Screen(name, price, row, col) {}
	void showMovieInfo();
	void showMovieMenu();
};

class LotteCinemaScreen : public Screen {
public:
	LotteCinemaScreen(string name, int price, int row, int col) : Screen(name, price, row, col) {}
	void showMovieMenu();
	void showMovieInfo();
};

class MegaboxScreen : public Screen {
public:
	MegaboxScreen(string name, int price, int row, int col) : Screen(name, price, row, col) {}
	void showMovieInfo();
	void showMovieMenu();
};

#endif