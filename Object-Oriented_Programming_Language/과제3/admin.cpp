#include "admin.h"
#include <ctime>
#include <algorithm>

void admin_class::access() {
	string t_pwd;

	cout << "--------------------\n";
	cout << " 사용자 정의 기능\n";
	cout << "--------------------\n\n";
	cout << "사용자 정의 기능의 비밀번호를 입력하세요: \n";

	cin >> t_pwd;

	if (t_pwd != this->admin_password) {
		cout << "비밀번호가 다릅니다.\n";
		return;
	}

	cout << "\n1. 좌석 관리 기능\n";
	cout << "2. 로그 관리 기능\n";

	int command;
	cin >> command;

	switch (command) {
	case 1:
		cout << "\n1. 좌석 일괄 처리\n";
		cout << "2. 비율에 따른 좌석 처리\n";

		int command2;
		cin >> command2;

		if (command2 == 1) {
			this->set_seat();
		}
		else if (command2 == 2) {
			this->seat_random_spread();
		}
		else {
			cout << "범위를 정확히 입력해 주세요\n";
		}

		return;
	case 2:
		this->show_log();

		return;
	default:
		return;
	}
}

void admin_class::seat_random_spread() {
	double ratio;

	cout << "\n비율을 입력하세요 (0~100)사이의 소수: ";
	cin >> ratio;

	if (0 > ratio || ratio > 100) {
		cout << "범위를 초과하였습니다.\n";
		return;
	}

	pair<int, int>* t_index; // 자리 위치 저장할 임시 변수
	vector<pair<int, int>*> index_array; // 자리 위치 저장하는 컨테이너(벡터)

	for (int i = 0; i < this->row; ++i) {
		for (int j = 0; j < this->col; ++j) {
			t_index = new pair<int, int>(j, i);

			index_array.push_back(t_index);
		}
	}

	srand(time(nullptr));
	random_shuffle(index_array.begin(), index_array.end());

	int cell = this->col * this->row * ratio / 100;
	for (int i = 0; i < cell; ++i) { // 비율에 맞춰서 임의의 위치에 자리 설정
		t_index = index_array[i];

		int t_col = t_index->first, t_row = t_index->second;

		this->ticket_arr[t_row][t_col].setCheck(SEAT_COMPLETION_MARK);
	}

	for (auto it = index_array.begin(); it != index_array.end(); ++it) {
		delete* it; // 동적 메모리 해제
	}
}

void admin_class::set_seat() {
	char mark;
	int command;

	cout << "\n1. 좌석 비우기\n";
	cout << "2. 좌석 예약 상태로 만들기\n";
	cout << "3. 좌석 결제 완료 상태로 만들기\n";

	cin >> command;

	switch (command) {
	case 1:
		mark = SEAT_EMPTY_MARK;
		break;
	case 2:
		mark = SEAT_RESERVED_MARK;
		break;
	case 3:
		mark = SEAT_COMPLETION_MARK;
		break;
	default:
		cout << "정확한 범위를 입력해 주세요\n";
		return;
	}

	for (int i = 0; i < this->row; ++i) {
		for (int j = 0; j < this->col; ++j) {
			this->ticket_arr[i][j].setCheck(mark);
		}
	}
}

void admin_class::show_log() {
	cout << "-------------------\n";
	cout << " 로그 확인\n";
	cout << "-------------------\n";

	int f_rsvid = NULL;
	string f_paymthd = "";
	string f_name = "";

	while (1) {
		cout << "1. 로그 조회\n";
		cout << "2. 필터 설정\n";
		cout << "3. 필터 초기화\n";
		cout << "그외 로그 조회 종료\n";

		int command;
		cin >> command;
		cout << '\n';

		if (command == 1) {
			for (auto it = this->log_arr.begin(); it != this->log_arr.end(); ++it) {
				log_data* curr = *it;

				int c_rsrv_id = curr->get_rsrv_id();
				int c_payamnt = curr->get_payamnt();
				string c_name = curr->get_name();
				int c_col = curr->get_col();
				int c_row = curr->get_row();
				int t_paymthd = curr->get_paymthd();
				string c_paymthd;

				switch (t_paymthd) {
				case 1:
					c_paymthd = "모바일 결제";
					break;
				case 2:
					c_paymthd = "은행 결제";
					break;
				case 3:
					c_paymthd = "카드 결제";
					break;
				default:
					c_paymthd = "";
					break;
				}

				if ((f_rsvid == NULL || (f_rsvid == c_rsrv_id)) || c_rsrv_id == NULL) {
					if (c_rsrv_id == NULL && (f_paymthd == "" || (f_paymthd == c_paymthd))) { // 예약번호가 없는경우(결제한 경우)
						cout << c_row + 1 << "행 " << c_col + 1 << "열에 " << c_name << " 님이 " << c_paymthd << " 로 " << c_payamnt << " 원 결제했습니다.\n";
					}
					else if (c_rsrv_id == f_rsvid || f_rsvid == NULL) { // 예약번호가 있는경우(예약한 경우)
						cout << c_row + 1 << "행 " << c_col + 1 << "열에 " << c_rsrv_id << " 번 으로 예약되었습니다.\n";
					}
				}
			}
			cout << "\n";
		}
		else if (command == 2) {

			cout << "- 예약 번호 필터 -\n";
			cout << "예약 번호 입력: ";
			cin >> f_rsvid;
			cout << '\n';

			cout << "- 결제 방법 필터 -\n";
			cout << "1. 모바일결제\n";
			cout << "2. 은행결제\n";
			cout << "3. 카드결제\n";
			cout << "결제 방법 입력: ";

			int t_paymthd;
			cin >> t_paymthd;
			cout << '\n';

			switch (t_paymthd) {
			case 1:
				f_paymthd = "모바일 결제";
				break;
			case 2:
				f_paymthd = "은행 결제";
				break;
			case 3:
				f_paymthd = "카드 결제";
				break;
			default:
				f_paymthd = "";
				break;
			}

			cout << "- 이름 필터 -\n";
			cout << "이름 입력: ";
			cin >> f_name;
			cout << '\n';

			if (f_name == "0") { // 이름 필터 초기화
				f_name = "";
			}
		}
		else if (command == 3) {
			f_rsvid = NULL;
			f_paymthd = "";
			f_name = "";
		}
		else {
			return;
		}
	}
}

void admin_class::data_push(log_data* val) {
	this->log_arr.push_back(val);
}