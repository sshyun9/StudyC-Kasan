#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void main(void) {
	printf("%.2lf\n", (10 + 10.5));
	printf("%lf\n", (double)10);  // ����ȯ
	printf("%d\n", (int)10.5); // int�� ��ȯ�ϴϱ� �ڿ� .5 �Ҽ��� ���ư�.

	int a = 10;
	float fa = 3.14;
	double da = 3.14;

	printf("int�� ���� ũ�� : %d\n", sizeof(a));
	printf("float�� ���� ũ�� : %d\n", sizeof(fa));
	printf("double�� ���� ũ�� : %d\n", sizeof(da));

	int b = 20, res;
	res = (a > b) ? a : b;
	printf("res = %d\n", res);

	// ��Ʈ������
	int c = 10;  // 00000000 00000000 00000000 00001010
	int d = 12;  // 00000000 00000000 00000000 00001100

	printf("c & d : %d\n", (c & d));  // 8
	printf("c | d : %d\n", (c & d));  // 14
	printf("c ^ d : %d\n", (c & d));  // 6
	printf("~c : %d\n", ~c);  // -11
	printf("c << 1 : %d\n", c << 1);  // shift ����  16 + 4 = 20
	printf("c << 2 : %d\n", c << 2);  // 32 + 8 = 40

}