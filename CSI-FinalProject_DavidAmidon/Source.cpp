#include "Header.h"
#include "Login.h"

void getInput(int& data, string msg = "")
{
	cout << msg;
	cin >> data;
}

int main()
{
	loginScreen();

	return 0;
}