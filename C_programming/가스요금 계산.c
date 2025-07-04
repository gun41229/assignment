#include <stdio.h>

int main() {
	double cook, heat;
	double cook_fee, heat_fee;

    printf("취사용 도시가스 사용량을 입력하세요 (단위: MJ)\n");
	scanf("%lf", &cook);
	printf("난방용 도시가스 사용량을 입력하세요 (단위: MJ)\n");
	scanf("%lf", &heat);

	cook_fee = (1200 + cook * 22.5593) * 1.1;
	if (heat > 516) {
		heat_fee = (1200 + 516 * 22.5593 + (heat - 516) * 22.5258) * 1.1; // 516MJ 까지는 취사단가 적용
	}
	else {
		heat_fee = (1200 + heat * 22.5593) * 1.1;
	}

	printf("취사용 도시가스 요금: %.0lf 원\n", cook_fee);
	printf("난방용 도시가스 요금: %.0lf 원\n", heat_fee);

	return 0;
}