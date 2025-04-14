#include <iostream>
#include "headerFiles/textStyles.h"
#include "headerFiles/scorecard.h"
#include <vector>
#include <algorithm>
#include "headerFiles/playerinfo.hpp"
#include <cstdlib>
#include <ctime>
#include <limits>


using namespace std;

class Players {
protected:
    int n;
    string team1;
    string team2;
    vector<string> t1players;
    vector<string> t2players;
    vector<string> teams;
    string name;
    int totalOversToBePlayed;
    string choice;
    string tossWinner;
    string tossLoser;

public:
    Players() {
        cout << endl
             << "\t\t\t🎾🏏⚾️" << UNDERLINE << BOLD << BRIGHT_WHITE << " WELCOME TO THE SCORING AREA " << RESET << "⚾️🏏🎾" << endl;
        cout << endl
             << "HOW MANY OVERS YOU WANT TO PLAY: ";
        cin >> totalOversToBePlayed;

        for (int i = 0; i < 2; i++) {
            if (i == 0) {
                cout << "ENTER NAME of TEAM 1: ";
                cin >> team1;
                teams.push_back(team1);
            } else {
                cout << "ENTER NAME of TEAM 2: ";
                cin >> team2;
                teams.push_back(team2);
            }

            cout << "\nEnter Number of Players in TEAM " << i + 1 << ": ";
            cin >> n;
            cout << "\nEnter Players (Make sure that the Player is Already Registered)\n\n";

            for (int j = 0; j < n; j++) {
                cout << "Player " << j + 1 << ": ";
                cin >> name;

                if (!isPlayerRegistered(name)) {
                    cout << "❌ Player not registered. Please enter a valid name.\n";
                    j--; // Retry the same player number
                    continue;
                }

                if (i == 0) {
                    t1players.push_back(name);
                } else {
                    t2players.push_back(name);
                }
            }

            cout << endl;
        }

        srand(time(0));
        cout << endl
             << BOLD << YELLOW << "COIN TOSSED !!" << RESET << endl;
        tossWinner = teams[rand() % 2];
        cout << BOLD << MAGENTA << tossWinner << YELLOW << " WINS THE TOSS !!" << endl
             << endl;
        cout << ORANGE << "What do you want to choose (bat/bowl): " << RESET;
        cin >> choice;

        if (tossWinner == team1) {
            tossLoser = team2;
        } else {
            tossLoser = team1;
        }
    }

    ~Players() {}
};

class BatsmanBowler : public Players {
    // BATSMAN
    string onStrike;
    string runningEnd;
    string batsman1;
    string batsman2;
    int b1Runs;
    int b2Runs;
    int runsScoredOnThisBall;
    int target;

    // BOWLER
    string bowler;
    int totalBalls;
    int ballsBowled;
    int overs;
    int wickets;

    // STATIC VARIABLES
    static int oversThrown;
    static int runsScored;
    static int wicketsDown;

public:
    static void resetStaticVariables() {
        oversThrown = 0;
        runsScored = 0;
        wicketsDown = 0;
    }

    BatsmanBowler() {
        cout << "\nEnter Name of Batsman on Striking End: ";
        cin >> onStrike;

        cout << "Enter Name of Batsman on Running End: ";
        cin >> runningEnd;

        cout << "Enter Name of Bowler: ";
        cin >> bowler;

        batsman1 = onStrike;
        batsman2 = runningEnd;
        runsScoredOnThisBall = 0;

        b1Runs = 0;
        b2Runs = 0;
        totalBalls = 6;
        ballsBowled = 0;
        overs = 0;
        wickets = 0;
    }

    void strikeChange(int runs = 0) {
        if (runs % 2 == 0 && batsman1 == onStrike) {
            b1Runs += runs;
            updateStats(batsman1, b1Runs, 0, 0); // Update batsman1 stats
        } else if (runs % 2 == 0 && batsman2 == onStrike) {
            b2Runs += runs;
            updateStats(batsman2, b2Runs, 0, 0); // Update batsman2 stats
        } else if (runs % 2 != 0 && batsman1 == onStrike) {
            b1Runs += runs;
            updateStats(batsman1, b1Runs, 0, 0); // Update batsman1 stats
            swap(onStrike, runningEnd);
        } else if (runs % 2 != 0 && batsman2 == onStrike) {
            b2Runs += runs;
            updateStats(batsman2, b2Runs, 0, 0); // Update batsman2 stats
            swap(onStrike, runningEnd);
        } else {
            cout << "ERROR in strikeChange() !!";
        }

        ballsBowled++;
        if (ballsBowled == totalBalls) {
            overs++;
            oversThrown++;
            ballsBowled = 0;
            updateStats(bowler, 0, overs, wickets); // Update bowler stats
        }
    }

