#pragma once
#include "Header.h"

bool usernameTaken(string username);
string getUserPassword(string username);
void printUserChoices();

void createUserFile(string user);
void openUserFile(string user);
void createAccount();

void loginScreen();
void login();