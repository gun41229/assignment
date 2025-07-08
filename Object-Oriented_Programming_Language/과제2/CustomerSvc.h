#ifndef CUSTOMERSVC_H
#define CUSTOMERSVC_H

#include "Account.h"

class CustomerSvc {
	Account** pAccArray;
	int nMaxAccNum;

public:
	CustomerSvc();
	CustomerSvc(Account** acctArray, int nMaxAccountNum);

	// 비밀번호 변경 요청 함수
	void updatePasswdReq();
};

#endif