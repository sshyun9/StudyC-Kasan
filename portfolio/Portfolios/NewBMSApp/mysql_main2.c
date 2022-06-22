#define _CRT_SECURE_NO_WARNINGS
#pragma comment (lib, "libmysql.lib")

#include <winsock.h>
#include <windows.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// MySQL ���� ����(�ڱ⼳������ ���� �ʿ�!)
#define mysqlip "127.0.0.1" 
#define port 3306
#define loginusername "bms"
#define loginpassword "1234"
#define mysqlname "bms"

#define	TITLE_LENGTH 100

// å���� ���� ����ü bookInfo
typedef struct bookInfo {
	int id;
	char title[TITLE_LENGTH];
	char writer[TITLE_LENGTH];
	char genre[45];
	char release_date[15];  // "2020-06-22\0" �̱⶧���� 11�� ������. => 10���� �ϸ� �ȵ�!
	short pages;
	char company[50];
	int price;
} book;

// �Լ� ��������
void connect_db(MYSQL*);
void close_db(MYSQL*);
int insert_book(MYSQL*);
int display_books(MYSQL*);
int update_book(MYSQL*);  //
int delete_book(MYSQL*);  //
int search_book(MYSQL*);  //
void print_header(void);

int main(void) {
	setlocale(LC_ALL, "Korean");

	MYSQL* conn;
	MYSQL_RES* result;
	MYSQL_ROW row;
	int query_stat;
	unsigned int num_fields;
	unsigned long* lengths;
	int input = 0;  // �޴� �Է°�
	int ret = 0; // ���ϰ� �޴� �Լ�

	conn = mysql_init(NULL);
	connect_db(conn);

	// ���ѷ���
	while (1) {
		system("cls"); // ȭ�� Ŭ����
		printf("�������� ���α׷�(v2.0)\n");
		printf("1. ������ȸ\n");
		printf("2. �����Է�\n");
		printf("3. ��������\n");
		printf("4. �����˻�\n");
		printf("5. ��������\n");
		printf("6. ���α׷�����\n");
		printf("�Է� > ");
		scanf("%d", &input); rewind(stdin);

		switch (input) {
		case 1:
			ret = display_books(conn);
			if (ret == 100) {
				close_db(conn);
				printf("������������ ����Ǿ����ϴ�.\n");
				exit(1);
			}
			system("pause");
			break;
		case 2:
			ret = insert_book(conn);
			if (ret == 100) {
				close_db(conn);
				printf("������������ ����Ǿ����ϴ�.\n");
				exit(1);
			system("pause");
			break;
		case 3:
			ret = update_book(conn);
			if (ret == 100) {
				close_db(conn);
				printf("������������ ����Ǿ����ϴ�.\n");
				exit(1);
			system("pause");
			break;
		case 4:
			ret = search_book(conn);
			if (ret == 100) {
				close_db(conn);
				printf("������������ ����Ǿ����ϴ�.\n");
				exit(1);
			system("pause");
			break;
		case 5:
			ret = delete_book(conn);
			if (ret == 100) {
				close_db(conn);
				printf("������������ ����Ǿ����ϴ�.\n");
				exit(1);
			system("pause");
			break;
		case 6:
		default:
			close_db(conn);
			printf("���α׷� ����!");
			exit (0);
		}
	}
	return 0;
}

void connect_db(MYSQL* conn) {
	mysql_real_connect(conn, mysqlip, loginusername, loginpassword, mysqlname, port, NULL, 0);

	if (conn == NULL) {
		fprintf(stderr, "�������! : %s\n", mysql_error(conn));
		return ;
	}
	printf("���Ἲ��!\n");
}

void close_db(MYSQL* conn) {
	mysql_close(conn);
	printf("��������\n");
}

int display_books(MYSQL* conn) {
	MYSQL_RES* result;
	MYSQL_ROW row;
	int query_stat;
	unsigned int num_fields;
	unsigned long* lengths;
	
	int i = 0;

	query_stat = mysql_query(conn, "SELECT * FROM books_info");
	if (query_stat != 0) {
		fprintf(stderr, "��������! : %s\n", mysql_error(conn));
		// mysql_close(conn);
		return 100; //����
	}

	result = mysql_store_result(conn);
	if (result->row_count == 0) {
		printf("����� �����Ͱ� �����ϴ�.\n");
		return 0;
	}

	print_header();

	num_fields = mysql_num_fields(result);
	while (row = mysql_fetch_row(result)) {
		lengths = mysql_fetch_lengths(result);
		for (i = 0; i < num_fields; i++)
		{
			printf("[%.*s] ", (int)lengths[i], row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}
	return 0;
}

int insert_book(MYSQL* conn) {
	int i, j = 0;
	char query[500] = { 0, };
	book tmpBook = { 0, };
	int res = 0;

	printf("å�̸� �Է� > ");
	scanf("%[^\n]s", tmpBook.title);
	rewind(stdin); // ǥ���Է� ���÷���

	if (strlen(tmpBook.title) == 0){
		printf("Ģ�̸��� �����ϴ�.�޴��� �����մϴ�.\n')")
		return 0;


	printf("���ڸ� �Է� > ");
	scanf("%[^\n]s", tmpBook.writer);
	rewind(stdin);

	if (strlen(tmpBook.writer) == 0) {
		printf("���ڸ��� �����ϴ�.�޴��� �����մϴ�.\n')")
			return 0;


	printf("�帣 �Է� > ");
	scanf("%[^\n]s", tmpBook.genre);
	rewind(stdin);

	printf("������ �Է�(ex. 2022-06-01) > ");
	scanf("%s", tmpBook.release_date);
	rewind(stdin);

	printf("�������� �Է�(ex. 300) > ");
	scanf("%d", &tmpBook.pages);   // ���ڴ� &���̱�
	rewind(stdin);

	printf("���ǻ� �Է� > ");
	scanf("%[^\n]s", tmpBook.company);
	rewind(stdin);

	printf("���� �Է�(ex. 15000) > ");
	scanf("%d", &tmpBook.price);   // ���ڴ� &���̱�
	rewind(stdin);

	sprintf(query, " INSERT INTO books_info "
				   " (title, writer, genre, release_date, pages, company, price) "
				   " VALUES "
				   " ('%s', '%s', '%s', '%s', %d, '%s', %d) ",
			tmpBook.title, tmpBook.writer, tmpBook.genre, tmpBook.release_date,
			tmpBook.pages, tmpBook.company, tmpBook.price);

	if (mysql_query(conn, query) != 0) {
		fprintf(stderr, "�Է¿��� : %s\n", mysql_error(conn));
		return 100; // 100 �� DB����
	}
	printf("å������ �ԷµǾ����ϴ�.\n");
	return 0;
}

// å���� �����Լ�
int update_book(MYSQL* conn) {
	int i = 0;
	MYSQL_RES* result;
	MYSQL_ROW row;
	int query_stat;
	unsigned int num_fields;
	unsigned long* lengths;
	char query[500] = { 0, };
	

	// å ����ü
	book tmpBook = { 0, };

	printf("������ å ��ȣ �Է� > ");
	scanf("%d", &tmpBook.id);
	rewind(stdin);

	sprintf(query, "SELECT*FROM books_info WHERE id = %d", tmpBook.id);
	query_stat = mysql_query(conn, query);
	if (query_stat != 0) {
		fprintf(stderr, "��������! : %s\n", mysql_error(conn));
		// mysql_close(conn);
		return 100;
	}

	printf("��������\n");

	result = mysql_store_result(conn);
	if (result->row_count == 0) {
		printf("����� �����Ͱ� �����ϴ�.\n");
		return;
	}

	print_header();

	num_fields = mysql_num_fields(result);
	while (row = mysql_fetch_row(result)) {
		lengths = mysql_fetch_lengths(result);
		for (i = 0; i < num_fields; i++)
		{
			printf("[%.*s] ", (int)lengths[i], row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	printf("���� å�̸� �Է� > ");
	scanf("%[^\n]s", tmpBook.title);
	rewind(stdin); // ǥ���Է� ���÷���

	printf("���� ���ڸ� �Է� > ");
	scanf("%[^\n]s", tmpBook.writer);
	rewind(stdin);

	printf("�����帣 �Է� > ");
	scanf("%[^\n]s", tmpBook.genre);
	rewind(stdin);

	sprintf(query, " UPDATE books_info SET "
				   "		title = '%s' "
			   	   "		,writer = '%s' "
				   "		,genre = '%s' "
				   " WHERE id = %d ", tmpBook.title, tmpBook.genre, tmpBook.id);

	if (mysql_query(conn, query) != 0) {
		fprintf(stderr, "������������! : %s\n", mysql_error(conn));
		return 100;
	}
	printf("å������ �����Ǿ����ϴ�.\n");
	return 0;
}

int delete_book(MYSQL* conn) {
	char query[500] = { 0, };

	book tmpBook = { 0, };
	MYSQL_RES* result;
	int query_stat;

	printf("������ å ��ȣ �Է� > ");
	scanf("%d", &tmpBook.id);
	rewind(stdin);

	query_stat = mysql_query(conn, "SELECT * FROM books_info");
	if (query_stat != 0) {
		fprintf(stderr, "��������! : %s\n", mysql_error(conn));
		// mysql_close(conn);
		return 100;
	}

	result = mysql_store_result(conn);
	if (result->row_count == 0) {
		printf("������ �����Ͱ� �����ϴ�.\n");
		return 0;
	}

	sprintf(query,
		" DELETE FROM books_info WHERE id = %d ", tmpBook.id);

	if (mysql_query(conn, query) != 0) {
		fprintf(stderr, "������������! : %s\n", mysql_error(conn));
		return 100;
	}
	printf("å������ �����Ǿ����ϴ�.\n");
	return 0;
}

int search_book(MYSQL* conn) {
	
	MYSQL_RES* result;
	MYSQL_ROW row;
	int query_stat;
	unsigned int num_fields;
	unsigned long* lengths;
	book tmpBook = { 0, };
	char query[500] = { 0, };

	int i = 0;

	printf("�˻� å�̸� �Է� > ");
	scanf("%[^\n]s", tmpBook.title);
	rewind(stdin);

	sprintf(query,
		" SELECT * FROM books_info WHERE title like '%%%s%%' ", tmpBook.title); // �˻� : %% �ڵ� %%

	query_stat = mysql_query(conn, query); 
	if (query_stat != 0) {
		fprintf(stderr, "��������! : %s\n", mysql_error(conn));
		return 100;
	}

	result = mysql_store_result(conn);
	if (result->row_count == 0) {
		printf("����� �����Ͱ� �����ϴ�.\n");
		return 0;
	}

	print_header();

	num_fields = mysql_num_fields(result);
	while (row = mysql_fetch_row(result)) {
		lengths = mysql_fetch_lengths(result);
		for (i = 0; i < num_fields; i++)
		{
			printf("[%.*s] ", (int)lengths[i], row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}
	return 0;
}

void print_header(void) {
	printf(" [��ȣ]  [å����]  [����]  [�帣]  [������]  [��������]  [���ǻ�]  [����] \n");
	printf("===========================================================================\n");
}