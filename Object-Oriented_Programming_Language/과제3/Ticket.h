#ifndef TICKET_H
#define TICKET_H

#define SEAT_EMPTY_MARK '-'
#define SEAT_RESERVED_MARK 'R'
#define SEAT_COMPLETION_MARK '$'

class Ticket {
	// 좌석 행 (세로줄)
	int nRow;

	// 좌석 열 (가로줄)
	int nCol;

	// 예약 여부
	char charCheck; 
	
	// 예약 번호
	int nReservedID; 

	// 결제 금액
	int nPayAmount;

	// 결제 수단
	int nPayMethod;

public:

	Ticket() { this->charCheck = SEAT_EMPTY_MARK; this->nPayAmount = 0; };

	// 예약여부 설정
	void setCheck(char check) { charCheck = check; }

	// 예약여부 가져오기
	char getCheck() { return charCheck; }

public:

	// 추가기능1 - 좌석 번호 저장
	void setSeat(int row, int col) {
		this->nRow = row; this->nCol = col;
	}

	// 추가기능1 - 좌석 예약 번호 저장
	void setReservedID(int reserved) { this->nReservedID = reserved; }

	// 추가기능1 - 좌석 예약 번호 가져오기
	int getReservedID() { return this->nReservedID; }

public:

	// 추가기능2 - 결제한 가격 설정
	void setPayAmount(int amount) { this->nPayAmount = amount; }

	// 추가기능2 - 결제한 가격 가져오기
	int getPayAmount() { return this->nPayAmount; }

	// 추가기능2 - 결제 방법 설정
	void setPayMethod(int method) { this->nPayMethod = method; }
};

#endif