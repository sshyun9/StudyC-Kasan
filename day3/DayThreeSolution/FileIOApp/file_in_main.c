#define _CRT_SECURE_NO_WARNINGS
// ���� �б�
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE* fp; // ����ü(Ŭ�������� ������ �ִ°Ͱ� ���� ����)
	int ch;

	fp = fopen("C:\\temp\\a.txt", "r"); // a.txt ������ �б��� ����
	if (fp == NULL) {
		printf("������ ���� ���߽��ϴ�\n");
		return (1); // == return 1;
	}

	while (1) {// C���� true == 1
		ch = fgetc(fp);
		if (ch == EOF) break;  // End Of File

		putchar(ch);  // printf("%c", ch);
	}

	fclose(fp); // ���� �ݾ������!! �ݵ��!!
}