#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "headerFiles/authenticate.hpp"

using namespace std;

int main() {
    cout << endl << line1;
    Path mdp;
    
    cout << endl << line2 << "\t";
    int userIn;
    cin >> userIn;

    cin.ignore(); 
    string username, pwd;
    ofstream file;
    switch(userIn) {
        case 1: // Login
            cout << endl << "Username: ";
            getline(cin,username);
            cout << endl << "Password: ";
            getline(cin,pwd);
            authenticate(username, pwd, mdp);
            break;

        case 2: // Signup
            cout << endl << "Username: ";
            getline(cin,username);
            cout << endl << "Password: ";
            getline(cin,pwd);
            writeUser(username, pwd, mdp);
            break;

        default:
            cout << inpErr;
    }

    return 0;
}
