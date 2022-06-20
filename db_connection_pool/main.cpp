#include <iostream>
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>

using std::string;
using std::cout;

void extract_error(
	string fn,
	SQLHANDLE handle,
	SQLSMALLINT type)
{
	SQLINTEGER   i = 0;
	SQLINTEGER   native;
	SQLWCHAR      state[7];
	SQLWCHAR      text[256];
	SQLSMALLINT  len;
	SQLRETURN    ret;

	cout << "\nThe driver reported the following diagnostics whilst running " << fn << "\n\n";

	do
	{
		ret = SQLGetDiagRec(type, handle, ++i, state, &native, text, sizeof(text), &len);
		if (SQL_SUCCEEDED(ret))
			std::wcout << text << std::endl;
	} while (ret == SQL_SUCCESS);
}

SQLHSTMT createstatement(const WCHAR* connectionString) {
	SQLHENV	_environment = SQL_NULL_HANDLE;

	if (::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_environment) != SQL_SUCCESS)
		return nullptr;

	if (::SQLSetEnvAttr(_environment, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0) != SQL_SUCCESS)
		return nullptr;

	SQLHDBC	_connection = SQL_NULL_HANDLE;
	SQLHSTMT statement = SQL_NULL_HANDLE;
	auto alloc_handle_result = ::SQLAllocHandle(SQL_HANDLE_DBC, _environment, &_connection);
	if (alloc_handle_result != SQL_SUCCESS) {
		return nullptr;
	}

	WCHAR stringBuffer[MAX_PATH] = { 0 };
	::wcscpy_s(stringBuffer, connectionString);

	WCHAR resultString[MAX_PATH] = { 0 };
	SQLSMALLINT resultStringLen = 0;

	SQLRETURN ret = ::SQLDriverConnectW(
		_connection,
		NULL,
		reinterpret_cast<SQLWCHAR*>(stringBuffer),
		_countof(stringBuffer),
		OUT reinterpret_cast<SQLWCHAR*>(resultString),
		_countof(resultString),
		OUT & resultStringLen,
		SQL_DRIVER_NOPROMPT
	);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		extract_error("SQLDriverConnectW ", _connection, SQL_HANDLE_DBC);
		return nullptr;
	}

	auto hanle_statement_result = ::SQLAllocHandle(SQL_HANDLE_STMT, _connection, &statement);
	if (hanle_statement_result != SQL_SUCCESS) {
		extract_error("SQLDriverConnectW ", statement, SQL_HANDLE_STMT);
		return nullptr;
	};

	return statement;
}

bool do_fetch(SQLHSTMT statement) {
	SQLRETURN ret = ::SQLFetch(statement);

	switch (ret)
	{
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:
		return true;
	case SQL_NO_DATA:
		std::cout << "NO DATA" << std::endl;
		return false;
	case SQL_ERROR:
		extract_error("SQLDriverConnectW ", statement, SQL_HANDLE_STMT);
		return false;
	}
}

void read_account_id_table(SQLHSTMT statement) {
	/*---------------------------------
	|     이전에 바인딩된 정보 다 날리기   |
	----------------------------------*/
	::SQLFreeStmt(statement, SQL_UNBIND);
	::SQLFreeStmt(statement, SQL_RESET_PARAMS);
	::SQLFreeStmt(statement, SQL_CLOSE);

	/*---------------------------
	|	read 할 column 들 바인딩  |
	----------------------------*/
	__int32 outAccountId = 0;
	SQLLEN outAccountIdLen = 0;
	SQLRETURN ret_account_id_binding = ::SQLBindCol(statement, 1, SQL_C_LONG, &outAccountId, sizeof(outAccountId), &outAccountIdLen);
	if (ret_account_id_binding != SQL_SUCCESS && ret_account_id_binding != SQL_SUCCESS_WITH_INFO)
	{
	}

	WCHAR outSurname[50];
	SQLLEN outSurnameLen = 0;
	SQLRETURN ret_surname_binding = ::SQLBindCol(statement, 2, SQL_C_WCHAR, &outSurname, sizeof(outSurname), &outSurnameLen);
	if (ret_surname_binding != SQL_SUCCESS && ret_surname_binding != SQL_SUCCESS_WITH_INFO)
	{
		extract_error("SQLDriverConnectW ", statement, SQL_HANDLE_STMT);
	}

	bool isAdmin;
	SQLLEN isAdminLen = 0;
	SQLRETURN ret_is_admin_binding = ::SQLBindCol(statement, 3, SQL_TINYINT, &isAdmin, sizeof(isAdmin), &isAdminLen);
	if (ret_is_admin_binding != SQL_SUCCESS && ret_is_admin_binding != SQL_SUCCESS_WITH_INFO)
	{
		extract_error("SQLDriverConnectW ", statement, SQL_HANDLE_STMT);
	}

	// TODO Sammy
	TIMESTAMP_STRUCT createdAt;
	SQLLEN createdAtLen = 0;
	SQLRETURN ret_created_at_binding = ::SQLBindCol(statement, 4, SQL_C_TIMESTAMP, &createdAt, sizeof(createdAt), &createdAtLen);
	if (ret_created_at_binding != SQL_SUCCESS && ret_created_at_binding != SQL_SUCCESS_WITH_INFO)
	{
		extract_error("SQLDriverConnectW ", statement, SQL_HANDLE_STMT);
	}

	/*--------------------------------
	|	read 에 사용할 param 들 바인딩  |
	---------------------------------*/

	__int32 paramAccountId = 0;
	SQLLEN paramAccountIdLen = 0;
	SQLRETURN ret_param_binding = ::SQLBindParameter(statement, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, sizeof(paramAccountId), 0, &paramAccountId, 0, &paramAccountIdLen);

	/*---------------------------
	|		    SQL 실행		    |
	----------------------------*/
	auto query = L"SELECT AccountId, Surname, IsAdmin, CreatedAt FROM [dbo].[Account] WHERE AccountId > (?)";
	SQLRETURN ret_execute = ::SQLExecDirectW(statement, (SQLWCHAR*)query, SQL_NTSL);
	if (ret_execute == SQL_SUCCESS || ret_execute == SQL_SUCCESS_WITH_INFO) {

	}
	else {
		extract_error("SQLDriverConnectW ", statement, SQL_HANDLE_STMT);
	}

	/*---------------------------
	|	   SQL result fetch     |
	----------------------------*/
	while (do_fetch(statement)) {
		std::wcout << "AccountId: " << outAccountId << " Surname : " << outSurname << "IsAdmin " << isAdmin << std::endl;
	}

	/*---------------------------
	|	   간단한 비교들	         |
	----------------------------*/
	SQL_TIMESTAMP_STRUCT date_compare;
	date_compare.year = 2022;
	date_compare.month = 1;
	date_compare.day = 1;
	date_compare.hour = 23;

	std::wstring target(outSurname);
	std::wstring compareWith = L"Samuel";
	if (target == compareWith) {
		std::cout << "Yes we found Samuel account" << std::endl;
	};
}

int main()
{
	// Trusted_Connection 를 제공하지 않으면 Username, password 를 넣어줘야 한다
	// DRIVER 매우 중요하다.. 잘못된 Driver을 넣으면 연결 불가하다
	auto connectionString = L"DRIVER={ODBC Driver 17 for SQL Server};SERVER=localhost;Database=testdb;Trusted_Connection=Yes;";

	SQLHSTMT statement = createstatement(connectionString);
	read_account_id_table(statement);
}
