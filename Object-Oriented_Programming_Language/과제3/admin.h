#ifndef ADMIN_H
#define ADMIN_H
#include <vector>
#include <iostream>
#include "Screen.h"
using namespace std;

class admin_class {
	Ticket** ticket_arr;

	int col, row;

	vector<log_data*> log_arr;

	string admin_password;

public:
	admin_class(Screen* screen, string pwd) {
		this->ticket_arr = screen->return_arrptr();
		this->col = screen->return_col();
		this->row = screen->return_row();
		this->admin_password = pwd;
	}

	~admin_class() { // 영화관 변경시 로그데이터 삭제
		for (auto& log : log_arr) {
			delete log;
		}
		log_arr.clear();
	}

	void access();

	void seat_random_spread();

	void set_seat();

	void show_log();

	void data_push(log_data* val);
};

#endif