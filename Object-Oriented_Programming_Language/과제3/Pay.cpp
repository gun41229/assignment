#include "Pay.h"
#include <iostream>
using namespace std;

int CardPay::charge(int amount) {
	return amount + amount * this->interest;
}

int BankTransfer::charge(int amount) {
	return amount + amount * this->interest;
}

int MobilePay::charge(int amount) {
	return amount + amount * this->interest;
}