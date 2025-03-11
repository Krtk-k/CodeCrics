#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Path {
    private:
    string mainDirPath;

    public:
    Path() {
        cout << endl << "Enter the main directory path: ";
        cin >> mainDirPath;
    }
    ofstream signUp() {
        ofstream signup(mainDirPath + "/userSign.txt", ios::app);
        return (signup);
    }
    ifstream logIn() {
        ifstream login(mainDirPath + "/userLog.txt");
        return (login);
    }

    ~Path() {}
};

string line1 = "\t\tWelcome to CodeCrics", line2 = "\t\t1->Login, 2->Signup";
string inpErr = "Invalid input";


void authenticate(string &name, string &pass, Path &directory) {
    // This function checks for existing user
    string fname = NULL, fpass = NULL;
    ifstream l_file = directory.logIn();
    char ch;
    bool matchFound = false;
    while(1) {
        while((l_file.get(ch)) && (ch != '\0')) {
            fname.push_back(ch);
        }
        l_file.seekg(ios::cur + 1);
        while(l_file.get(ch) && (ch != '\n')) {
            fpass.push_back(ch);
        }

        if((name == fname) && (pass == fpass)) {
            cout << endl << "User Found, Welcome";
            matchFound = true;
            break;
        }
    }

    if(matchFound == false) {
        cout << endl << "You are not an existing user, signup first";
        exit(0);
    }
}

int main() {
    cout << endl << line1;
    Path mdp;
    
    cout << endl << line2 << "\t";
    int userIn;
    cin >> userIn;

    cin.ignore(); 
    string usernameL, pwdL, usernameS, pwdS;
    ofstream file;
    switch(userIn) {
        case 1: // Login
            cout << endl << "Username: ";
            cin.ignore(); 
            getline(cin, usernameL);
            cout << endl << "Password: ";
            getline(cin, pwdL);
            authenticate(usernameL, pwdL, mdp);
            break;

        case 2: // Signup
            cout << endl << "Username: ";
            cin.ignore(); 
            getline(cin, usernameS);
            cout << endl << "Password: ";
            getline(cin, pwdS);
            break;

        default:
            cout << inpErr;
    }

    return 0;
}