    friend void scorecard(string, BatsmanBowler);

    ~BatsmanBowler() {}
};

// INITIALIZING STATIC VARIABLES OF BatsmanBowler CLASS
int BatsmanBowler::oversThrown = 0;
int BatsmanBowler::runsScored = 0;
int BatsmanBowler::wicketsDown = 0;

void scorecard(string inning, BatsmanBowler matchDetails) {
    int totalTeamPlayers;
    if (inning == "(INNING : 1)") {
        if (matchDetails.choice == "bat") {
            totalTeamPlayers = (matchDetails.tossWinner == matchDetails.team1) ? matchDetails.t1players.size() : matchDetails.t2players.size();
        } else {
            totalTeamPlayers = (matchDetails.tossLoser == matchDetails.team1) ? matchDetails.t1players.size() : matchDetails.t2players.size();
        }
    } else {
        if (matchDetails.choice == "bat") {
            totalTeamPlayers = (matchDetails.tossLoser == matchDetails.team1) ? matchDetails.t1players.size() : matchDetails.t2players.size();
        } else {
            totalTeamPlayers = (matchDetails.tossWinner == matchDetails.team1) ? matchDetails.t1players.size() : matchDetails.t2players.size();
        }
    }

    while (matchDetails.totalOversToBePlayed != matchDetails.oversThrown &&
           matchDetails.wicketsDown != (totalTeamPlayers - 1)) {
        cout << endl
             << BOLD << UNDERLINE << BRIGHT_WHITE << "\t\t\t\t SCORECARD " << RESET << endl;
        cout << endl
             << "\t\t                " << ORANGE << inning << RESET << endl
             << endl
             << endl;
        cout << "\t\t\t " << BLUE << matchDetails.tossWinner << " CHOSE TO " << matchDetails.choice << " FIRST" << RESET << endl
             << endl
             << endl
             << endl;

        matchDetails.strikeChange(matchDetails.runsScoredOnThisBall);
        cout << endl
             << endl
             << BOLD << BRIGHT_WHITE << "\t\t\t\t  RUNS : " << matchDetails.runsScored << endl
             << endl;
        cout << BLUE << "\t\t\t WICKETS/TOTAL WICKETS : " << matchDetails.wicketsDown << "/" << (totalTeamPlayers - 1) << endl
             << endl;
        cout << BRIGHT_WHITE << "\t\t\t   OVERS/TOTAL OVERS : " << matchDetails.oversThrown << "/" << matchDetails.totalOversToBePlayed << RESET << endl
             << endl;

        if (inning == "(INNING : 2)") {
            cout << "\t\t\t       " << BG_BRIGHT_YELLOW << "TARGET"
                 << " : " << matchDetails.target << RESET << endl
                 << endl;
            if (matchDetails.runsScored >= matchDetails.target) {
                break; // End the match if the target is reached
            }
        }
    }

    if (inning == "(INNING : 1)") {
        matchDetails.target = matchDetails.runsScored;
    }

    updateStats(matchDetails.batsman1, matchDetails.b1Runs, 0, 0);
    updateStats(matchDetails.batsman2, matchDetails.b2Runs, 0, 0);
    updateStats(matchDetails.bowler, 0, matchDetails.overs, matchDetails.wickets);
}

void enteringScoringArea() {
    BatsmanBowler matchDetails;
    cout << endl
         << endl
         << BRIGHT_WHITE << BOLD << "THE MATCH BEGINS !!" << RESET << endl
         << endl;

    scorecard("(INNING : 1)", matchDetails);

    cout << endl
         << endl
         << BRIGHT_WHITE << BOLD << "INNINGS BREAK !!" << RESET << endl
         << endl;

    scorecard("(INNING : 2)", matchDetails);

    cout << endl
         << endl
         << BRIGHT_WHITE << BOLD << "MATCH ENDS !!" << RESET << endl
         << endl;

    savePlayerStats();

    int option;
    do {
        cout << "\n🏏 ----------- Post-Match Stats Menu -----------\n";
        cout << "1. View a player's stats\n";
        cout << "2. View all players' stats\n";
        cout << "3. Exit\n";
        cout << "Choose an option (1-3): ";
        cin >> option;

        switch (option) {
        case 1: {
            string lookupName;
            cout << "\n🔍 Enter player's name: ";
            cin >> lookupName;
            printPlayerStats(lookupName);
            break;
        }
        case 2:
            cout << "\n📊 Showing all player stats:\n";
            printAllPlayerStats();
            break;
        case 3:
            cout << "\n👋 Exiting post-match stats menu. Thank you for playing!\n";
            break;
        default:
            cout << "\n❌ Invalid option. Please select between 1-3.\n";
        }
    } while (option != 3);
}

int main() {
    loadPlayerStats();
    enteringScoringArea();
    return 0;
}