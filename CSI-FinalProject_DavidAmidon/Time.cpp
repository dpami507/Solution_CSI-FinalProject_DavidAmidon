/*
Author        : David Amidon
Class         : CSI - 240 : Advanced Programming
Assignment    : CSI-240 Final Project
*/

#include "Header.h"
#include "Time.h"

Time::Time(int seconds)
{
	hours = 0;
	minutes = 0;
	this->seconds = seconds;
	fixTime();
}

Time::Time()
{
	cout << "Enter the Hours: ";
	cin >> hours;

	cout << "Enter the Minutes: ";
	cin >> minutes;

	cout << "Enter the Seconds: ";
	cin >> seconds;

	fixTime();
}

void Time::fixTime()
{
	if (seconds >= 60)
	{
		minutes += seconds / 60;
		seconds %= 60;
	}
	if (minutes >= 60)
	{
		hours += minutes / 60;
		minutes %= 60;
	}
}

void Time::setTimeFromSeconds(const int& i)
{
	//Set seconds
	seconds = i;
	minutes = 0;
	hours = 0;

	//Just fix it
	fixTime();
}

int Time::getSeconds()
{
	int totalSeconds = 0;
	totalSeconds += seconds;
	totalSeconds += minutes * 60;
	totalSeconds += hours * 3600;

	return totalSeconds;
}

ostream& operator<<(ostream& out, const Time& time)
{
	out << setfill('0') << setw(2) << time.hours << ":"
		<< setfill('0') << setw(2) << time.minutes << ":"
		<< setfill('0') << setw(2) << time.seconds << endl;
	return out;
}

string Time::format()
{
	stringstream time;
	time << setfill('0') << setw(2) << hours << ":"
		<< setfill('0') << setw(2) << minutes << ":"
		<< setfill('0') << setw(2) << seconds << endl;

	return time.str();
}
