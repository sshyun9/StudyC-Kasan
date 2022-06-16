// 문자열 학습 main.c
#define _CRT_SECURE_NO_WARNINGS  // strcpy, scanf 등을 사용할 때 전처리기, 도구-옵션-텍스트편집-전처리기에서도 해결가능

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void) {
	const double tax_rate = 0.12; // 세율 초기화 상수화
	char fruit[6] = "apple"; // apple 5글자지만 [6]으로 해야함. 문자열 끝에는 문자가 끝났다는 특수문자 한자리 포함.
	char kfruit[6] = "사과"; // 한글은 하나당 2 사과는 총 5이상 필요 

	printf("%s\n", fruit);
	printf("%s\n", kfruit);

	//fruit = "오렌지" // 위에서 fruit 이미 픽스 했기 때문에 그냥은 못바꿈.
	
	strcpy(fruit, "오렌지");
	printf("%s\n", fruit);

	// tax_rate = 0.15;  // error 상수값은 변경불가

}