#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void main(void) {
	printf("%.2lf\n", (10 + 10.5));
	printf("%lf\n", (double)10);  // 형변환
	printf("%d\n", (int)10.5); // int로 변환하니까 뒤에 .5 소수점 날아감.

	int a = 10;
	float fa = 3.14;
	double da = 3.14;

	printf("int형 변수 크기 : %d\n", sizeof(a));
	printf("float형 변수 크기 : %d\n", sizeof(fa));
	printf("double형 변수 크기 : %d\n", sizeof(da));

	int b = 20, res;
	res = (a > b) ? a : b;
	printf("res = %d\n", res);

	// 비트연산자
	int c = 10;  // 00000000 00000000 00000000 00001010
	int d = 12;  // 00000000 00000000 00000000 00001100

	printf("c & d : %d\n", (c & d));  // 8
	printf("c | d : %d\n", (c & d));  // 14
	printf("c ^ d : %d\n", (c & d));  // 6
	printf("~c : %d\n", ~c);  // -11
	printf("c << 1 : %d\n", c << 1);  // shift 연산  16 + 4 = 20
	printf("c << 2 : %d\n", c << 2);  // 32 + 8 = 40

}