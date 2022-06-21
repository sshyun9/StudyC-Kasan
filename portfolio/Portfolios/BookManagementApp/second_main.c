#pragma comment (lib, "libmysql.lib") // MySQL ���̺귯�� ���
#define _WINSOCKAPI_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 
#include <Windows.h>

#include <my_global.h>
#include <Winsock.h>
#include <mysql.h>


#define mysqlip "127.0.0.1" // localhost, 192.168.0.17
#define port 3306
#define userid "root"
#define password ""
#define mysqlname "ems" // mysql schema��


int main(void) {
    // ����
    MYSQL* conn;
    MYSQL_RES* result;
    MYSQL_ROW row;

    int query_stat;

    unsigned int num_fields;
    unsigned long* lengths;

    int i = 0;

    setlocale(LC_ALL, "Korean"); // �ѱ��� ����������
    conn = mysql_init(NULL);
    mysql_real_connect(conn, mysqlip, userid, password,
        mysqlname, port, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "������� : %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    printf("���Ἲ��!!\n");

    // ����� ���� ó��!!!
    printf("�������� %s\n", conn->server_version);

    // ������ ����
    query_stat = mysql_query(conn, "SELECT * FROM ems.books_info;");
    if (query_stat != 0) {
        fprintf(stderr, "�������� : %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // ��������� ȭ�����
    result = mysql_store_result(conn); // ���  ������ü ����
    num_fields = mysql_num_fields(result); // �÷�����
    while (row = mysql_fetch_row(result)) {
        lengths = mysql_fetch_lengths(result);
        for (i = 0; i < num_fields; i++) {
            printf("[%s]", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    // ����Ǯ(Connection Pool)
    mysql_close(conn);

    system("pause");
    return EXIT_SUCCESS;

}