#include <iostream>
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>

using std::cout;
using std::string;

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

	SQLRETURN ret = ::SQLDriverConnect(
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
		extract_error("SQLDriverConnect ", _connection, SQL_HANDLE_DBC);
		return nullptr;
	}

	auto hanle_statement_result = ::SQLAllocHandle(SQL_HANDLE_STMT, _connection, &statement);
	if (hanle_statement_result != SQL_SUCCESS) {
		extract_error("SQLDriverConnect ", statement, SQL_HANDLE_STMT);
		return nullptr;
	};

	return statement;
}

void call_precedure(SQLHSTMT statement) {

	/*---------------------------------
|     이전에 바인딩된 정보 다 날리기   |
----------------------------------*/
	::SQLFreeStmt(statement, SQL_UNBIND);
	::SQLFreeStmt(statement, SQL_RESET_PARAMS);
	::SQLFreeStmt(statement, SQL_CLOSE);

	RETCODE retcode;
	SQLLEN cbParm1 = SQL_NTS;
	SQLLEN cbParm2 = SQL_NTS;
	SWORD sParm1 = 0, sParm2 = 1;

	// 위의 코드처럼 Param binding을 할 때 SWORD타입의 데이터의 레퍼런스를 넣어줘도 되고 아니면 아래처럼 int32로 명시해주어도 된다.
	// 다만 데이터를 받아와서 쓸 때 컨버팅이 필요.
	__int32 outParmValue = 0;
	__int32 outReturnValue = 0;

	// Bind the return code to variable sParm1.  
	retcode = SQLBindParameter(statement, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &outParmValue, 0, &cbParm1);
	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)) {
		printf("SQLBindParameter(sParm1) Failed\n\n");
		extract_error("[Calling Procedure] ", statement, SQL_HANDLE_STMT);
		return;
	}

	// Bind the output parameter to variable sParm2.  
	retcode = SQLBindParameter(statement, 2, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &outReturnValue, 0, &cbParm2);
	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)) {
		printf("SQLBindParameter(sParm2) Failed\n\n");
		extract_error("[Calling Procedure] ", statement, SQL_HANDLE_STMT);
		return;
	}

	// Execute the command.   
	retcode = SQLExecDirect(statement, (SQLWCHAR*)L"{? = call TestParm(?)}", SQL_NTS);
	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)) {
		printf("SQLExecDirect Failed\n\n");
		extract_error("[Calling Procedure] ", statement, SQL_HANDLE_STMT);
		return;
	}

	// Show parameters are not filled.  
	printf("Before result sets cleared: RetCode = %d, OutParm = %d.\n", sParm1, sParm2);

	// Clear any result sets generated.  
	while ((retcode = SQLMoreResults(statement)) != SQL_NO_DATA);

	// Show parameters are now filled.  
	std::cout << "outParmValue is " << outParmValue << std::endl;
	std::cout << "outReturnValue is " << outReturnValue << std::endl;
	printf("After result sets drained: RetCode = %d, OutParm = %d.\n", sParm1, sParm2);
}

/*
Prerequisite : MSSQL, SSMS, AdventureWorks samle database(https://docs.microsoft.com/en-us/sql/samples/adventureworks-install-configure?view=sql-server-ver15&tabs=ssms)
Reference : https://docs.microsoft.com/en-us/sql/relational-databases/native-client-odbc-how-to/running-stored-procedures-process-return-codes-and-output-parameters?view=sql-server-ver16
*/
int main() {
	// Trusted_Connection 를 제공하지 않으면 Username, password 를 넣어줘야 한다
	// DRIVER 매우 중요하다.. 잘못된 Driver을 넣으면 연결 불가하다
	auto connectionString = L"FILEDSN=E:/Joycity/FS2/Program/Branches/master/Server/Output/_FS2_KOR_DEV_DEBUG_x64/FSGameServer/FS2_GAME.dsn;UID=SC_FS2USER;PWD=f$ei#L!;";
	//auto connectionString = L"DRIVER={ODBC Driver 17 for SQL Server};SERVER=DESKTOP-S46ITDN;Database=FS2_GAME;UID=SC_FS2USER;PWD=f$ei#L!;";

	SQLHSTMT statement = createstatement(connectionString);
	call_precedure(statement);
}