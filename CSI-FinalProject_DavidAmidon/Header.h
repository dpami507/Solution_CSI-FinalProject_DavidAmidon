#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//Add Podcast and other Media types
//Add throwing
//Add opperator overloading
//Profit

const string USERS_FILE = "users.txt";
const string TYPES[] = { "MOVIE", "TVSHOW", "SONG", "PODCAST" };
const int TYPES_LENGTH = 4;

template<class T>
void getInput(T& data, string msg)
{
	do
	{
		cout << msg;
		getline(cin, data);

	} while (data.length() <= 0);
}
void getInput(int& data, string msg);