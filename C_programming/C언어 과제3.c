#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000 // 동적배열의 최대크기 설정

typedef struct { // 데이터들을 용이하게 저장하기위해 Data라는 구조체 선언
	char name[100];
	char address[100];
	char callnumber[100];
} Data;

void set_data(Data* obj, char* val1, char* val2, char* val3) { // 데이터의 값을 저장하기위한 함수
	strncpy(obj->name, val1, 99);
	strncpy(obj->address, val2, 99);
	strncpy(obj->callnumber, val3, 99);
}

char* search(Data** arr, char* name, char* callnum) { // 이름과 전화번호로 주소를 찾는 함수
	int indx = 0;
	while (indx < MAX) {
		if (arr[indx]->name[0] == '\0') return NULL; // 찾지 못하고 배열의 끝을 만난경우 null리턴

		if // 배열에서 이름과 주소가 같은 데이터를 찾은경우 그 데이터의 주소를 리턴
			(strncmp(arr[indx]->name, name, 99) == 0 && strncmp(arr[indx]->callnumber, callnum, 99) == 0) return arr[indx]->address;
		++indx;
	}
	return NULL;
}

int compare(const void* a, const void* b) { // qsort용 비교함수
	Data* dataA = *(Data**)a;
	Data* dataB = *(Data**)b;

	if (dataA->name[0] == '\0' || dataB->name[0] == '\0') return 0;
	return strncmp(dataA->name, dataB->name, 99);
}

void printarr(Data** arr) { // 배열 출력하는 함수
	int indx = 0;
	while (1) {
		if (arr[indx]->name[0] == '\0') return;
		printf("%s %s %s\n", arr[indx]->name, arr[indx]->address, arr[indx]->callnumber);
		++indx;
	}
}



int main() {
	int pushpoint = 0;
	Data** arr = (Data**)malloc(sizeof(Data*) * MAX); // 데이터들을 저장하고 쉽게 사용하기위해 포인터배열 사용
	if (arr == NULL) { // 메모리 할당에 실패한경우 프로그램 종료
		printf("메모리 할당에 실패했습니다.\n");
		free(arr);
		return 1;
	}

	for (int i = 0; i < MAX; ++i) {
		Data* temp = (Data*)malloc(sizeof(Data)); // 초기 데이터들은 더미 데이터로 채워 넣음

		if (temp == NULL) { // 메모리 할당에 실패한경우 프로그램 종료
			printf("메모리 할당에 실패했습니다.\n");
			for (int j = i; j >= 0; --j) {
				free(arr[j]);
			}
			free(arr);
			return 1;
		}

		temp->name[0] = '\0'; // 초기 데이터들의 이름을 비워놓음
		arr[i] = temp;
	}

	while (1) {
		char command;
		command = getchar();
		while (command == '\n') command = getchar();

		if (command == '1') { // 1을 입력한경우 배열을 정렬
			qsort(arr, pushpoint, sizeof(Data*), compare); // stdlib내장함수 qsort사용
			printf("정렬이 완료되었습니다.\n");
		}
		else if (command == '2') { // 2를 입력한경우 검색
			printf("이름과 전화번호를 입력하세요.\n");
			char s_name[100], s_callnum[100];
			scanf_s("%s %s", s_name, 99, s_callnum, 99);

			char* search_res = search(arr, s_name, s_callnum);

			if (search_res == NULL) printf("데이터를 찾을 수 없습니다.\n");
			else {
				printf("주소 : %s\n", search_res);
			}
		}
		else if (command == '3') { // 3을 입력한경우 데이터를 배열에 넣음
			if (pushpoint >= MAX) {
				printf("배열이 가득 찼습니다.\n");
				continue;
			}

			printf("이름, 주소, 전화번호를 입력하세요.\n");
			char p_name[100], p_address[100], p_callnum[100];
			scanf_s("%s %s %s", p_name, 99, p_address, 99, p_callnum, 99);

			Data* newdata = (Data*)malloc(sizeof(Data)); // 새로운 데이터를 동적할당

			if (newdata == NULL) {
				printf("메모리 할당에 실패했습니다.\n");

				for (int i = 0; i < MAX; ++i) {
					free(arr[i]);
				}
				free(arr);

				return 1;
			}

			set_data(newdata, p_name, p_address, p_callnum); // 새로운 데이터를 처리
			free(arr[pushpoint]);
			arr[pushpoint++] = newdata; // 새로운 데이터를 배열에 넣음
		}
		else if (command == '4') { // 4를 입력한경우 배열 출력
			printarr(arr);
		}
		else { // 그 이외의 입력에서 프로그램 종료
			printf("프로그램을 종료합니다.\n");

			for (int i = 0; i < MAX; ++i) {
				free(arr[i]);
			}
			free(arr);
			return 0;
		}
	}

	for (int i = 0; i < MAX; ++i) { // 배열의 내부 데이터를 먼저 메모리 해제
		free(arr[i]);
	}
	free(arr); // 배열 메모리 해제
	return 0;
}