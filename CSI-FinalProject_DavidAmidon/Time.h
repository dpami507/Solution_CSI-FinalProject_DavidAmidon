/*
Author        : David Amidon
Class         : CSI - 240 : Advanced Programming
Assignment    : CSI-240 Final Project
*/

#pragma once
#include "Header.h"

class Time
{
public:
	Time(int seconds);
	Time();
	void fixTime();
	void setTimeFromSeconds(const int& i);
	int getSeconds();
	string format();

private:
	int hours;
	int minutes;
	int seconds;
	friend ostream& operator<<(ostream& out, const Time& time);
};