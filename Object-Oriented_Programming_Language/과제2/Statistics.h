#ifndef STATICS_H
#define STATICS_H

#include "Account.h"

class Statistics {
public:
	// 계좌 잔고 총합
	static int sum(Account** pArray, int size); 

	// 계좌 잔고 평균
	static int average(Account** pArray, int size);

	// 계좌 잔고 최소 / 0명일때는 atm 에서 처리
	static int min(Account** pArray, int size);

	// 계좌 잔고 최고 / 0명일때는 atm 에서 처리
	static int max(Account** pArray, int size); 

	// 내림 차순 정렬 (편리한 버블정렬 이용)
	static void sort(Account** pArray, int size);
};

#endif