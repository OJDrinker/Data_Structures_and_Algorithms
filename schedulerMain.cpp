#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "PendingProcess.h"

#include "Scheduler.cpp"

vector<PendingProcess> readPendingProcessList(istream& in);

using namespace std;


int main() {

	int seconds = 0;

	int SIZE;

	ifstream in;
	in.open("pendingProcessList.csv"); // Open file

	if (!in) { // Exit with an error massage if the file doesn't exist
		cout << "ERROR - File failed to open. make sure that "
			<< "the input file and this file are in the "
			<< "same directory" << endl;
	}

	vector <PendingProcess> list = readPendingProcessList(in);

	Scheduler obj;
	for (PendingProcess& a : list) obj.add(a);
	while (obj.empty())
	{
	cout << "Second " << ":" << obj.next() << endl;
	seconds++;
	}

	in.close();

	return 0;
}

vector<PendingProcess>readPendingProcessList(istream & in) {
	string name;
	int timeRemaining;
	string line;
	string token;
	vector<PendingProcess> ProcessList;

	while (getline(in, line)) {
		// cout << line << endl;
		size_t pos = line.find(",");
		name = line.substr(0, pos);
		//cout << name;
		timeRemaining = stoi(line.substr(pos + 1));
		//cout << timeRemaining;
		PendingProcess proc(name, timeRemaining);
		ProcessList.push_back(proc);
		// cout << name << " " << timeRemaining;
	}
	return ProcessList;
}