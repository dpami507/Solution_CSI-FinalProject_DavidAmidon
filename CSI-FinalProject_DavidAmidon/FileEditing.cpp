#include "Header.h"
#include "MediaClasses.h"

MediaBase* mediaType()
{
	cout << "\nWhat Type of Media are you adding?\n";

	//Print types
	for (int i = 0; i < TYPES_LENGTH; i++)
	{
		cout << i << ". " << setw(10) << left << TYPES[i];
	}
	cout << endl;

	//Get user choice
	int choice;
	getInput(choice, "Choice: ");

	MediaBase* type;

	//return type
	switch (choice)
	{
	case 0:
		type = new Movie();
		return type;
	case 1:
		type = new TVShow();
		return type;
	case 2:
		type = new Song();
		return type;
	case 3:
		type = new Podcast();
		return type;
	default:
		string msg = "[!] Not an Option [!]\n";
		throw msg;
	}
}

void addMedia(vector<MediaBase*>& vec)
{
	MediaBase* newMedia;

	try
	{
		newMedia = mediaType();
	}
	catch (const string& msg)
	{
		cout << msg;
		return;
	}
	catch (...)
	{
		cout << "[!] DEV_ERR: WRONG THROW TYPE [!]\n";
		return;
	}
	vec.push_back(newMedia);
}

void deleteMedia(vector<MediaBase*>& vec)
{
	cin.ignore();
	string titleToDelete;
	getInput(titleToDelete, "What is the Title you want to delete: ");

	for (int i = 0; i < vec.size(); i++)
	{
		if (vec.at(i)->getTitle() == titleToDelete)
		{
			vec.erase(vec.begin() + i);
			return;
		}
	}

	cout << "[!] Title not found [!]\n";
}

void editMedia(vector<MediaBase*>& vec)
{
	cin.ignore();
	string titleToEdit;
	getInput(titleToEdit, "What is the Title you want to edit: ");

	for (int i = 0; i < vec.size(); i++)
	{
		if (vec.at(i)->getTitle() == titleToEdit)
		{
			MediaBase* newMedia;

			newMedia = mediaType();
			vec[i] = newMedia;
			return;
		}
	}
}