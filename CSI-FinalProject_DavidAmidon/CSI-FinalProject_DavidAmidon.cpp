#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

string USERS_FILE = "users.txt";
string TYPES[] = { "Movie", "TV Show", "Song", "Podcast"};

void loginScreen(); //TESTING PROTOTYPE

void getInput(string& data, string msg = "")
{
	do
	{
		cout << msg;
		getline(cin, data);

	} while (data.length() <= 0);
}

class Time
{
public:
	Time(int seconds)
	{
		hours = 0;
		minutes = 0;
		this->seconds = seconds;
		fixTime();
	}
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
	MediaBase(string title, Time* time)
	{
		this->title = title;
		this->time = time;
	}
	MediaBase()
	{
		cin.ignore();
		getInput(title, "Enter the title: ");
		time = new Time();
	}
	~MediaBase()
	{
		cout << "Media Destroyed!\n";
		delete time;
		time = nullptr;
	}

	virtual string formatInfo() = 0;
	virtual void print() = 0;

	//Getters
	string getTitle() { return title; }
	string getType() { return type; }
	int getLength() { return time->getSeconds(); }
	string getFormatedTime() { return time->format(); }

	void setType(string type)
	{
		this->type = type;
	}

private:
	string title;
	string type;
	Time* time;
};

class Movie : public MediaBase
{
public:
	Movie(string title, Time* time, string director) : MediaBase(title, time)
	{
		setType("MOVIE");
		this->director = director;
	}

	Movie() : MediaBase()
	{
		cout << "Movie Created!\n";
		setType("MOVIE");
		cin.ignore();
		getInput(director, "Enter the director: ");
	}
	~Movie()
	{
		cout << "Movie Destroyed!\n";
	}

	//Getters
	string getDirector() { return director; }

	virtual string formatInfo()
	{
		stringstream format;
		format << getType() << endl 
			<< getTitle() << endl 
			<< getLength() << endl 
			<< getDirector() << endl;

		return format.str();
	}

	virtual void print() override
	{
		cout << getTitle() << endl;
		cout << getFormatedTime();
		cout << getDirector() << endl;
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

void fillVectorWithFile(vector<MediaBase*> &vec, const string& filename)
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

void openUserFile(string user)
{
	//Set up and open user file;
	string filename = user + ".txt";
	ofstream fout(filename, std::ios::app);
	ifstream fin(filename);

	//Create vector
	vector<MediaBase*> list;
	fillVectorWithFile(list, filename);

	//Give choives to user
	cout << "===== " << user << "'s Collection =====\n";
	printUserChoices();
	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1:
		list.push_back(new Movie()); //Add based on type first
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