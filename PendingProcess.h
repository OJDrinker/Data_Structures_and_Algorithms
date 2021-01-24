#include <iostream>

#include <string>

using namespace std;

struct PendingProcess
{
public:
	string name;

	int timeRemaining;

	PendingProcess(string name, int timeRemaining) : name(name), timeRemaining(timeRemaining) {}
};
