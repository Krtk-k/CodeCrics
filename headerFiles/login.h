#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Path {
    private:
    string mainDirPath;

    public:
    Path();
    ofstream signUp();
    ifstream logIn();

    ~Path();
};

string line1, line2, inpErr;

void authenticate(string name, string pass, Path directory);
void writeUser(string name, string pass, Path directory);