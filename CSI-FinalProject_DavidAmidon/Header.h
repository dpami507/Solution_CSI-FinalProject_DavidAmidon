#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "Time.h"
#include "MediaClasses.h"
using namespace std;

string USERS_FILE = "users.txt";
string TYPES[] = { "Movie", "TV Show", "Song", "Podcast" };

void getInput(string& data, string msg = "");
void getInput(int& data, string msg = "");

bool usernameTaken(string username);
string getUserPassword(string username);
void printUserChoices();

void createUserFile(string user);
void fillVectorWithFile(vector<MediaBase*>& vec, const string& filename);
void writeToFile(vector<MediaBase*>& vec, const string& filename);

void openUserFile(string user);
void createAccount();

void loginScreen();
void login();