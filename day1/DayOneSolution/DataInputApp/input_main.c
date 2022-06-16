// 입출력 중 입력
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void main(void) {
	//int a;
	//int res;

	//printf("정수를 입력하세요 > ");
	//// res = 1 정상적으로 입력, 0 잘못된 값 입력
	//res = scanf("%d", &a);  // 콘솔에서 키보드 입력. a 변수의 시작주소!!
	//printf("입력된 값 : %d\n", a);

	//int age;
	//double height;

	//printf("나이와 키를 입력하세요 >");
	//res = scanf("%d%lf", &age, &height);
	//printf("나이는 %d살, 키는 %.1lfcm 입니다.", age, height);

	char grade;
	char name[20];

	printf("학점 입력 >");
	scanf("%c", &grade);
	printf("이름 입력 >");
	scanf("%s, name"); // 문자열, 변수명 자체가 시작주소나타냄
	
	printf("%s 학생의 학점은 %c", name, grade);
}