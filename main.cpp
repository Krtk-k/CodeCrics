#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "headerFiles/authenticate.hpp"
#include "headerFiles/classes.hpp"
#include "headerFiles/textStyles.hpp"

using namespace std;

int main() {
    cout << endl << BOLD << GREEN << line1 << RESET;
    Path mdp;

    cout << endl << BOLD << CYAN << line2 << RESET << "\t";
    int userIn;
    cin >> userIn;

    cin.ignore();
    string username, pwd;
    ofstream file;
    bool is_author = 0;
    switch (userIn) {
        case 1: // Login
            cout << endl << BOLD << "Username: " << RESET;
            getline(cin, username);
            cout << endl << BOLD << "Password: " << RESET;
            getline(cin, pwd);
            if (authenticate(username, pwd, mdp)) {
                if (checkAuthor(username, pwd, mdp)) {
                    is_author = 1;
                }
                cout << GREEN << "Login successful! Welcome, " << username << "." << RESET << endl;
            } else {
                cout << RED << "Authentication failed! Please try again." << RESET << endl;
                throw 'a';
            }
            break;

        case 2: // Signup
            cout << endl << BOLD << "Username: " << RESET;
            getline(cin, username);
            cout << endl << BOLD << "Password: " << RESET;
            getline(cin, pwd);
            cout << endl << BOLD << "Is author: (1- yes, 0-no): " << RESET;
            cin >> is_author;
            if (writeUser(username, pwd, mdp)) {
                if (is_author) {
                    writeAuthor(username, pwd, mdp);
                }
                cout << GREEN << "Signup successful! Welcome, " << username << "." << RESET << endl;
            } else {
                cout << RED << "Error during signup. Please try again." << RESET << endl;
                throw 'w';
            }
            break;

        default:
            cout << RED << inpErr << RESET;
    }

    // Continuation of the program
    int user_choice;
    string match_name;

user_err:
    cout << endl << BOLD << "1- Write a match" << RESET << endl;
    cout << BOLD << "2- View stats" << RESET << endl;
    cin >> user_choice;
    Author user1("", "", false); // Declare outside switch
    Viewer vu("", "", false);   // Declare outside switch

    switch (user_choice) {
        case 1:
            if(checkAuthor(username, pwd, mdp)) {
                user1 = Author(username, pwd, true);
            }
            else {
                cout << endl << RED << "Sorry, You dont have rights" << RESET;
                goto user_err;
            }
            cout << CYAN << "Match name: " << RESET << endl;

            break;

        case 2:
            vu = Viewer(username, pwd, false);
            cout << CYAN << "Match name: " << RESET << endl;

            break;

        default:
            cout << RED << "Wrong input! Please try again." << RESET << endl;
            goto user_err;
    }

    return 0;
}
