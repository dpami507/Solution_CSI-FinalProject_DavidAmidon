#pragma once
#include "Header.h"
class MediaBase
{
public:
	MediaBase(string title, Time* time);
	MediaBase();
	~MediaBase();

	virtual string formatInfo() = 0;
	virtual void print() = 0;

	//Getters
	string getTitle();
	string getType();
	int getLength();
	string getFormatedTime();

	void setType(string type);

private:
	string title;
	string type;
	Time* time;
};

class Movie : public MediaBase
{
public:
	Movie(string title, Time* time, string director);
	Movie();
	~Movie();

	//Getters
	string getDirector();

	virtual string formatInfo();

	virtual void print() override;

private:
	string director;
};