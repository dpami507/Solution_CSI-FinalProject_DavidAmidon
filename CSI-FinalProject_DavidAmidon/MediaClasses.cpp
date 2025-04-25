#include "Header.h"
#include "MediaClasses.h"

MediaBase::MediaBase()
{
	cin.ignore();
	getInput(title, "Enter the title: ");
	time = new Time();
}
MediaBase::MediaBase(string title, Time* time)
{
	this->title = title;
	this->time = time;
}
MediaBase::~MediaBase()
{
	//cout << "Media Destroyed!\n";
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
	//cout << "Movie Created!\n";
	setType(TYPES[0]);
	cin.ignore();
	getInput(director, "Enter the director: ");
}
Movie::~Movie()
{
	//cout << "Movie Destroyed!\n";
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

// --------------------- TV Show --------------------- //
TVShow::TVShow(string title, Time* time, int seasonLength, int episodeCount) : MediaBase(title, time)
{
	setType(TYPES[1]);
	this->seasonLength = seasonLength;
	this->episodeCount = episodeCount;
}
TVShow::TVShow() : MediaBase()
{
	//cout << "Movie Created!\n";
	setType(TYPES[1]);
	cin.ignore();
	getInput(seasonLength, "How many Seasons are there: ");
	getInput(episodeCount, "How many Episodes are in a Season: ");
}
TVShow::~TVShow()
{
	//Tv Show destructered
}

//Getters
int TVShow::getSeasonLength() { return seasonLength; }
int TVShow::getEpisodeCount() { return episodeCount; }

string TVShow::formatInfo()
{
	stringstream format;
	format << getType() << endl
		<< getTitle() << endl
		<< getLength() << endl
		<< getSeasonLength() << endl
		<< getEpisodeCount() << endl;

	return format.str();
}

void TVShow::print()
{
	cout << getTitle() << endl;
	cout << getFormatedTime();
	cout << getSeasonLength() << endl;
	cout << getEpisodeCount() << endl;
}


void fillVectorWithFile(vector<MediaBase*>& vec, const string& filename)
{
	ifstream fin(filename);

	while (!fin.eof())
	{
		string data;
		getline(fin, data);
		if (data == TYPES[0])
		{
			string title;
			getline(fin, title);

			int seconds;
			fin >> seconds;
			fin.ignore();

			string director;
			getline(fin, director);

			MediaBase* newMovie = new Movie(title, new Time(seconds), director);
			vec.push_back(newMovie);
		}
	}
}

void writeToFile(vector<MediaBase*>& vec, const string& filename)
{
	ofstream fout(filename);
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i]->formatInfo();
		fout << vec[i]->formatInfo();
	}
	fout.close();
}