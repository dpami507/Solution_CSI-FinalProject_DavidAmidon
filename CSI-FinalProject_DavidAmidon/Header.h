/*
Author        : David Amidon
Class         : CSI - 240 : Advanced Programming
Assignment    : CSI-240 Final Project
*/
/*
Project Description :
Allows multiple users to create accounts and login to their own accounts to store and save media records (Movie, TVShow, Podcast, Song)

Certification of Authenticity :

I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of
academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking
service (which may then retain a copy of this assignment on its
database for the purpose of future plagiarism checking)
*/

#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

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