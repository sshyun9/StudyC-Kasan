#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void main(void) {
	int a, b;
	int sum, sub, mvl, inv;

	a = 10; b = 20;
	sum = a + b;
	sub = a - b;
	mvl = a * b;
	inv = -a;

	printf("a=%d, b =%d\n", a, b);
	printf("sum=%d\n", sum);
	printf("sub=%d\n", sub);
	printf("mvl=%d\n", mvl);
	printf("inv=%d\n", inv);

	// 나누기
	double apple;
	int banana, orange;

	apple = 5.0 / 2.0;
	banana = 5 / 2;
	orange = 5 % 2;

	printf("apple=%lf\n", apple);
	printf("banana=%d\n", banana);
	printf("orange=%d\n", orange);

	printf("%d\n", ++a);  // ++a : 11 , a++ : 10  순서 중요.


}