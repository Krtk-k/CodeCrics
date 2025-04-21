#pragma  once
#include <string>
#include <fstream>
#include "headerFiles/authenticate.hpp"

using namespace std;

Path user_path;

int findPersonIndex(string username, string pass, Path p);

class User {
    protected:
    string username;
    string password;
    bool isAuthor;
    int index;

    public:
    User(string &username, string &pass, bool isAuthor);

    void change_username(string name);

    void change_password(string pass);

    // Add more functions if needed
};

class Viewer : public User {
    private:
    Match *match;

    public:
    Viewer(string username, string pass, bool isAuthor);

    void show_batting();
    void show_bowling();
};

class Author : public Viewer {
    public:
    Author(string username, string pass, bool isAuthor);
};

class Match{
    private:
    string name;
    ifstream runPtr, batsMen, bowlers;
    vector<vector<pair<int, int>>> viewVector;

    public:
    Match(string name);
    ifstream* returnRunPtr();
    ifstream* returnBatsMenPtr();
    ifstream* returnBowlersPtr();

    void ini_viewVector();
    // Add more functionns if required
};
