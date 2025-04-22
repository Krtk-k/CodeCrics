#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "headerFiles/authenticate.hpp"
#include "headerFiles/classes.hpp"
#include "headerFiles/scoreboard.hpp"
#include "headerFiles/textStyles.hpp"

using namespace std;

Path mdp;

vector<string> createBattingVector(string matchNum, string team) {
    ifstream file = mdp.battingFile(matchNum, team);
    string str;
    vector<string>batsMan;
    while(getline(file, str)) {
        string name = str.substr(0, str.find("_"));
        batsMan.push_back(name);
    }
    file.close();
    return batsMan;
}

vector<string> createBowlingVector(string matchNum, string team) {
    ifstream file = mdp.ballingFile(matchNum, team);
    string str;
    vector<string>bowler;
    while(getline(file, str)) {
        string name = str.substr(0, str.find("_"));
        bowler.push_back(name);
    }
    file.close();
    return bowler;
}

int main() {
    cout << endl << BOLD << GREEN << line1 << RESET;
    

    cout << endl << BOLD << CYAN << line2 << RESET << "\t";
    int userIn;
    cin >> userIn;

    cin.ignore();
    string username, pwd;
    ofstream file;
    bool is_author = 0;
    Author user1("", "", false);
    Viewer vu("", "", false);
    switch (userIn) {
        case 1: // Login
            cout << endl << BOLD << "Username: " << RESET;
            getline(cin, username);
            toLowerCase(username);
            cout << endl << BOLD << "Password: " << RESET;
            getline(cin, pwd);
            if (authenticate(username, pwd, mdp)) {
                if (checkAuthor(username, pwd, mdp)) {
                    user1 = Author(username, pwd, true);
                    is_author = 1;
                }
                vu = Viewer(username, pwd, false);
            } else {
                throw 'a';
            }
            break;

        case 2: // Signup
            cout << endl << BOLD << "Username: " << RESET;
            getline(cin, username);
            toLowerCase(username);
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
    string user_choice;
    string match_name;
    
    

while(1) {
    cout << endl << BOLD << "1- Write a match: " << RESET << endl;
    cout << BOLD << "2- View stats: " << RESET << endl;
    cout << BOLD << RED << "3- Change password: " << RESET << endl;
    cout << BOLD << RED << "4- Change username: " << RESET;
    cin >> user_choice;

    if (user_choice == "1") {
            if(checkAuthor(username, pwd, mdp)) {
                cout << CYAN << "Starting the match: " << RESET << endl;
                user1.callScoreBoard();
                break;
            }
            else {
                cout << endl << RED << "Sorry, You are not an author" << RESET;
            }
    }
            else if(user_choice == "2") {

                ifstream userMatchChoicesFile = mdp.viewMatchChoices();
                string choices;
                int num = 0;
                int matchNum;
                while(getline(userMatchChoicesFile, choices)) {
                    int pos1 = choices.find('&');
                    string firstline = choices.substr(0, pos1);
                    int pos2 = choices.find('/');
                    string secondline = choices.substr(pos1+1, pos2);
                    string winner = choices.substr(pos2+1, choices.length());

                    ++num;
                    cout << num << "- " << firstline << " VS " << secondline << " Winner : "<<winner<< endl;
                }

                cin >> matchNum;
                userMatchChoicesFile.seekg(0, ios::beg);
                for(int i = 0; i<matchNum; i++) {
                    getline(userMatchChoicesFile, choices);
                }
                int pos1 = choices.find(':');
                string mn = choices.substr(0, pos1);
                int pos2 = choices.find('&');
                string team1Name = choices.substr(pos1+1, pos2);
                int pos3 = choices.find('/');
                string team2Name = choices.substr(pos2+1, pos3);
                string winner = choices.substr(pos3+1, choices.length());
                

            cout << endl << BRIGHT_YELLOW << "Team 1: " << RESET << WHITE << team1Name << RESET << endl
            << GREEN << "Batting.." << RESET<<endl;
            
            vector<string> battingVector = createBattingVector(mn, team1Name);
            vector<string> bowlingVector = createBowlingVector(mn, team1Name);
            vu.show_batting(battingVector, team1Name, mn);
            cout << endl << GREEN << "Bowling.." << RESET<<endl;
            vu.show_bowling(bowlingVector, team1Name, mn);

            cout << endl << BRIGHT_YELLOW << "Team 2: " << RESET << WHITE << team2Name << RESET << endl << RESET
            << GREEN << "Batting.." << RESET<<endl;

            battingVector = createBattingVector(mn, team1Name);
            bowlingVector = createBowlingVector(mn, team1Name);
            vu.show_batting(battingVector, team2Name, mn);
            cout << endl << GREEN << "Bowling.." << RESET<<endl;
            vu.show_bowling(bowlingVector, team2Name, mn);

            break;
        }

        else if(user_choice == "3") {
            if(checkAuthor(username, pwd, mdp)) {
                cout << endl << "Enter new password: ";
                cin >> pwd;
                user1.change_password(pwd);
                cout << endl << GREEN << "Password updated successfully" << RESET;
            }
            else {
                cout << endl << "Enter new password: ";
                cin >> pwd;
                vu.change_password(pwd);
                cout << endl << GREEN << "Password updated successfully" << RESET;
            }
            break;
        }

        else if(user_choice == "4") {
            if(checkAuthor(username, pwd, mdp)) {
                cout << endl << "Enter new username: ";
                cin >> username;
                user1.change_username(username);
                cout << endl << GREEN << "Username updated successfully" << RESET;
            }
            else {
                cout << endl << "Enter new username: ";
                cin >> username;
                vu.change_username(username);
                cout << endl << GREEN << "Username updated successfully" << RESET;
            }
            break;
        }

        else {
        cout << RED << "Wrong input! Please try again." << RESET << endl;
        }
    }

    return 0;
}
