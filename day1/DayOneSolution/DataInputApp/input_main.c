// ����� �� �Է�
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void main(void) {
	//int a;
	//int res;

	//printf("������ �Է��ϼ��� > ");
	//// res = 1 ���������� �Է�, 0 �߸��� �� �Է�
	//res = scanf("%d", &a);  // �ֿܼ��� Ű���� �Է�. a ������ �����ּ�!!
	//printf("�Էµ� �� : %d\n", a);

	//int age;
	//double height;

	//printf("���̿� Ű�� �Է��ϼ��� >");
	//res = scanf("%d%lf", &age, &height);
	//printf("���̴� %d��, Ű�� %.1lfcm �Դϴ�.", age, height);

	char grade;
	char name[20];

	printf("���� �Է� >");
	scanf("%c", &grade);
	printf("�̸� �Է� >");
	scanf("%s, name"); // ���ڿ�, ������ ��ü�� �����ּҳ�Ÿ��
	
	printf("%s �л��� ������ %c", name, grade);
}