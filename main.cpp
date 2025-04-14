#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "headerFiles/playerinfo.hpp"   // To handle player stats
#include "scorecard.cpp"    // To start cricket game (if modularized, use headers instead)

using namespace std;

class Path {
private:
    string mainDirPath;

public:
    Path() {
        mainDirPath = "mainDir/loginInfo";
    }
    ofstream signUp() {
        ofstream signup(mainDirPath + "/userSign.txt", ios::app);
        if (!signup.is_open()) {
            cerr << "Error: Could not open userSign.txt for sign-up" << endl;
        }
        return signup;
    }
    ifstream logIn() {
        ifstream login(mainDirPath + "/userSign.txt");
        if (!login.is_open()) {
            cerr << "Error: Could not open userSign.txt for login" << endl;
        }
        return login;
    }

    ~Path() {}
};

string line1 = "\t\tWelcome to CodeCrics", line2 = "\t\t1->Login, 2->Signup";
string inpErr = "Invalid input";

bool isPlayerRegistered(const string& playerName) {
    ifstream file("username.txt");
    string name;
    while (getline(file, name)) {
        if (name == playerName) return true;
    }
    return false;
}

bool authenticate(string name, string pass, Path directory){
    ifstream file = directory.logIn();
    if (!file.is_open()) return false;

    string line;
    bool matchFound = false;
    while(getline(file,line)){
        int pos = line.find('\0');
        string username = line.substr(0,pos);
        if (username == name){
            matchFound = true;
            string password = line.substr(pos+1,line.length());
            if (password == pass){
                cout << endl << "✅ LOGIN SUCCESSFUL !! Welcome " << name << "!";
                file.close();

                // ✅ Sync player registration with playerinfo.txt
                if (!isPlayerRegistered(name)) {
                    ofstream reg("username.txt", ios::app);
                    reg << name << "\n";
                    reg.close();
                }

                return true;
            } else {
                cout << endl << "❌ Incorrect Password !!";
                return false;
            }
        }
    }
    if(!matchFound){
        cout << endl << "⚠️ You are not an existing user !! Sign up first.";
    }
    file.close();
    return false;
}

void writeUser(string name, string pass, Path directory) {
    ofstream file_write = directory.signUp();
    ifstream file_read = directory.logIn();
    if (!file_write.is_open() || !file_read.is_open()) return;

    string line;
    bool matchFound = false;
    while(getline(file_read,line)){
        int pos = line.find('\0');
        string username = line.substr(0,pos);
        if (username == name){
            matchFound = true;
            cout<<endl<<"❗ Username Already Exists !! Try a different one !!"<<endl;
            break;
        }
    }
    if(!matchFound){
        file_write.seekp(0, ios::end);
        file_write << name << '\0' << pass << '\n';
        cout << endl << "🎉 ACCOUNT CREATED SUCCESSFULLY !!";

        // Register in playerinfo system too
        ofstream reg("username.txt", ios::app);
        reg << name << "\n";
        reg.close();
    }
    file_write.close();
    file_read.close();
}

int main() {
    cout << endl << line1;
    Path mdp;

    cout << endl << line2 << "\t";
    int userIn;
    cin >> userIn;

    cin.ignore(); 
    string username, pwd;

    switch(userIn) {
        case 1: // Login
            cout << endl << "Username: ";
            getline(cin,username);
            cout << endl << "Password: ";
            getline(cin,pwd);

            if (authenticate(username, pwd, mdp)) {
                loadPlayerStats();
                enteringScoringArea();  // Start match
                savePlayerStats();
            }
            break;

        case 2: // Signup
            cout << endl << "Choose a Username: ";
            getline(cin,username);
            cout << endl << "Choose a Password: ";
            getline(cin,pwd);
            writeUser(username, pwd, mdp);
            break;

        default:
            cout << inpErr;
    }

    return 0;
}
