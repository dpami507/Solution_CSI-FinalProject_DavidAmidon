#pragma once
#include "Header.h"
#include "Time.h"

class MediaBase
{
public:
	MediaBase();
	MediaBase(string title, Time* time);
	~MediaBase();

	virtual string formatInfo() = 0;
	virtual void print() = 0;

	//Getters
	string getTitle();
	string getType();
	int getLength();

	void setType(string type);
protected:
	Time* time;

private:
	string title;
	string type;
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

class TVShow : public MediaBase
{
public:
	TVShow(string title, Time* time, int seasonLength, int episodeCount);
	TVShow();
	~TVShow();

	//Getters
	int getSeasonLength();
	int getEpisodeCount();

	virtual string formatInfo();

	virtual void print() override;

private:
	int seasonLength;
	int episodeCount;
};

class Song : public MediaBase
{
public:
	Song(string title, Time* time, string leadArtist, string album);
	Song();
	~Song();

	//Getters
	string getLeadArtist();
	string getAlbum();

	virtual string formatInfo();

	virtual void print() override;

private:
	string leadArtist;
	string album;
};

class Podcast : public MediaBase 
{
public:
	Podcast(string title, Time* time, string leadArtist, string album);
	Podcast();
	~Podcast();

	//Getters
	string getHost();
	string getPlatform();

	virtual string formatInfo();

	virtual void print() override;

private:
	string host;
	string platform;
};

void fillVectorWithFile(vector<MediaBase*>& vec, const string& filename);
void writeToFile(vector<MediaBase*>& vec, const string& filename);
