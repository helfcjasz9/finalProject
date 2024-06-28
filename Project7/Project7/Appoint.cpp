#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <regex>
#include <algorithm>
#include <thread>
#include <conio.h>
#include "AdditionalFunctions.h"
#include <atomic>
#define red "\033[31m"
#define reset "\033[0m"

using namespace std;



Appointment::Appointment() : id(0), name(""), age(0), number(0), doctor(""), floor(0), cabinet(0), time(""), notes("") {}
Appointment::Appointment(int i, const string& n, int a, int num, const string& d, int f, int c, const string& t, const string& note) : id(i), name(n),
age(a), number(num), doctor(d), floor(f), cabinet(c), time(t), notes(note) {}


Appointment::~Appointment() {}

int Appointment::getID() const { return id; }
string Appointment::getName() const { return name; }
int Appointment::getNumber() const { return number; }
int Appointment::getAge()const { return age; }
string Appointment::getDoctor()const { return doctor; }
int Appointment::getFloor() const { return floor; }
int Appointment::getCabinet() const { return cabinet; }
string Appointment::getTime() const { return time; }
string Appointment::getNotes()const { return notes; }

void opers();


bool Appointment::validID(vector<Appointment>& appointments, int id) {
	for (const auto& app : appointments) {
		if (app.id == id) {
			return false;
		}
	}
	return true;
}




ostream& operator<<(ostream& os, const Appointment& app) {
	os << app.id << endl;
	os << app.name << endl;
	os << app.age << endl;
	os << app.number << endl;
	os << app.doctor << endl;
	os << app.floor << endl;
	os << app.cabinet << endl;
	os << app.time << endl;
	os << app.notes << endl;

	return os;
}

istream& operator>>(istream& is, Appointment& app) {

	string line;

	if (getline(is, line)) { app.id = stoi(line); }

	getline(is, app.name);

	if (getline(is, line)) { app.age = stoi(line); }

	if (getline(is, line)) { app.number = stoi(line); }

	getline(is, app.doctor);

	if (getline(is, line)) { app.floor = stoi(line); }

	if (getline(is, line)) { app.cabinet = stoi(line); }

	getline(is, app.time);

	getline(is, app.notes);

	return is;
}


void Appointment::addAppointment(vector<Appointment>& appointments) {

	cout << "Enter id: ";
	cin >> id;

	while (!validID(appointments, id)) {
		cout << red << "ID must be unique!" << reset << endl;
		cout << "Enter id: ";
		cin >> id;
	}

	cout << "Enter name and surname: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter age: ";
	cin >> age;
	cout << "Enter number of patient room: ";
	cin >> number;
	cout << "Enter specialization of doctor: ";
	cin.ignore();
	getline(cin, doctor);
	cout << "Enter floor: ";
	cin >> floor;
	cout << "Enter cabinet: ";
	cin >> cabinet;
	cout << "Enter time: ";
	cin >> time;

	while (!validationTime(time)) {
		cout << "Enter time: ";
		cin >> time;
	}
	cout << "Enter notes: ";
	cin.ignore();
	getline(cin, notes);

	appointments.push_back(Appointment(id, name, age, number, doctor, floor, cabinet, time, notes));
}


void Appointment::deleteAppointment(vector<Appointment>& appointments) {
	int id;
	bool found = false;

	cout << "Enter ID of the appointment to delete(0 - back): ";
	cin >> id;

	if (id == 0) {
		return;
	}

	while (!found) {


		for (const auto& app : appointments) {
			if (app.id == id) {
				found = true;
				break;
			}
		}

		if (!found) {
			cout << red << "You have entered incorrect ID!" << reset << endl;
			cout << "Enter ID of the appointment to delete: ";
			cin >> id;
		}


		for (auto i = appointments.begin(); i != appointments.end();) {
			if (i->id == id) {
				i = appointments.erase(i);
			}
			else {
				i++;
			}
		}
	}


}


