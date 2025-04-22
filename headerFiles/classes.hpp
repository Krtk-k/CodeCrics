#pragma once

using namespace std;

int findPersonIndex(string username, string pass, Path p);

class User { // This should be an abstract class (no instances)
    protected:
    string username;
    string password;
    bool isAuthor;
    int index;

    public:
        User(string username, string pass, bool isAuthor);
        void change_username(string name);
        void change_password(string pass);
        // Add more functions if needed
};

class Viewer : public User {
    public:
        Viewer(string username, string pass, bool isAuthor);
        void show_batting(const vector<string>& batsmen, const string& teamName, const string& matchNum);
        void show_bowling(const vector<string>& bowlers, const string& teamName, const string& matchNum);
};

class Author : public Viewer {
    public:
        Author(string username, string pass, bool isAuthor);
        void callScoreBoard();
};