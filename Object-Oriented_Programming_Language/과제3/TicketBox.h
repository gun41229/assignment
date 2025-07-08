#ifndef TICKETBOX_H
#define TICKETBOX_H
#define TICKETBOX_MANAGER_PWD "admin"

class TicketBox {
public:

	// 상영관 선택 메뉴
	virtual Screen* selectMenu() { return NULL; }
	void Initialize() {}
};

class TUKoreaTBox : public TicketBox {
	CGVScreen* pCGVScreen;
	LotteCinemaScreen* pLotteCinemaScreen;
	MegaboxScreen* pMegaBoxScreen;
public:
	TUKoreaTBox();
	~TUKoreaTBox();

	// 메인메뉴 나오는 함수
	Screen* selectMenu();

	void Initialize();

public:

	// 추가기능 4 - 관리 함수
	void manage();
};

#endif