#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

string USERS_FILE = "users.txt";
string TYPES[] = { "Movie", "TV Show" };

void loginScreen(); //TESTING PROTOTYPE

bool stringContainsChar(string s, char c)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == c)
			return true;
	}

	return false;
}

void getInput(string& data, string msg = "")
{
	do
	{
		cout << msg;
		getline(cin, data);

		if (stringContainsChar(data, '|'))
			cout << "[!] The symbol '|' can not be used [!]\n";

	} while (stringContainsChar(data, '|') || data.length() <= 0);
}

class Time
{
public:
	Time()
	{
		cout << "Enter the Hours: ";
		cin >> hours;

		cout << "Enter the Minutes: ";
		cin >> minutes;

		cout << "Enter the Seconds: ";
		cin >> seconds;

		fixTime();
	}

	void fixTime()
	{
		if (seconds >= 60)
		{
			minutes += seconds / 60;
			seconds %= 60;
		}
		if (minutes >= 60)
		{
			hours += minutes / 60;
			minutes %= 60;
		}
	}

	void setTimeFromSeconds(const int& i)
	{
		seconds = i;
		minutes = 0;
		hours = 0;

		fixTime();
	}

	int getSeconds()
	{
		int totalSeconds = 0;
		totalSeconds += seconds;
		totalSeconds += minutes * 60;
		totalSeconds += hours * 3600;

		return totalSeconds;
	}

	string format()
	{
		stringstream time;
		time << setfill('0') << setw(2) << hours << ":"
			<< setfill('0') << setw(2) << minutes << ":"
			<< setfill('0') << setw(2) << seconds << endl;

		return time.str();
	}

	void print()
	{
		cout << format();
	}

private:
	int hours;
	int minutes;
	int seconds;
};

void getInput(int& data, string msg = "")
{
	cout << msg;
	cin >> data;
}

class MediaBase
{
public:
	MediaBase()
	{
		setType();
		cin.ignore();
		getInput(title, "Enter the title: ");
		time = new Time();
	}
	~MediaBase()
	{
		delete time;
		time = nullptr;
	}

	virtual string formatInfo() = 0;

	//Getters
	string getTitle() { return title; }
	string getType() { return type; }
	int getLength() { return time->getSeconds(); }

	void setType()
	{
		int typesArrLength = sizeof(TYPES) / sizeof(TYPES[0]);

		cout << "What type of meadia are you adding?\n";
		for (int i = 0; i < typesArrLength; i++)
		{
			cout << i << ". " << TYPES[i] << endl;
		}

		int requestedType;

		do
		{
			getInput(requestedType, "Choice : ");
		} while (requestedType >= typesArrLength || requestedType < 0);
	}

private:
	string title;
	string type;
	Time* time;
};

class Movie : public MediaBase
{
public:
	Movie() : MediaBase()
	{
		cin.ignore();
		getInput(director, "Enter the director: ");
	}

	//Getters
	string getDirector() { return director; }

	virtual string formatInfo()
	{
		stringstream format;
		format << getType() << "|"
			<< getTitle() << "|"
			<< getLength() << "|"
			<< getDirector() << endl;

		return format.str();
	}

private:
	string director;
};

bool usernameTaken(string username)
{
	ifstream fin(USERS_FILE);

	if (!fin.is_open())
	{
		cout << "[!] NO USERS FILE : Please create an account first [!]\n";
		loginScreen();
	}

	while (!fin.eof())
	{
		string line;
		getline(fin, line);

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
	string fileName = user + ".txt";
	ofstream file(fileName, std::ios::app);
}
MediaBase* getUserType()
{
	MediaBase* type;
	type = new Movie();
	return type;
}

void openUserFile(string user)
{
	//Set up and open user file;
	string fileName = user + ".txt";
	ofstream fout(fileName, std::ios::app);
	ifstream fin(fileName);

	//Create vector
	vector<MediaBase*> list;

	//Give choives to user
	cout << "===== " << user << "'s Collection =====\n";
	printUserChoices();
	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1:
		list.push_back(getUserType()); //Add based on type first
		for (int i = 0; i < list.size(); i++)
		{
			fout << list[i]->formatInfo();
		}
		
		break;
	case 2:
		//Edit Media 
		break;
	case 3:
		//Remove Media
		break;
	case 4:
		//View Media
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

int main()
{
	loginScreen();

	return 0;
}