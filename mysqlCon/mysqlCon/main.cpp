#include <iostream>
#include <mysql.h>
#include "DBCon.h"

//������Ʈ �������� �߰����� ����, �̷��� �߰��ص� �ȴ�.
//#pragma comment(lib, "libmysql.lib")

using ::std::cout;
using ::std::endl;
const int DB_QUERY_SUCCESS = 0;

int main()
{
    //mysql + c++�����ϱ�(�̶������� �ܼ��� mysql lib�� �����ؼ� ��� �׽�Ʈ������, ���� server�� ������ �� �ƴ�)
    cout << mysql_get_client_info() << endl;

    MYSQL conn;			//mysql ������ ��� ����ü
    MYSQL* connPtr;		//mysql�ڵ�
    MYSQL_RES* result;	//���� ��û�� ��� ����ü������
    MYSQL_ROW row;		//���� ��û�� ��ȯ�� �ο�(��)
    int stat;		    //���� ��û�� ���(����,����)

    mysql_init(&conn);	//mysql ���� ����ü �ʱ�ȭ
    //mysql���� ����, local�� ���������, �ּ��ΰ�� �ܺ� ���ӵǰ� ���� �����ؾ� �Ѵ�.
    connPtr = mysql_real_connect(&conn, "192.168.35.179", "nicecapj", "epdlxjqpdltm82!", "mydb", 3306, nullptr, 0);
    if (!connPtr)
    {
        cout << "error connect" << endl;
        return -1;
    }

    //db�� ���ڿ��� vs���ڿ��� �����ֱ�
    mysql_query(connPtr, "set session character_set_connection=euc_kr;");
    mysql_query(connPtr, "set session character_set_results=euc_kr;");
    mysql_query(connPtr, "set session character_set_client=euc_kr;");

    //query ����
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