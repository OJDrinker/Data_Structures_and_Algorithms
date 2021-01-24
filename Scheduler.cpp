#include "Scheduler.h"

void Scheduler::add(PendingProcess a)
{
	q.push(a);
}

string Scheduler::next()
{
	PendingProcess obj = q.front();
	q.pop();
	if (obj.timeRemaining > 1)
	{
		obj.timeRemaining--;
		q.push(obj);
	}
	return obj.name;
}

bool Scheduler::empty()
{
	if (q.empty())
		return false;
	else
		return true;

}