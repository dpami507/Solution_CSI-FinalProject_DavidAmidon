#include "Header.h"

void createUserFile(string user)
{
	string fileName = user + ".txt";
	ofstream file(fileName, std::ios::app);
}

void fillVectorWithFile(vector<MediaBase*>& vec, const string& filename)
{
	ifstream fin(filename);

	while (!fin.eof())
	{
		string data;
		getline(fin, data);
		if (data == "MOVIE")
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
		newMedia = new Movie();
		list.push_back(newMedia); //Add based on type first
		writeToFile(list, filename);
		break;
	case 2:
		//Edit Media 
		break;
	case 3:
		//Remove Media
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