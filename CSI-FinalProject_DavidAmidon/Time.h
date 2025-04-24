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
};