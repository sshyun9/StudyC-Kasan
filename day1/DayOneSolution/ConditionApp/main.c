#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

//void main(void) {
//	int a=10;
//
//	// if�� ����!
//	if (a > 10) {
//		printf("a�� 10���� ŭ");
//	}
//	else if (a == 10) {
//		printf("a�� 10");
//	}
//	else {
//		printf("a�� 10���� ����");
//
//	}
//}

void main(void) {

	char grade;

	printf("������ �Է��ϼ��� > ");
	scanf("%c", &grade);

	switch (grade)
	{
	case'A':
		printf("����ϳ׿�!");
		break;
	case'B':
		printf("���� ���ϼ̽��ϴ�!");
		break;
	case'C':
		printf("���߽��ϴ�.");
		break;
	case'D':
		printf("�ܿ� ����߱���");
		break;
	case'F':
		printf("���� �б⿡ �� ����~");
		break;
	default:   // �ټ����� ���̽��� �ƴ� ���
		printf("������ ����� �Է��ϼ���!!");
		break;
	}
}

//if (grade == 'A') {
//	printf("����ϳ׿�!");
//}
//else if (grade == 'B') {
//	printf("���� ���ϼ̽��ϴ�!");
//}
//else if (grade == 'C') {
//	printf("���߽��ϴ�.");
//}
//else if (grade == 'D') {
//	printf("�ܿ� ����߱���");
//}
//else if (grade == 'F') {
//	printf("���� �б⿡ �� ����~");
//}