/*
Author        : David Amidon
Class         : CSI - 240 : Advanced Programming
Assignment    : CSI-240 Final Project
*/

#include "Header.h"
#include "MediaClasses.h"

MediaBase* mediaType()
{
	cout << "\nWhat Type of Media are you adding?\n";

	//Print types
	for (int i = 0; i < TYPES_LENGTH; i++)
	{
		cout << setfill(' ');
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
	//Create new type
	MediaBase* newMedia;

	try
	{
		//Get new type from user
		newMedia = mediaType();
	}
	catch (const string& msg)
	{
		//Error if wrong type inputed
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
	//Get title
	cin.ignore();
	string titleToDelete;
	getInput(titleToDelete, "What is the Title you want to delete: ");

	//Check all titles in user vector
	for (int i = 0; i < vec.size(); i++)
	{
		//If it is equal delete it
		if (vec.at(i)->getTitle() == titleToDelete)
		{
			vec.erase(vec.begin() + i);
			return;
		}
	}

	//Runs if title not in vector
	cout << "[!] Title not found [!]\n";
}

void editMedia(vector<MediaBase*>& vec)
{
	//Get user input
	cin.ignore();
	string titleToEdit;
	getInput(titleToEdit, "What is the Title you want to edit: ");

	//Loop through entire vector
	for (int i = 0; i < vec.size(); i++)
	{
		//If title is equal, create new entry at that position allowing for editing
		if (vec.at(i)->getTitle() == titleToEdit)
		{
			MediaBase* newMedia;

			newMedia = mediaType();
			vec[i] = newMedia;
			return;
		}
	}
}

void printAllMedia(vector<MediaBase*>& vec)
{
	//Loop through vector and print media
	cout << "\n===== All Your Media =====\n";
	int counter = 0;
	for (MediaBase* media : vec)
	{
		counter++;
		media->print();
	}

	cout << "Found : " << counter << " results\n";
}

void searchMediaByCatagory(const vector<MediaBase*>& vec)
{
	cout << "\nWhat Type of Media are you searching?\n";

	//Print types
	for (int i = 0; i < TYPES_LENGTH; i++)
	{
		cout << setfill(' ') << i << ". " << setw(10) << left << TYPES[i];
	}
	cout << endl;

	//Get user choice
	int choice;
	getInput(choice, "Choice: ");

	string type;

	//get type
	switch (choice)
	{
	case 0:
		type = TYPES[0];
		break;
	case 1:
		type = TYPES[1];
		break;
	case 2:
		type = TYPES[2];
		break;
	case 3:
		type = TYPES[3];
		break;
	default:
		cout << "[!] Not an Option [!]\n";
		break;
	}

	cout << "\n===== Searching Catagory '" << type << "' ===== \n";

	//Go through Vector
	int counter = 0;
	for (MediaBase* media : vec)
	{
		if (media->getType() == type)
		{
			counter++;
			media->print();
		}
	}

	cout << "Found : " << counter << " results\n";				
}

void searchMediaByName(const vector<MediaBase*>& vec)
{
	//User input
	cin.ignore();
	string mediaNameSearch;
	cout << "\nWhat is the Title are you searching?\n";
	getInput(mediaNameSearch, "Title: ");

	cout << "\n===== Search for '" << mediaNameSearch << "' ==== = \n";

	//loop through vector
	for (int i = 0; i < vec.size(); i++)
	{
		//if title matches print it
		if (vec.at(i)->getTitle() == mediaNameSearch)
		{
			vec[i]->print();
			return;
		}
	}

	cout << "[!] Title not found [!]\n";
}