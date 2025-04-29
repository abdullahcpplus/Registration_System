#include<iostream>
#include<windows.h>
#include <string>
#include<mysql.h>
#include<mysqld_error.h>
#include<resultset.h>
#include <statement.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
using namespace std;
class page
{
    string abs;
    string fname,lname,bdate, password, email;

public:
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
    page() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn,"localhost","root","abcd@12345678","sign_up_data",3306,NULL,0)) {
        cout << "ERROR: " << mysql_error(conn)<< endl;
    }
    else {
        cout << "Connected with database," << endl;
    }
    }
    void sign_up();
    void log_in();
    void forgot();
};
void page::sign_up()
{
    system("cls");
    string abd;
    getline(cin, abd);
    cout << "----------sign_up--------------" << endl;
    cout << "Enter first name : " << endl;
    getline(cin, fname);
    cout << "Enter last name :" << endl;
    getline(cin, lname);
    cout << "Enter date of birth(yyyy-mm-dd) :" << endl;
    getline(cin, bdate);
    cout << "Enter your email: ";
    getline(cin, email);
    cout << "Enter Password";
    getline(cin, password);
    string ins = "INSERT INTO signs (first_name,last_name,Dtae_of_birth, email,password)";
    ins += "VALUES ('" + fname + "','" + lname + "','" + bdate + "','" + email + "','" + password + "')";
    if (mysql_query(conn, ins.c_str())) {
        cout << "ERROR: " << mysql_error(conn);
        Sleep(2000);
    }
    else {
        cout << "sigUp successfullly" << endl;
        Sleep(1000);
    }
}
void page::log_in()
{
    system("cls");
    string abd;            // this is only to remove getline error
    getline(cin, abd);     // BEACUSE FIRST GETLINE DOES NOT WORKING
    char dec;
    string searchmail, searchpass;
    string data1="";
    string data2="";
    cout << "------------login-------------" << endl;
    cout << "enter email : " << endl;
    getline(cin, searchmail);
    cout << "enter password : " << endl;
    getline(cin, searchpass);
    string ins = "SELECT* FROM signs WHERE email='" + searchmail + "' and password='" + searchpass + "'";
    if (mysql_query(conn, ins.c_str())) {
        cout << "ERROR: " << mysql_error(conn);
        Sleep(2000);
        return;
    }
    else {
        res = mysql_store_result(conn);
        if ((row = mysql_fetch_row(res))) {
            cout << "Login successfull" << endl;
            cout <<"Id          : " << row[0] << endl;
            cout <<"FirstName   : " << row[1] << endl;
            cout <<"LastName    : " << row[2] << endl;
            cout <<"DateOfBirth : " << row[3] << endl;
            cout <<"Email       : " << row[4] << endl;
            Sleep(2000);
            mysql_close(conn);
          }
        else {
            char cho;
            cout << "invalid email or password" << endl;
            cout << "  1) Try again." << endl;
            cout << "  2) Forgot password." << endl;
            cout << "enter your choice: ";
            cin >> cho;
            if (cho == '1') {
                log_in();
            }
            else if (cho == '2') {
                forgot();
            }
            else {
                log_in();
            }
        }
        mysql_free_result(res);
    }
    char ch;
    cout << "Enter any key to exit";
    cin >> ch;
}
void page::forgot()
{
    system("cls");
    string abd;            // this is only to remove getline error
    getline(cin, abd);     // BEACUSE FIRST GETLINE DOES NOT WORKING
    char dec;
    string searchmail, searchbirth;
    string data1 = "";
    string data2 = "";
    cout << "------------login-------------" << endl;
    cout << "enter Date of birth (yyyy-mm-dd) : " << endl;
    getline(cin, searchbirth);
    cout << "enter eamil : " << endl;
    getline(cin, searchmail);
    string ins = "SELECT* from signs WHERE email='" + searchmail + "' and Dtae_of_birth ='" + searchbirth + "'";
    if (mysql_query(conn, ins.c_str())) {
        cout << "ERROR: " << mysql_error(conn);
        Sleep(2000);
        return;
    }
    else {
        res = mysql_store_result(conn);
        if ((row = mysql_fetch_row(res))) {
            string newpass;
            cout << "Enter newPassword: ";
            getline(cin, newpass);
            string iis = "UPDATE signs SET password='" + newpass + "'";
            if (mysql_query(conn, iis.c_str())) {
                cout << "ERROR: " << mysql_error(conn);
                Sleep(2000);
            }
            else {
                cout << "Password updated succussfully." << endl;
                Sleep(1000);
            }
        }
        else {
            cout << "invalid email or date of birth." << endl;
        }
    }
    char ch;
    cout << "Enter any key to exit";
    cin >> ch;
}
int main()
{
    page obj;
    char choice;
    bool run = true;
    while (run) {
        system("cls");
        cout << "\t\t ________________________________" << endl;
        cout << "\t\t|  1)login                       |" << endl;
        cout << "\t\t|  2)signup                      |" << endl;
        cout << "\t\t|  3)forgot password             |" << endl;
        cout << "\t\t|  4)exit                        |" << endl;
        cout << "\t\t|________________________________|"<< endl;
        cout << "  choose one :";
        cin >> choice;
        if (choice == '1') {
            obj.log_in();
        }
        else if (choice == '2') {
            obj.sign_up();
        }
        else if (choice == '3') {
            obj.forgot();
        }
        else if(choice =='4') {
            run = false;
            cout << "Goodbye, have a nice day." << endl;
            Sleep(1000);
        }
        else {
            system("cls");
            cout << "Entered wrong input." << endl;
            cout << "directing the perious page." << endl;
            Sleep(1000);
        }
    }
    return 0;
}