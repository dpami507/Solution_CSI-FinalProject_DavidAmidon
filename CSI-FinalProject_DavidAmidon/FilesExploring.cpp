#include "Header.h"
#include "MediaClasses.h"

void createUserFile(string user)
{
	string fileName = user + ".txt";
	ofstream file(fileName, std::ios::app);
}

MediaBase* mediaType()
{
	//Print types
	for (int i = 0; i < TYPES_LENGTH; i++)
	{
		cout  << i << ". " << setw(10) << left << TYPES[i];
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
	default:
		break;
	}
}

void deleteMedia(vector<MediaBase*> vec)
{
	string titleToDelete;
	getInput(titleToDelete, "What is the Title you want to delete: ");

	for (int i = 0; i < vec.size(); i++)
	{
		if (vec.at(i)->getTitle() == titleToDelete)
		{
			vec.erase(vec.begin() + i);
			break;
		}
	}
}

void openUserFile(string user)
{
	//Set up and open user file;
	string filename = user + ".txt";

	vector<MediaBase*> list;
	{
		ifstream fin(filename);
		fillVectorWithFile(list, filename);
		fin.close();
	}

	cout << "===== " << user << "'s Collection =====\n";
	printUserChoices();
	int choice;
	cin >> choice;

	MediaBase* newMedia;

	switch (choice)
	{
	case 1:
		newMedia = mediaType();
		list.push_back(newMedia); //Add based on type first
		writeToFile(list, filename);
		break;
	case 2:
		//Edit Media 
		break;
	case 3:
		//Remove Media
		deleteMedia(list);
		writeToFile(list, filename);
		break;
	case 4:
		//View Media
		for (MediaBase* media : list)
		{
			media->print();
		}
		break;
	case 5:
		//View Catagory
		break;
	case 6:
		//Search Media
		break;
	case 7:
		//Log Out
		loginScreen();
		break;
	default:
		cout << "[!] Not a valid option [!]\n";
		break;
	}

	openUserFile(user);
}