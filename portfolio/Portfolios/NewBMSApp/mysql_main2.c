#define _CRT_SECURE_NO_WARNINGS
#pragma comment (lib, "libmysql.lib")

#include <winsock.h>
#include <windows.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// MySQL 접속 설정(자기설정따라 변경 필요!)
#define mysqlip "127.0.0.1" 
#define port 3306
#define loginusername "bms"
#define loginpassword "1234"
#define mysqlname "bms"

#define	TITLE_LENGTH 100

// 책정보 담을 구조체 bookInfo
typedef struct bookInfo {
	int id;
	char title[TITLE_LENGTH];
	char writer[TITLE_LENGTH];
	char genre[45];
	char release_date[15];  // "2020-06-22\0" 이기때문에 11개 들어가야함. => 10으로 하면 안됨!
	short pages;
	char company[50];
	int price;
} book;

// 함수 원형선언
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
	int input = 0;  // 메뉴 입력값
	int ret = 0; // 리턴값 받는 함수

	conn = mysql_init(NULL);
	connect_db(conn);

	// 무한루프
	while (1) {
		system("cls"); // 화면 클리어
		printf("도서관리 프로그램(v2.0)\n");
		printf("1. 도서조회\n");
		printf("2. 도서입력\n");
		printf("3. 도서수정\n");
		printf("4. 도서검색\n");
		printf("5. 도서삭제\n");
		printf("6. 프로그램종료\n");
		printf("입력 > ");
		scanf("%d", &input); rewind(stdin);

		switch (input) {
		case 1:
			ret = display_books(conn);
			if (ret == 100) {
				close_db(conn);
				printf("비정상적으로 종료되었습니다.\n");
				exit(1);
			}
			system("pause");
			break;
		case 2:
			ret = insert_book(conn);
			if (ret == 100) {
				close_db(conn);
				printf("비정상적으로 종료되었습니다.\n");
				exit(1);
			system("pause");
			break;
		case 3:
			ret = update_book(conn);
			if (ret == 100) {
				close_db(conn);
				printf("비정상적으로 종료되었습니다.\n");
				exit(1);
			system("pause");
			break;
		case 4:
			ret = search_book(conn);
			if (ret == 100) {
				close_db(conn);
				printf("비정상적으로 종료되었습니다.\n");
				exit(1);
			system("pause");
			break;
		case 5:
			ret = delete_book(conn);
			if (ret == 100) {
				close_db(conn);
				printf("비정상적으로 종료되었습니다.\n");
				exit(1);
			system("pause");
			break;
		case 6:
		default:
			close_db(conn);
			printf("프로그램 종료!");
			exit (0);
		}
	}
	return 0;
}

void connect_db(MYSQL* conn) {
	mysql_real_connect(conn, mysqlip, loginusername, loginpassword, mysqlname, port, NULL, 0);

	if (conn == NULL) {
		fprintf(stderr, "연결오류! : %s\n", mysql_error(conn));
		return ;
	}
	printf("연결성공!\n");
}

void close_db(MYSQL* conn) {
	mysql_close(conn);
	printf("연결종료\n");
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
		fprintf(stderr, "쿼리오류! : %s\n", mysql_error(conn));
		// mysql_close(conn);
		return 100; //에러
	}

	result = mysql_store_result(conn);
	if (result->row_count == 0) {
		printf("출력할 데이터가 없습니다.\n");
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

	printf("책이름 입력 > ");
	scanf("%[^\n]s", tmpBook.title);
	rewind(stdin); // 표준입력 리플레쉬

	if (strlen(tmpBook.title) == 0){
		printf("칙이름이 없습니다.메뉴를 종료합니다.\n')")
		return 0;


	printf("저자명 입력 > ");
	scanf("%[^\n]s", tmpBook.writer);
	rewind(stdin);

	if (strlen(tmpBook.writer) == 0) {
		printf("저자명이 없습니다.메뉴를 종료합니다.\n')")
			return 0;


	printf("장르 입력 > ");
	scanf("%[^\n]s", tmpBook.genre);
	rewind(stdin);

	printf("출판일 입력(ex. 2022-06-01) > ");
	scanf("%s", tmpBook.release_date);
	rewind(stdin);

	printf("페이지수 입력(ex. 300) > ");
	scanf("%d", &tmpBook.pages);   // 숫자는 &붙이기
	rewind(stdin);

	printf("출판사 입력 > ");
	scanf("%[^\n]s", tmpBook.company);
	rewind(stdin);

	printf("가격 입력(ex. 15000) > ");
	scanf("%d", &tmpBook.price);   // 숫자는 &붙이기
	rewind(stdin);

	sprintf(query, " INSERT INTO books_info "
				   " (title, writer, genre, release_date, pages, company, price) "
				   " VALUES "
				   " ('%s', '%s', '%s', '%s', %d, '%s', %d) ",
			tmpBook.title, tmpBook.writer, tmpBook.genre, tmpBook.release_date,
			tmpBook.pages, tmpBook.company, tmpBook.price);

	if (mysql_query(conn, query) != 0) {
		fprintf(stderr, "입력오류 : %s\n", mysql_error(conn));
		return 100; // 100 은 DB에러
	}
	printf("책정보가 입력되었습니다.\n");
	return 0;
}

// 책정보 수정함수
int update_book(MYSQL* conn) {
	int i = 0;
	MYSQL_RES* result;
	MYSQL_ROW row;
	int query_stat;
	unsigned int num_fields;
	unsigned long* lengths;
	char query[500] = { 0, };
	

	// 책 구조체
	book tmpBook = { 0, };

	printf("수정할 책 번호 입력 > ");
	scanf("%d", &tmpBook.id);
	rewind(stdin);

	sprintf(query, "SELECT*FROM books_info WHERE id = %d", tmpBook.id);
	query_stat = mysql_query(conn, query);
	if (query_stat != 0) {
		fprintf(stderr, "쿼리오류! : %s\n", mysql_error(conn));
		// mysql_close(conn);
		return 100;
	}

	printf("기존정보\n");

	result = mysql_store_result(conn);
	if (result->row_count == 0) {
		printf("출력할 데이터가 없습니다.\n");
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

	printf("변경 책이름 입력 > ");
	scanf("%[^\n]s", tmpBook.title);
	rewind(stdin); // 표준입력 리플레쉬

	printf("변경 저자명 입력 > ");
	scanf("%[^\n]s", tmpBook.writer);
	rewind(stdin);

	printf("변경장르 입력 > ");
	scanf("%[^\n]s", tmpBook.genre);
	rewind(stdin);

	sprintf(query, " UPDATE books_info SET "
				   "		title = '%s' "
			   	   "		,writer = '%s' "
				   "		,genre = '%s' "
				   " WHERE id = %d ", tmpBook.title, tmpBook.genre, tmpBook.id);

	if (mysql_query(conn, query) != 0) {
		fprintf(stderr, "수정쿼리오류! : %s\n", mysql_error(conn));
		return 100;
	}
	printf("책정보가 수정되었습니다.\n");
	return 0;
}

int delete_book(MYSQL* conn) {
	char query[500] = { 0, };

	book tmpBook = { 0, };
	MYSQL_RES* result;
	int query_stat;

	printf("삭제할 책 번호 입력 > ");
	scanf("%d", &tmpBook.id);
	rewind(stdin);

	query_stat = mysql_query(conn, "SELECT * FROM books_info");
	if (query_stat != 0) {
		fprintf(stderr, "쿼리오류! : %s\n", mysql_error(conn));
		// mysql_close(conn);
		return 100;
	}

	result = mysql_store_result(conn);
	if (result->row_count == 0) {
		printf("삭제할 데이터가 없습니다.\n");
		return 0;
	}

	sprintf(query,
		" DELETE FROM books_info WHERE id = %d ", tmpBook.id);

	if (mysql_query(conn, query) != 0) {
		fprintf(stderr, "삭제쿼리오류! : %s\n", mysql_error(conn));
		return 100;
	}
	printf("책정보가 삭제되었습니다.\n");
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

	printf("검색 책이름 입력 > ");
	scanf("%[^\n]s", tmpBook.title);
	rewind(stdin);

	sprintf(query,
		" SELECT * FROM books_info WHERE title like '%%%s%%' ", tmpBook.title); // 검색 : %% 코딩 %%

	query_stat = mysql_query(conn, query); 
	if (query_stat != 0) {
		fprintf(stderr, "쿼리오류! : %s\n", mysql_error(conn));
		return 100;
	}

	result = mysql_store_result(conn);
	if (result->row_count == 0) {
		printf("출력할 데이터가 없습니다.\n");
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
	printf(" [번호]  [책제목]  [저자]  [장르]  [출판일]  [페이지수]  [출판사]  [가격] \n");
	printf("===========================================================================\n");
}