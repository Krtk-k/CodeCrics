#pragma once
#include <string>
#include <fstream>

using namespace std;

class Path
{
private:
    string mainDirPath;

public:
    Path();
    ofstream signUp();
    ifstream logIn();
    ofstream author();
    ifstream authorc();
    ifstream viewMatchChoices();
    ifstream battingFile(string matchNum, string team);
    ifstream ballingFile(string matchNum, string team);
    ~Path();
};

extern string line1, line2, inpErr;
bool authenticate(string name, string pass, Path directory);
bool writeUser(string name, string pass, Path directory);
void writeAuthor(string name, string pass, Path directory);
bool checkAuthor(string name, string pass, Path directory);
// ifstream readUser();
// ofstream userUpdate();