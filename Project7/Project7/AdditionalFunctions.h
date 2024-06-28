#pragma once
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

#define red "\033[31m"
#define reset "\033[0m"

using namespace std;


class Appointment {
	int id;
	string name;
	int age;
	int number;
	string doctor;
	int floor;
	int cabinet;
	string time;
	string notes;

public:
	Appointment();
	Appointment(int i, const string& n, int a, int num, const string& d, int f, int c, const string& t, const string& note);
	~Appointment();


	int getID() const;
	string getName() const;
	int getNumber() const;
	int getAge()const;
	string getDoctor()const;
	int getFloor() const;
	int getCabinet() const;
	string getTime() const;
	string getNotes()const;

	bool validID(vector<Appointment>& appointments, int id);

	friend ostream& operator<<(ostream& os, const Appointment& app);

	friend istream& operator>>(istream& is, Appointment& app);

	void addAppointment(vector<Appointment>& appointments);

	void deleteAppointment(vector<Appointment>& appointments);

	void updateInfo(vector<Appointment>& appointments);

	void printAppointments(const vector<Appointment>& appointments);

	void saveToFile(const vector<Appointment>& appointments, const string& filename);

	void loadFromFile(vector <Appointment>& appointments, const string& filename);

	void showAppoint(const Appointment& app);

	void searchByName(vector<Appointment>& appointments);

	void searchByDoctor(vector <Appointment>& appointments);

	void sortByTime(vector<Appointment>& appointments);

	void archiveAppointment(vector<Appointment>& appointments, vector<Appointment>& archive, const string& filename);

	void readFromFile();

	void saveToFileArchive(vector<Appointment>& archive);

	void opers();
};


class fileAvailability : public exception {
private:
	string message;
public: fileAvailability(const string& m) : message(m) {}
	  virtual const char* what() const noexcept override {
		  return message.c_str();
	  }
};



bool validationTime(const string& time);

