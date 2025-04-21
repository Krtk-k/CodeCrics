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
            } else {
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
            } else {
                throw 'w';
            }
            break;

        default:
            cout << RED << inpErr << RESET;
    }

    // Continuation of the program
    int user_choice;
    string match_name;
    Author user1("", "", false);
    Viewer vu("", "", false);

user_err:
    cout << endl << BOLD << "1- Write a match: " << RESET << endl;
    cout << BOLD << "2- View stats: " << RESET << endl;
    cin >> user_choice;

    switch (user_choice) {
        case 1:
            if(checkAuthor(username, pwd, mdp)) {
                user1 = Author(username, pwd, true);
            }
            else {
                cout << endl << RED << "Sorry, You dont have rights" << RESET;
                goto user_err;
            }
            bool user_change = false;
            cout << endl << RED << "If change passwrord or username enter 1, (else enter 0): " << RESET;
            cin >> user_change;
            if(user_change == true) {
                string new_pass, new_name;
                cout << endl << "Enter new username: ";
                cin >> new_name;
                user1.change_username(new_name);
                cout << endl << "Enter new password: ";
                cin >> new_pass;
                user1.change_password(new_pass);
            }
            
            cout << CYAN << "Match name: " << RESET << endl;

            break;

        case 2:
            vu = Viewer(username, pwd, false);
            bool user_change = false;
            cout << endl << RED << "If change passwrord or username enter 1, (else enter 0): " << RESET;
            cin >> user_change;
            if(user_change == true) {
                string new_pass, new_name;
                cout << endl << "Enter new username: ";
                cin >> new_name;
                vu.change_username(new_name);
                cout << endl << "Enter new password: ";
                cin >> new_pass;
                vu.change_password(new_pass);
            }
            cout << endl << CYAN << "Match name: " << RESET << endl;
            string team_name;
            cout << endl << "Enter team name: ";
            cin >> team_name;
            cout << endl << BRIGHT_YELLOW << "Team 1: " << RESET << WHITE << team_name << RESET << endl
            << GREEN << "Batting.." << RESET;
            vu.show_batting();
            cout << endl << GREEN << "Bowling.." << RESET;
            vu.show_bowling();

            cout << endl << "Enter team name: ";
            cin >> team_name;
            cout << endl << BRIGHT_YELLOW << "Team 2: " << RESET << WHITE << team_name << RESET << endl << RESET
            << GREEN << "Batting.." << RESET;
            vu.show_batting();
            cout << endl << GREEN << "Bowling.." << RESET;
            vu.show_bowling();

            break;

        default:
            cout << RED << "Wrong input! Please try again." << RESET << endl;
            goto user_err;
    }

    return 0;
}
