#include "Header.h"
#include "MediaClasses.h"

#pragma region MediaBase
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
void MediaBase::setType(string type) { this->type = type; }
#pragma endregion

#pragma region Movie
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

//Formats for file
string Movie::formatInfo()
{
	stringstream format;
	format << getType() << endl
		<< getTitle() << endl
		<< getLength() << endl
		<< getDirector() << endl;

	return format.str();
}

//Prints for user
void Movie::print()
{
	cout << "Title: " << getTitle() << endl;
	cout << "Director: " << getDirector() << endl;
	cout << "Runtime: " << *time << endl;
}
#pragma endregion

#pragma region TVShow
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
	//Tv Show destructed
}

//Getters
int TVShow::getSeasonLength() { return seasonLength; }
int TVShow::getEpisodeCount() { return episodeCount; }

//Formats for file
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

//Prints for user
void TVShow::print()
{
	cout << "Title: " << getTitle() << endl;
	cout << "Seasons: " << getSeasonLength() << endl;
	cout << "Episodes per Season: " << getEpisodeCount() << endl;
	cout << "Episode Runtime: " << *time << endl;
}
#pragma endregion

#pragma region Song
// --------------------- Song --------------------- //
Song::Song(string title, Time* time, string leadArtist, string album) : MediaBase(title, time)
{
	setType(TYPES[2]);
	this->leadArtist = leadArtist;
	this->album = album;
}

Song::Song() : MediaBase()
{
	setType(TYPES[2]);
	cin.ignore();
	getInput(leadArtist, "Who is the lead Artist: ");
	getInput(album, "What Album is it apart of: ");
}

Song::~Song()
{
	//Song destructed
}

string Song::getLeadArtist() { return leadArtist; }
string Song::getAlbum() { return album; }

//Formats for file
string Song::formatInfo()
{
	stringstream format;
	format << getType() << endl
		<< getTitle() << endl
		<< getLength() << endl
		<< getLeadArtist() << endl
		<< getAlbum() << endl;

	return format.str();
}

//Prints for user
void Song::print()
{
	cout << "Title: " << getTitle() << endl;
	cout << "Album: " << getAlbum() << endl;
	cout << "Lead Artist: " << getLeadArtist() << endl;
	cout << "Song Length: " << *time << endl;
}
#pragma endregion

#pragma region Podcast
// --------------------- Podcast --------------------- //
Podcast::Podcast(string title, Time* time, string host, string platform) : MediaBase(title, time)
{
	setType(TYPES[3]);
	this->host = host;
	this->platform = platform;
}

Podcast::Podcast() : MediaBase()
{
	setType(TYPES[3]);
	cin.ignore();
	getInput(host, "Who is the Host: ");
	getInput(platform, "What Platform is it on: ");
}

Podcast::~Podcast()
{
	//Podcast destructed
}

string Podcast::getHost() { return host; }
string Podcast::getPlatform() { return platform; }

//Formats for file
string Podcast::formatInfo()
{
	stringstream format;
	format << getType() << endl
		<< getTitle() << endl
		<< getLength() << endl
		<< getHost() << endl
		<< getPlatform() << endl;

	return format.str();
}

//Prints for user
void Podcast::print()
{
	cout << "Title: " << getTitle() << endl;
	cout << "Host: " << getHost() << endl;
	cout << "Platform: " << getPlatform() << endl;
	cout << "Song Length: " << *time << endl;
}
#pragma endregion


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

			MediaBase* newMedia = new Movie(title, new Time(seconds), director);
			vec.push_back(newMedia);
		}
		else if (data == TYPES[1])
		{
			string title;
			getline(fin, title);

			int seconds;
			fin >> seconds;
			fin.ignore();

			int seasons;
			fin >> seasons;
			fin.ignore();

			int episodes;
			fin >> episodes;
			fin.ignore();

			MediaBase* newMedia = new TVShow(title, new Time(seconds), seasons, episodes);
			vec.push_back(newMedia);
		}
		else if (data == TYPES[2])
		{
			string title;
			getline(fin, title);

			int seconds;
			fin >> seconds;
			fin.ignore();

			string artist;
			getline(fin, artist);

			string album;
			getline(fin, album);

			MediaBase* newMedia = new Song(title, new Time(seconds), artist, album);
			vec.push_back(newMedia);
		}
		else if (data == TYPES[3])
		{
			string title;
			getline(fin, title);

			int seconds;
			fin >> seconds;
			fin.ignore();

			string host;
			getline(fin, host);

			string platform;
			getline(fin, platform);

			MediaBase* newMedia = new Podcast(title, new Time(seconds), host, platform);
			vec.push_back(newMedia);
		}
	}
}
void writeToFile(vector<MediaBase*>& vec, const string& filename)
{
	ofstream fout(filename);
	for (int i = 0; i < vec.size(); i++)
	{
		fout << vec[i]->formatInfo();
	}
	fout.close();
}