#include "Header.h"

MediaBase::MediaBase(string title, Time* time)
{
	this->title = title;
	this->time = time;
}
MediaBase::MediaBase()
{
	cin.ignore();
	getInput(title, "Enter the title: ");
	time = new Time();
}
MediaBase::~MediaBase()
{
	cout << "Media Destroyed!\n";
	delete time;
	time = nullptr;
}

//Getters
string MediaBase::getTitle() { return title; }
string MediaBase::getType() { return type; }
int MediaBase::getLength() { return time->getSeconds(); }
string MediaBase::getFormatedTime() { return time->format(); }

void MediaBase::setType(string type) { this->type = type; }

// --------------------- Movie --------------------- //
Movie::Movie(string title, Time* time, string director) : MediaBase(title, time)
{
	setType(TYPES[0]);
	this->director = director;
}

Movie::Movie() : MediaBase()
{
	cout << "Movie Created!\n";
	setType(TYPES[0]);
	cin.ignore();
	getInput(director, "Enter the director: ");
}
Movie::~Movie()
{
	cout << "Movie Destroyed!\n";
}

//Getters
string Movie::getDirector() { return director; }

string Movie::formatInfo()
{
	stringstream format;
	format << getType() << endl
		<< getTitle() << endl
		<< getLength() << endl
		<< getDirector() << endl;

	return format.str();
}

void Movie::print()
{
	cout << getTitle() << endl;
	cout << getFormatedTime();
	cout << getDirector() << endl;
}