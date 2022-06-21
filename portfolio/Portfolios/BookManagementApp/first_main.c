# pragma comment (lib,"libmysql.lib")   // MySQL 라이브러리

#include <stdio.h>
#include <stdlib.h>   // 기본

#include <winSock2.h>   // DB용, 네트워크 통신
#include <my_global.h>
#include <mysql.h>

int main(void) {
	printf("MySQL info = %s\n", mysql_get_client_info());

	system("pause");
	return EXIT_SUCCESS; // == return 1
}

