#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "headerFiles/authenticate.hpp"
#include "headerFiles/classes.hpp"
#include "headerFiles/scoreboard.hpp"
#include "headerFiles/textStyles.hpp"
#include "headerFiles/matchInfo.hpp"

using namespace std;

User::User(string username, string pass, bool isAuthor) {
        this->username = username;
        this->password = pass;
        this->isAuthor = isAuthor;
        this->index = findPersonIndex(username, pass, user_path);
    }

void User::change_username(string name) {
        // Authenticate first
        // Add exception handling

        string line;
        ifstream r_file = user_path.logIn();
        ofstream file("mainDir/loginInfo/temp.txt");
        for(int i = 1; i<index; i++) {
            getline(r_file, line);
            file << line << '\n';
        }
        file << name << '\0' << password << '\n';

        // r_file.seekg(name.length() + 2 + pass.length(), ios::cur);
        getline(r_file, line);

        while(getline(r_file, line)) {
            getline(r_file, line);
            file << line << '\n';
        }

        r_file.close();
        file.close();
        remove("mainDir/loginInfo/userSign.txt");
        rename("mainDir/loginInfo/temp.txt", "mainDir/loginInfo/userSign.txt");
    }

void User::change_password(string pass) {
        // Authenticate first
        // Add exception handling

        string line;
        ifstream r_file = user_path.logIn();
        ofstream file("mainDir/loginInfo/temp.txt");
        for(int i = 1; i<index; i++) {
            getline(r_file, line);
            file << line << '\n';
        }
        file << username << '\0' << pass << '\n';
        getline(r_file, line);

        while(getline(r_file, line)) {
            getline(r_file, line);
            file << line << '\n';
        }

        r_file.close();
        file.close();
        remove("mainDir/loginInfo/userSign.txt");
        rename("mainDir/loginInfo/temp.txt", "mainDir/loginInfo/userSign.txt");
    }

int findPersonIndex(string username, string password, Path p) {
    ifstream r_file = p.logIn();
    int index = 0;
    string line, name, pass;

    while(getline(r_file, line)) {
        int pos = line.find('\0');
        name = line.substr(0, pos);
        pass = line.substr(pos+1, line.length());
        index++;
        if((name == username) && (pass == password)) {
            break;
        }
    }
    r_file.close();
    return index;
}


Viewer::Viewer(string username, string pass, bool isAuthor) : User(username, pass, isAuthor) {
        this->index = findPersonIndex(username, pass, user_path);
    }

void Viewer::show_batting(const vector<string>& batsmen, const string& teamName, const string& matchNum) {
        matchInfo matchInfo1; // Create an instance of Matchinfo
        cout << "Batsman Name\tTotal Runs Scored\tNumber of Balls Played" << endl;
    
        for (const string& batsman : batsmen) {
            // Fetch stats for each batsman using getBatsman()
            vector<int> stats = matchInfo1.getBatsmanForView(batsman, teamName, matchNum);
    
            if (!stats.empty()) {
                // Print batsman name, total runs, and balls played
                cout << batsman << "\t\t" << stats[0] << "\t\t\t" << stats[1] << endl;
            } else {
                // Handle case where no stats are found
                cout << batsman << "\t\tNo stats available\t\tNo stats available" << endl;
            }
        }
    }
    
void Viewer::show_bowling(const vector<string>& bowlers, const string& teamName, const string& matchNum) {
        matchInfo matchInfo; // Create an instance of Matchinfo
        cout << "Bowler Name\tBalls Delivered\tWickets Taken\tTotal Runs Scored on Balls" << endl;
    
        for (const string& bowler : bowlers) {
            // Fetch stats for each bowler using getBowler()
            vector<int> stats = matchInfo.getBowlerForView(bowler, teamName, matchNum);
    
            if (!stats.empty()) {
                // Calculate total balls delivered from overs
                int ballsDelivered = stats[0] * 6;
                // Print bowler name, balls delivered, wickets taken, and runs given
                cout << bowler << "\t\t" << ballsDelivered << "\t\t" << stats[2] << "\t\t" << stats[1] << endl;
            } else {
                // Handle case where no stats are found
                cout << bowler << "\t\tNo stats available\t\tNo stats available\t\tNo stats available" << endl;
            }
        }
    }


Author::Author(string username, string pass, bool isAuthor) : Viewer(username, pass, isAuthor) {
        this->index = findPersonIndex(username, pass, user_path);
    }

void Author::callScoreBoard() {
        enteringScoringArea();
    }

// int main() {
//     User obj("kartik", "hello", true);

//     obj.change_username("kavi");
//     Viewer v1("kartik", "haha", false);
//     return 0;
// }