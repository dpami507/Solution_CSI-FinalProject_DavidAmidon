/*
Author        : David Amidon
Class         : CSI - 240 : Advanced Programming
Assignment    : CSI-240 Final Project
*/

#include "Header.h"
#include "Login.h"
#include "FileEditing.h"

bool usernameTaken(string username)
{
	ifstream fin(USERS_FILE);

	//Checks if there is a user file
	if (!fin.is_open())
	{
		cout << "[!] NO USERS FILE : Please create an account first [!]\n";
		loginScreen();
	}

	//Go through all usernames
	while (!fin.eof())
	{
		string line;
		getline(fin, line);

		//If there is a match return true
		if (line == username)
			return true;

		getline(fin, line);
	}

	return false;
}
string getUserPassword(string username)
{
	ifstream fin(USERS_FILE);

	while (!fin.eof())
	{
		string line;
		getline(fin, line);

		//Find user name and return the next line (password)
		if (line == username)
		{
			getline(fin, line);
			return line;
		}
	}
}
void printUserChoices()
{
	cout << "1. Add Media to List\n";
	cout << "2. Edit Media from List\n";
	cout << "3. Remove Media from List\n";
	cout << "4. View Media in List\n";
	cout << "5. View Catagory in List\n";
	cout << "6. Search Media in List\n";
	cout << "7. Log Out\n";
}

void createUserFile(string user)
{
	//Creates user file following format of (username.txt)
	string fileName = user + ".txt";
	ofstream file(fileName, std::ios::app);
}
void openUserFile(string user)
{
	//Set up and open user file;
	string filename = user + ".txt";

	//Create vector andn fill it
	vector<MediaBase*> list;
	{
		ifstream fin(filename);
		fillVectorWithFile(list, filename);
		fin.close();
	}

	cout << "===== " << user << "'s Collection =====\n";
	printUserChoices();
	int choice;
	getInput(choice, "Choice: ");

	switch (choice)
	{
	case 1:
		addMedia(list);
		writeToFile(list, filename);
		break;
	case 2:
		//Edit Media 
		editMedia(list);
		writeToFile(list, filename);
		break;
	case 3:
		//Remove Media
		deleteMedia(list);
		writeToFile(list, filename);
		break;
	case 4:
		//View Media
		printAllMedia(list);
		break;
	case 5:
		//View Catagory
		searchMediaByCatagory(list);
		break;
	case 6:
		//Search Media
		searchMediaByName(list);
		break;
	case 7:
		//Log Out
		for (MediaBase* l : list)
		{
			delete l; 
			l = nullptr;
		}
		loginScreen();
		break;
	default:
		cout << "[!] Not a valid option [!]\n";
		break;
	}

	cout << endl;
	openUserFile(user);
}
void createAccount()
{
	//Get Users File
	ofstream usersFile(USERS_FILE, std::ios::app);

	if (!usersFile.is_open())
	{
		cout << "File not open\n";
	}

	//User Data for account
	string username;
	string password;

	cin.ignore();

	//Loop until unique username
	bool taken = true;
	do
	{
		getInput(username, "Create username: ");

		if (usernameTaken(username))
		{
			taken = true;
			cout << "[!] Username Already Taken [!]\n";
		}
		else
		{
			taken = false;
		}

	} while (taken);

	getInput(password, "Create password: ");

	//Add to user file
	usersFile << username << endl;
	usersFile << password << endl;

	//Close file
	usersFile.close();
	createUserFile(username);

	cout << endl;
	openUserFile(username);
}

void loginScreen()
{
	int input;

	cout << "===== Login Page =====\n";
	cout << "1. Login\n";
	cout << "2. Create Account\n";
	cout << "3. Exit\n";

	cout << "Choice : ";
	cin >> input;

	cout << endl;

	switch (input)
	{
	case 1:
		//Login
		login();
		break;
	case 2:
		//Create Account
		createAccount();
		break;
	case 3:
		//Exit
		exit(0);
		break;
	default:
		break;
	}
}
void login()
{
	//User Data for account
	string username;
	string password;

	cin.ignore();

	//Get username
	bool taken = true;
	do
	{
		getInput(username, "Enter username: ");

		if (!usernameTaken(username))
		{
			taken = false;
			cout << "[!] Username Doesn't Exist [!]\n";
		}
		else
		{
			taken = true;
		}

	} while (!taken);

	//Get correct password
	string correctPassword;
	correctPassword = getUserPassword(username);
	int attempts = 3;

	while (attempts > 0)
	{
		//Get password inpuut
		getInput(password, "Enter password: ");

		if (password == correctPassword)
		{
			cout << "Login Success\n";
			cout << endl;
			openUserFile(username);
		}
		else
		{
			attempts--;
			cout << "[!] Invalid Password! Attempts Left: " << attempts << " [!]\n";
		}

		if (attempts <= 0)
		{
			cout << "[!] Max attempts reached, Exiting... [!]\n";
			break;
		}
	}
}