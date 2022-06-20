#define _CRT_SECURE_NO_WARNINGS
// 배열 동적할당
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int* pi;
	int i = 0, sum = 0;

	//핵심! 동적할당
	pi = (int*)malloc(5 * sizeof(int));  // int 사이즈 5개 (20바이트)
	if (pi == NULL) {  // null = 할당 못받음
		printf("메모리가 부족합니다.\n");
		exit(1);  // 일반적 에러
	}

	printf("다섯 명의 나이를 입력하세요 > ");
	for (i = 0; i < 5; i++) {
		scanf("%d", &pi[i]); //배열형태로 입력 // &pi[i] == (pi + i)
		sum += pi[i];  // == *(pi + i)
	}

	printf("다섯 명의 평균나이 : %.1lf\n", sum / 5.0);
	free(pi); // 동적메모리 해제, 필수!! 절대 필수!

	//exit(0); // 성공적으로 프로그램 종료 일반적 생략
}