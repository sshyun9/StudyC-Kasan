#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>

SQLHENV henv = NULL;  // DB 환경 구조체
SQLHDBC hdbc = NULL;   // DB 접속 구조체

int OBDCConnect(SQLCHAR* dsn, SQLCHAR* userId, SQLCHAR* pwd) {
	SQLRETURN res;
	henv = NULL;  
	hdbc = NULL;  // 초기화

	// SQL 환경 henv 값을 할당
	res = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	if (res == SQL_SUCCESS || res == SQL_SUCCESS_WITH_INFO) {
		// ODBC 버전에 따른 환경 속성 설정
		res = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
		if (res == SQL_SUCCESS || res == SQL_SUCCESS_WITH_INFO) {
			// 커넥션 핸들 설정
			res = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
			if (res == SQL_SUCCESS || res == SQL_SUCCESS_WITH_INFO) {
				// 접속하기위한 설정 먼저
				SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)10, 0);
				// 실제 접속
				res = SQLConnect(hdbc, dsn, SQL_NTS, userId, SQL_NTS, pwd, SQL_NTS);
				if (res == SQL_SUCCESS || res == SQL_SUCCESS_WITH_INFO) {
					return 1; // 접속 성공 == true
				}
				SQLDisconnect(hdbc);
			}
			SQLFreeHandle(SQL_HANDLE_DBC, hdbc);

			hdbc = henv = NULL;

			return 0;  // 접속 실패 false
		}
	}
}

int main(void) {
	printf("MSSQL 접속 시작");
	OBDCConnect("BMS", "sa", "1234");

	OBDCDisconnect();
	printf("접속종료!");
	return 0;
}