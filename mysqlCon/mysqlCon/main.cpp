#include <iostream>
#include <mysql.h>
#include "DBCon.h"

//프로젝트 설정에서 추가하지 말고, 이렇게 추가해도 된다.
//#pragma comment(lib, "libmysql.lib")

using ::std::cout;
using ::std::endl;
const int DB_QUERY_SUCCESS = 0;

int main()
{
    //mysql + c++연동하기(이때까지는 단순히 mysql lib와 연결해서 기능 테스트했을뿐, 실제 server와 연결한 건 아님)
    cout << mysql_get_client_info() << endl;

    MYSQL conn;			//mysql 정보를 담는 구조체
    MYSQL* connPtr;		//mysql핸들
    MYSQL_RES* result;	//쿼리 요청후 결과 구조체포인터
    MYSQL_ROW row;		//쿼리 요청후 반환된 로우(열)
    int stat;		    //쿼리 요청후 결과(성공,실패)

    mysql_init(&conn);	//mysql 정보 구조체 초기화
    //mysql서버 연결, local은 상관없으나, 주소인경우 외부 접속되게 권한 설정해야 한다.
    connPtr = mysql_real_connect(&conn, "192.168.35.179", "nicecapj", "epdlxjqpdltm82!", "mydb", 3306, nullptr, 0);
    if (!connPtr)
    {
        cout << "error connect" << endl;
        return -1;
    }

    //db의 문자열과 vs문자열셋 맞춰주기
    mysql_query(connPtr, "set session character_set_connection=euc_kr;");
    mysql_query(connPtr, "set session character_set_results=euc_kr;");
    mysql_query(connPtr, "set session character_set_client=euc_kr;");

    //query 실행
    const char* query = "select * from account";
    stat = mysql_query(connPtr, query);
    if (stat != DB_QUERY_SUCCESS)
    {
        cout << "error querty" << endl;
        mysql_close(connPtr);

        return -1;
    }

    result = mysql_store_result(connPtr);
    while (row = mysql_fetch_row(result))
    {
        cout << row[0] << " " << row[1] << " " << row[2] << endl;
    }
    mysql_free_result(result);


    mysql_close(connPtr);

    return 0;
}