void Appointment::updateInfo(vector<Appointment>& appointments) {

	string nameP, doc, t, note;
	int numPR, ag, oper, fl, cab;
	bool found = false;


	while (!found) {
		cout << "Enter ID of the trip to change info in: ";
		cin >> id;

		for (const auto& app : appointments) {
			if (app.id == id) {
				found = true;
				break;
			}
		}

		if (!found) {
			cout << red << "You have entered incorrect ID" << reset << endl;
		}
	}


	for (auto i = appointments.begin(); i < appointments.end(); i++) {
		if (i->id == id) {
			opers();
			cin >> oper;

			switch (oper) {
			case 1:
				cout << "Name & surname: ";
				cin.ignore();
				getline(cin, nameP);
				i->name = nameP;
				break;
			case 2:
				cout << "Age: ";
				cin >> ag;
				i->age = ag;
				break;
			case 3:
				cout << "Patient room: ";
				cin >> numPR;
				i->number = numPR;
				break;
			case 4:
				cout << "Doctor's specialization: ";
				cin.ignore();
				getline(cin, doc);
				i->doctor = doc;
				break;
			case 5:
				cout << "Floor: ";
				cin >> fl;
				i->floor = fl;
				break;
			case 6:
				cout << "Cabinet: ";
				cin >> cab;
				i->cabinet = cab;
				break;
			case 7:
				cout << "Time: ";
				cin >> t;
				i->time = t;
				break;
			case 8:
				cout << "Notes: ";
				cin.ignore();
				getline(cin, note);
				i->notes = note;
				break;
			case 9:
				break;
			default:
				cout << "Invalid operation! Try again!" << endl;
				opers();
				cin >> oper;
			}
		}
	}



}


void Appointment::printAppointments(const vector<Appointment>& appointments) {

	for (auto& app : appointments) {
		showAppoint(app);
	}
}


void Appointment::saveToFile(const vector<Appointment>& appointments, const string& filename) {
	try {
		ofstream ofile(filename);

		if (!ofile.is_open()) {
			throw fileAvailability("Unable to open the file!");
		}

		for (const auto& app : appointments) {
			ofile << app;
		}
		ofile.close();
	}
	catch (const fileAvailability& e) {
		cerr << "ERROR: " << e.what() << endl;
	}

}



void Appointment::loadFromFile(vector <Appointment>& appointments, const string& filename) {

	try {
		ifstream ifile(filename);

		if (!ifile.is_open()) {
			throw fileAvailability("Unable to open file!");
		}


		Appointment app;

		while (ifile >> app) {
			appointments.push_back(app);
		}

		ifile.close();
	}
	catch (const fileAvailability& e) {
		cerr << "ERROR: " << e.what() << endl;
	}

}






void Appointment::showAppoint(const Appointment& app) {
	cout << "----------------------------------------------------------------------" << endl;
	cout << "|" << setw(35) << "ID: " << red << app.id << reset << endl;
	cout << "| Patient: " << setw(15) << red << app.name << reset << setw(20) << "Age: " << red << app.age << reset << endl;
	cout << "| Patient room: " << setw(8) << red << app.number << reset << endl;
	cout << "| Doctor: " << setw(8) << red << app.doctor << reset << setw(30) << "Location: " << red << app.floor << "fl. " << app.cabinet << "cab." << reset << endl;
	cout << "| Time: " << setw(10) << red << app.time << reset << endl;
	cout << "| Notes: " << red << app.notes << reset << endl;
	cout << "----------------------------------------------------------------------" << endl;
}


void Appointment::searchByName(vector<Appointment>& appointments) {

	string nameToSearch;
	bool found = false;

	cout << "Enter name to search by: ";
	cin.ignore();
	getline(cin, nameToSearch);

	for (const auto& app : appointments) {

		if (app.name == nameToSearch) {
			showAppoint(app);
			cout << endl;
			found = true;
		}
	}

	if (!found) {
		cerr << red << "Not found!" << reset << endl;
	}

}

