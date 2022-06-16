#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

//void main(void) {
//	int a=10;
//
//	// if문 생략!
//	if (a > 10) {
//		printf("a는 10보다 큼");
//	}
//	else if (a == 10) {
//		printf("a는 10");
//	}
//	else {
//		printf("a는 10보다 작음");
//
//	}
//}

void main(void) {

	char grade;

	printf("학점을 입력하세요 > ");
	scanf("%c", &grade);

	switch (grade)
	{
	case'A':
		printf("대단하네요!");
		break;
	case'B':
		printf("정말 잘하셨습니다!");
		break;
	case'C':
		printf("잘했습니다.");
		break;
	case'D':
		printf("겨우 통과했군요");
		break;
	case'F':
		printf("다음 학기에 또 봐요~");
		break;
	default:   // 다섯가지 케이스가 아닌 경우
		printf("학점을 제대로 입력하세요!!");
		break;
	}
}

//if (grade == 'A') {
//	printf("대단하네요!");
//}
//else if (grade == 'B') {
//	printf("정말 잘하셨습니다!");
//}
//else if (grade == 'C') {
//	printf("잘했습니다.");
//}
//else if (grade == 'D') {
//	printf("겨우 통과했군요");
//}
//else if (grade == 'F') {
//	printf("다음 학기에 또 봐요~");
//}