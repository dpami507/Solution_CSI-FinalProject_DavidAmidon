#include "Header.h"

void getInput(string& data, string msg = "")
{
	do
	{
		cout << msg;
		getline(cin, data);

	} while (data.length() <= 0);
}

void getInput(int& data, string msg = "")
{
	cout << msg;
	cin >> data;
}

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