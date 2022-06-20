#define _CRT_SECURE_NO_WARNINGS
// 파일 읽기
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE* fp; // 구조체(클래스에서 변수만 있는것과 거의 동일)
	int ch;

	fp = fopen("C:\\temp\\a.txt", "r"); // a.txt 파일을 읽기모드 오픈
	if (fp == NULL) {
		printf("파일을 열지 못했습니다\n");
		return (1); // == return 1;
	}

	while (1) {// C에서 true == 1
		ch = fgetc(fp);
		if (ch == EOF) break;  // End Of File

		putchar(ch);  // printf("%c", ch);
	}

	fclose(fp); // 파일 닫아줘야함!! 반드시!!
}