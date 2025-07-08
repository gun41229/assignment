#include "statistics.h"

int Statistics::totalRevenue(Screen* pScreen) {
	int total = 0;

	Ticket** arr = pScreen->return_arrptr();
	int col = pScreen->return_col();
	int row = pScreen->return_row();

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (arr[i][j].getCheck() == SEAT_COMPLETION_MARK) {
				total += arr[i][j].getPayAmount();
			}
		}
	}

	return total;
}

int Statistics::totalSalesCount(Screen* pScreen) {
	int total = 0;

	Ticket** arr = pScreen->return_arrptr();
	int col = pScreen->return_col();
	int row = pScreen->return_row();

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (arr[i][j].getCheck() == SEAT_COMPLETION_MARK && arr[i][j].getPayAmount() != 0) {
				++total;
			}
		}
	}

	return total;
}