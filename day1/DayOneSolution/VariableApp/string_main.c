// ���ڿ� �н� main.c
#define _CRT_SECURE_NO_WARNINGS  // strcpy, scanf ���� ����� �� ��ó����, ����-�ɼ�-�ؽ�Ʈ����-��ó���⿡���� �ذᰡ��

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void) {
	const double tax_rate = 0.12; // ���� �ʱ�ȭ ���ȭ
	char fruit[6] = "apple"; // apple 5�������� [6]���� �ؾ���. ���ڿ� ������ ���ڰ� �����ٴ� Ư������ ���ڸ� ����.
	char kfruit[6] = "���"; // �ѱ��� �ϳ��� 2 ����� �� 5�̻� �ʿ� 

	printf("%s\n", fruit);
	printf("%s\n", kfruit);

	//fruit = "������" // ������ fruit �̹� �Ƚ� �߱� ������ �׳��� ���ٲ�.
	
	strcpy(fruit, "������");
	printf("%s\n", fruit);

	// tax_rate = 0.15;  // error ������� ����Ұ�

}