void Appointment::searchByDoctor(vector <Appointment>& appointments) {
	string doc;
	bool found = false;

	cout << "Enter doctor: ";
	cin.ignore();
	getline(cin, doc);

	for (const auto& app : appointments) {
		if (app.doctor == doc) {
			showAppoint(app);
			cout << endl;
			found = true;
		}
	}

	if (!found) {
		cerr << red << "Not found!" << reset << endl;
	}

}

void Appointment::sortByTime(vector<Appointment>& appointments) {

	auto compareTime = [](const Appointment& a, const Appointment& b) {
		int hA = stoi(a.getTime().substr(0, 2));
		int mA = stoi(a.getTime().substr(3, 5));
		int hB = stoi(b.getTime().substr(0, 2));
		int mB = stoi(b.getTime().substr(3, 5));

		if (hA == hB) {
			return mA < mB;
		}
		else {
			return hA < hB;
		}
		};


	sort(appointments.begin(), appointments.end(), compareTime);

}



void Appointment::archiveAppointment(vector<Appointment>& appointments, vector<Appointment>& archive, const string& filename) {


	auto now = chrono::system_clock::now();
	time_t nowTime = chrono::system_clock::to_time_t(now);

	tm localTime;
	localtime_s(&localTime, &nowTime);

	for (auto i = appointments.begin(); i != appointments.end();) {
		int hours = stoi(i->getTime().substr(0, 2));
		int minutes = stoi(i->getTime().substr(3, 5));

		if (localTime.tm_hour > hours || (localTime.tm_hour == hours && localTime.tm_min > minutes)) {
			archive.push_back(*i);
			i = appointments.erase(i);
		}
		else {
			i++;
		}
	}

	saveToFileArchive(archive);

}




void Appointment::readFromFile() {

	try {

		ifstream ifile("archive.txt");

		if (!ifile.is_open()) {
			throw fileAvailability("Unable to open the file!");
		}

		string line;

		while (getline(ifile, line)) {
			cout << line << endl;
		}

	}
	catch (const fileAvailability& e) {
		cerr << red << "ERROR: " << e.what() << reset << endl;
	}

}


void Appointment::saveToFileArchive(vector<Appointment>& archive) {
	try {
		ofstream ofile("archive.txt", ios::app);

		if (!ofile.is_open()) {
			throw fileAvailability("Unable to open the file!");
		}

		for (const auto& arch : archive) {
			ofile << "ID: " << arch.id << endl;
			ofile << "Patient: " << arch.name << endl;
			ofile << "Age: " << arch.age << endl;
			ofile << "Patient room: " << arch.number << endl;
			ofile << "Doctor: " << arch.doctor << endl;
			ofile << "Location: " << arch.floor << "fl. " << arch.cabinet << "cab." << endl;
			ofile << "Time: " << arch.time << endl;
			ofile << "Notes: " << arch.notes << endl;
			ofile << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
		}

		ofile.close();
	}
	catch (const fileAvailability& e) {
		cerr << red << "ERROR: " << e.what() << reset << endl;
	}
}

void Appointment::opers() {
	cout << "Choose what to change: " << endl;
	cout << "1 - name & surname of patient" << endl;
	cout << "2 - age of patient" << endl;
	cout << "3 - nummber of patient room" << endl;
	cout << "4 - doctor" << endl;
	cout << "5 - floor" << endl;
	cout << "6 - cabinet" << endl;
	cout << "7 - time" << endl;
	cout << "8 - notes" << endl;
	cout << "9 - back" << endl;
	cout << "Operation >> ";
}



bool validationTime(const string& time) {

	regex time_format("^([01]?[0-9]|2[0-3]):[0-5][0-9]$");

	if (regex_match(time, time_format)) {
		return true;
	}
	else {
		cerr << red << "You have entered incorrect time" << reset << endl;
		return false;
	}
}



