#pragma once
#include <string>
#include <fstream>

class Path
{
private:
    string mainDirPath;

public:
    Path();
    ofstream signUp();
    ifstream logIn();
    ~Path();
}; 
extern string line1, line2, inpErr;
void authenticate(string name, string pass, Path directory);
void writeUser(string name, string pass, Path directory);
// ifstream readUser();
// ofstream userUpdate();