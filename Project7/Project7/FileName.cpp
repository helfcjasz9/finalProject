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



namespace OpersSpace {

	void mainOperations() {
		cout << "1 - add appointment" << endl;
		cout << "2 - delete appointment" << endl;
		cout << "3 - update info about appointment" << endl;
		cout << "4 - searching" << endl;
		cout << "5 - exit" << endl;
		cout << "Operation >> ";
	}

	void operations() {
		cout << "1 - operations" << endl;
		cout << "2 - archive" << endl;
		cout << "3 - exit" << endl;
		cout << "Operation >> ";
	}

}



void archiveRecursive(Appointment& list, vector<Appointment>& appoints, vector<Appointment>& archive, const string& archivePath, int& op) {
	while (op != 3) {
		list.archiveAppointment(appoints, archive, archivePath);

		if (appoints.empty()) {
			cout << "* * * No Appoints Yet * * *" << endl;
		}

		list.sortByTime(appoints);
		list.printAppointments(appoints);
		OpersSpace::operations();

		for (int i = 0; i < 60; ++i) {
			if (op == 3) {
				return;
			}
			this_thread::sleep_for(chrono::seconds(1));
		}

		system("cls");
	}
}



void main() {

	Appointment list;
	vector<Appointment> appoints;
	vector<Appointment> archive;

	string appointsPath = "appointments.txt";
	string archivePath = "archive.txt";
	int op,  oper, search, a;
	

	appoints.clear();

	list.loadFromFile(appoints, appointsPath);
	

	thread archiver(archiveRecursive, ref(list), ref(appoints), ref(archive), ref(archivePath), ref(op));

	do {

		cin >> op;
		switch (op) {
		case 1:
			do {
				OpersSpace::mainOperations();
				cin >> oper;
				switch (oper) {
				case 1:
					list.addAppointment(appoints);
					system("cls");
					break;
				case 2:
					list.printAppointments(appoints);
					list.deleteAppointment(appoints);
					system("cls");
					break;
				case 3:
					list.updateInfo(appoints);
					system("cls");
					break;
				case 4:
					cout << "1 - by name of patient" << endl;
					cout << "2 - doctor" << endl;
					cout << "Choice >> ";
					cin >> search;

					switch (search) {
					case 1:
						list.searchByName(appoints);
						break;
					case 2:
						list.searchByDoctor(appoints);
						break;
					default:
						cout << red << "Invalid operation!" << reset << endl;
						cout << "1 - by name of patient" << endl;
						cout << "2 - doctor" << endl;
						cout << "Choice >> ";
						cin >> search;
					}
					break;
				case 5:
					list.saveToFile(appoints, appointsPath);
					system("cls");
					break;
				default:
					cerr << red << "Invalid operation!" << reset << endl;
					OpersSpace::mainOperations();
					cin >> oper;
				}
			} while (oper != 5);
			system("cls");
			break;
		case 2:
			list.readFromFile();
			cout << "Press 0 to leave: ";
			cin >> a;
			if (a == 0) {
				system("cls");
				break;
			}
			break;
		case 3:
			list.saveToFile(appoints, appointsPath);
			break;
		default:
			cout << "INVALID OPERATION!" << endl;
			OpersSpace::operations();
			cin >> op;
		}


	} while (op != 3);

	if (archiver.joinable()) {
		archiver.join();
	}



}