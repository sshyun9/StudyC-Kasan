#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>

SQLHENV henv = NULL;  // DB ȯ�� ����ü
SQLHDBC hdbc = NULL;   // DB ���� ����ü

int OBDCConnect(SQLCHAR* dsn, SQLCHAR* userId, SQLCHAR* pwd) {
	SQLRETURN res;
	henv = NULL;  
	hdbc = NULL;  // �ʱ�ȭ

	// SQL ȯ�� henv ���� �Ҵ�
	res = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	if (res == SQL_SUCCESS || res == SQL_SUCCESS_WITH_INFO) {
		// ODBC ������ ���� ȯ�� �Ӽ� ����
		res = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
		if (res == SQL_SUCCESS || res == SQL_SUCCESS_WITH_INFO) {
			// Ŀ�ؼ� �ڵ� ����
			res = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
			if (res == SQL_SUCCESS || res == SQL_SUCCESS_WITH_INFO) {
				// �����ϱ����� ���� ����
				SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)10, 0);
				// ���� ����
				res = SQLConnect(hdbc, dsn, SQL_NTS, userId, SQL_NTS, pwd, SQL_NTS);
				if (res == SQL_SUCCESS || res == SQL_SUCCESS_WITH_INFO) {
					return 1; // ���� ���� == true
				}
				SQLDisconnect(hdbc);
			}
			SQLFreeHandle(SQL_HANDLE_DBC, hdbc);

			hdbc = henv = NULL;

			return 0;  // ���� ���� false
		}
	}
}

int main(void) {
	printf("MSSQL ���� ����");
	OBDCConnect("BMS", "sa", "1234");

	OBDCDisconnect();
	printf("��������!");
	return 0;
}