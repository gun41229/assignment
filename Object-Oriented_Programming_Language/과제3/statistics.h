#ifndef STATISTCIS_H
#define STATISTCIS_H
#include "Screen.h"

class Statistics {
public:

	// 추가기능4 - 수입 확인
	static int totalRevenue(Screen* pScreen);

	// 추가기능4 - 판매량 확인
	static int totalSalesCount(Screen* pScreen);
};
#endif
