#pragma once
#include "generalFunctions.h"
#include <mysql.h>
#include <Windows.h>
#include<sstream>
#include<stdio.h>
void updateDatabase(int id, string name, string disease, int age) {
	string dummy;
	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "root", "patient", 0, NULL, 0);
	if (conn) {
		int qstate = 0;  
		stringstream ss;
		ss << "UPDATE patientdata SET patientName = + '" << name << "',patientdisease = +'" << disease << "', Age= +'"<<age<<"'WHERE patientId = '" << id << "'";
		//ss << "UPDATE patientdata SET  '" << disease << "'WHERE patientId = '" << id << "'";

		string query = ss.str();

		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (qstate == 0) {
			cout << "Record Updated..." << endl;
		
		}
		else {
			cout << "Insert Error" << mysql_error(conn) << endl;
			cout << "Press any key to go back";
			cin >> dummy;
		}
	}
	else {
		cout << "Connection Error" << endl;
		cout << "Press any key to go back";
		cin >> dummy;
	}

	system("pause");
	system("cls");

}

void insertToDatabase(int id, string name, string disease, int age) {
	string dummy;

	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "root", "patient", 0, NULL, 0);
	if (conn) {
		int qstate = 0;
		stringstream ss;

		ss << "INSERT INTO patientdata(patientId, patientName, patientdisease, Age) VALUES('" << id << "','" << name << "','" << disease <<"','"<< age<< "')";

		string query = ss.str();
		const char* que = query.c_str();
		qstate = mysql_query(conn, que);
		if (qstate == 0) {
			cout << "Record Inserted..." << endl;
		}
		else {
			cout << "Insert Error" << mysql_error(conn) << endl;
			cout << "Press any key to go back";
			cin >> dummy;
		}
	}
	else {
		cout << "Connection Error" << endl;
		cout << "Press any key to go back";
		cin >> dummy;
	}

	system("pause");
	system("cls");
}


void deleteFromDb(int id) {
	string dummy;

	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "root", "patient", 0, NULL, 0);
	if (conn) {
		int qstate = 0;
		stringstream ss;

		ss << "DELETE FROM patientdata WHERE patientId = + '" << id << "'";

		string query = ss.str();
		const char* que = query.c_str();
		qstate = mysql_query(conn, que);
		if (qstate == 0) {
			cout << "Record Deleted..." << endl;	
		}
		else {
			cout << "Error:  " << mysql_error(conn) << endl;
			cout << "Press any key to go back";
			cin >> dummy;
		}
	}
	else {
		cout << "Connection Error" << endl;
		cout << "Press any key to go back";
		cin >> dummy;
	}

	system("pause");
	system("cls");
}

//void displayDetails(int id) {
//		string dummy;
//	
//		MYSQL* conn;
//		conn = mysql_init(0);
//		conn = mysql_real_connect(conn, "localhost", "root", "root", "patient", 0, NULL, 0);
//		if (conn) {
//			int qstate = 0;
//			stringstream ss;
//
//			ss << "SELECT * FROM patientdata WHERE patientId = + '" << id << "'";
//
//			string query = ss.str();
//			const char* que = query.c_str();
//			qstate = mysql_query(conn, que);
//			if (qstate == 0) {
//				cout << "Record Deleted..." << endl;
//				cout << "Press B to go back";
//				cin >> dummy;
//			}
//			else {
//				cout << "Error:  " << mysql_error(conn) << endl;
//				cout << "Press B to go back";
//				cin >> dummy;
//			}
//		}
//		else {
//			cout << "Connection Error" << endl;
//			cout << "Press B to go back";
//			cin >> dummy;
//		}
//
//		system("pause");
//		system("cls");
//}



void displayDetails(int id) {
	string dummy;

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "root", "patient", 0, NULL, 0);
	if (conn) {
		stringstream ss;
		ss << "SELECT * FROM patientdata WHERE patientId = + '" << id << "'";
		string query = ss.str();
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);


		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				cout << "\npatient id" << "\t | \t" << "patient name" << "\t | \t" << "patient disease" << "\t | \t" << "Age"<< endl;
				cout << row[0] << "        \t | \t" << row[1] << "        \t | \t" << row[2] << "      \t | \t" << row[3] << endl << endl;
			}
		}
	}

	cout << "Press any key to go back";
	cin >> dummy;

	system("pause");
	system("cls");
}