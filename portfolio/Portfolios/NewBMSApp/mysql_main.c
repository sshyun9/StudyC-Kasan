#pragma comment (lib, "libmysql.lib")

#include <winsock.h>
#include <windows.h>
#include <mysql.h>
#include <stdio.h>
// #include <stdlib.h>
#include <string.h>
#include <locale.h>

// MySQL ���� ����(�ڱ⼳������ ���� �ʿ�!)
#define mysqlip "127.0.0.1" 
#define port 3306
#define loginusername "bms"
#define loginpassword "1234"
#define mysqlname "bms"

int main(void) {
	MYSQL* conn;

	conn = mysql_init(NULL);
	mysql_real_connect(conn, mysqlip, loginusername, loginpassword, mysqlname, port, NULL, 0);  // conn ��ü�� ���� ����
	if (conn == NULL) {
		fprintf(stderr, "������� : %s\n", mysql_error(conn));
		return 1;
	}
	else {
		printf("���Ἲ��!!!!\n");
		printf("�������� %s\n", conn->server_version);
	}

	mysql_close(conn);
	return 0;
}
