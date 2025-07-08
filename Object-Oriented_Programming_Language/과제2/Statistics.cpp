#include "Statistics.h"

int Statistics::sum(Account** pArray, int size) {
	int result = 0;

	for (int i = 0; i < size; ++i) {
		Account* curr = pArray[i];

		result += curr->getBalance();
	}

	return result;
}

int Statistics::average(Account** pArray, int size) {
	return sum(pArray, size) / size;
}

int Statistics::min(Account** pArray, int size) {
	int result = 2147483647;
	for (int i = 0; i < size; ++i) {
		Account* curr = pArray[i];
		
		int curr_balance = curr->getBalance();

		if (curr_balance < result) {
			result = curr_balance;
		}
	}

	return result;
}

int Statistics::max(Account** pArray, int size) {
	int result = (-2147483647 - 1);
	for (int i = 0; i < size; ++i) {
		Account* curr = pArray[i];

		int curr_balance = curr->getBalance();

		if (curr_balance > result) {
			result = curr_balance;
		}
	}

	return result;
}

void Statistics::sort(Account** pArray, int size) {
	for (int i = 0; i < size - 1; ++i) {
		for (int j = i + 1; j < size; ++j) {

			Account* first = pArray[i];
			Account* second = pArray[j];

			if (first->getBalance() < second->getBalance()) {
				Account* temp = first;
				pArray[i] = pArray[j];
				pArray[j] = temp;
			}
		}
	}
}
