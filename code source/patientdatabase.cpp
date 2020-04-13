#include "generalFunctions.h"
#include "sqlqueries.h"

string filename = "C:/Users/Kushal/Desktop/patient.csv";  
class patientClass {
private:
	string patientName;
	int patientID;
	string patientDisease;
	int patientage;

public:
	patientClass() {}

	patientClass(string name, int id, string disease, int age)
	{
		patientName = name;
		patientID = id;
		patientDisease = disease;
		patientage = age;
	}

	string getName() {
		return patientName;
	}

	string getDisease() {
		return patientDisease;
	}

	int getId() {
		return patientID;
	}

	int getage() {
		return patientage;
	}

	void setName(string name) {
		patientName = name;
	}

	void setdisease(string disease) {
		patientDisease = disease;
	}

	void setId(int id) {
		patientID = id;
	}

	void setage(int age) {
		patientage = age;
	}

};

class patientDataabase {
private:
	patientClass* patients;
	int count;
public:
	patientDataabase(int size) {
		patients = new patientClass[size];
		count = size;
	}
	patientDataabase() {}

	void addPatientInfo(patientClass patientobj);
	void removePatientInfo(int id);
	void updatepatientInfo(patientClass patientobj);
	void findPatient(int id);
};

void patientDataabase::addPatientInfo(patientClass patientobj) {

	for (int i = 0; i < count; i++)
	{
		if (patients[i].getName() == "") {

			patients[i] = patientobj;
			break;
		}
	}
}
void patientDataabase::updatepatientInfo(patientClass patientobj) {
	for (int i = 0; i < count; i++)
	{
		if (patients[i].getId() == patientobj.getId()) {

			patients[i] = patientobj;

		}
	}
}
void patientDataabase::removePatientInfo(int id) {
	for (int i = 0; i < count; i++)
	{
		if (patients[i].getId() == id) {

			patients[i].setId(0);
			patients[i].setName("");
			patients[i].setdisease("");
			patients[i].setage(0);

		}
	}

}

void patientDataabase::findPatient(int num) {
	cout << count;
	for (int i = 0; i < count; i++) {
		if (patients[i].getId() == num) {
			cout << "\nPatient Name: " << patients[i].getName() << "\n";
			cout << "\nPatient ID: " << patients[i].getId() << "\n";
			cout << "\nPatient Disease : " << patients[i].getDisease() << "\n";
			cout << "\nPatient Age: " << patients[i].getage() << "\n\n";

		}
	}
}

string userMenu() {
	string menu = "\n~~~~~~~~~~~~~~PATIENT REGISTRY~~~~~~~~~~~~~~~~\n\n";
	menu += "To Add New Patient's Details:       PRESS 1\n";
	menu += "To Update a Patient's Information   PRESS 2\n";
	menu += "To Remove a Patient's Details:      PRESS 3\n";
	menu += "To Find Patient Details:            PRESS 4\n";
	menu += "Press any other key to exit\n";
	return menu;
}

patientDataabase* globj;

void csvfile(int id,string name, string disease, int age){
	ofstream file;
	string line="";
	file.open(filename.c_str(),ios::app);
	getline(cin,line);
	file<<id<<","<<name<<","<<disease<<","<<age<<endl;
	file.close();
}

void addOperation() {
	string name = getString("enter patient's name:");
	int id = getNumber("enter patient's Id: ");
	string disease = getString("enter patient's disease: ");
	int age = getNumber("Enter patient's Age: ");
	patientClass obj(name, id, disease, age);

	insertToDatabase(id, name, disease,age);
	
	globj->addPatientInfo(obj);
	csvfile(id, name, disease, age);
}

void updateOperation() {
	int id = getNumber("enter patient's Id: ");
	string name = getString("enter patient's name: ");
	string disease = getString("enter patient's disease");
	int age = getNumber("Enter patient's Age: ");

	patientClass obj(name, id, disease, age);

	updateDatabase(id, name, disease,age);
	globj->updatepatientInfo(obj);
}
void removeOperation() {
	int id = getNumber("enter patient's Id");
	deleteFromDb(id);
	globj->removePatientInfo(id);
}

void findOperation() {
	int id = getNumber("enter patient's Id");
  	globj->findPatient(id);
	displayDetails(id);
}

void process(int choice) {
	switch (choice) {
	case 1:
		addOperation();
		break;
	case 2:
		updateOperation();
		break;
	case 3:
		removeOperation();
		break;
	case 4:
		findOperation();
		break;
	default:
		break;
	}
}
int main()
{
	int size = getNumber("Enter the number of patients");
	globj = new patientDataabase(size);
	int choice;
	string menu = userMenu();
	do {
		choice = getNumber(menu);
		process(choice);
	} while (choice < 5);

	return 0;
}
