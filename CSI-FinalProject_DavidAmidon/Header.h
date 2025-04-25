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
void getInput(T& data, string msg);
void getInput(int& data, string msg);

bool usernameTaken(string username);
string getUserPassword(string username);
void printUserChoices();

void createUserFile(string user);
void openUserFile(string user);
void createAccount();

void loginScreen();
void login();