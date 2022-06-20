#define _CRT_SECURE_NO_WARNINGS
// calloc, realloc
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int* pi; //정수형포인터
	int size = 5, count = 0, num, i;

	//calloc  // 0으로 초기화된 메모리 공간을 얻는건 calloc 뿐
	pi = calloc(size, sizeof(int));  // 5의 int형 배열 0으로 초기화
	while (1)
	{
		if (count == size) break;  // 5까지 늘어났으면 종료

		printf("양수만 입력하세요 => ");
		scanf("%d", &num);
		if (num <= 0) break;


		// 5보다 입력할 갯수가 늘어나면 사이즈를 늘려주는
		// realloc
		if (count == size) {
			size += 5;
			pi = (int*)realloc(pi, sizeof(int) * size); // size +5 증가
		}
		pi[count++] = num;
		count++;
	}

	for (i = 0; i < size; i++) {
		printf("%5d", pi[i]);
	}
	free(pi);
}