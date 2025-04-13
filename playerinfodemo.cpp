// cricket_game_with_stats.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class CricketPlayer {
    string name;
    int runs;
    int overs;
    int wickets;
    int halfCenturies;
    int centuries;

public:
    CricketPlayer() : runs(0), overs(0), wickets(0), halfCenturies(0), centuries(0) {}

    void setName(const string& n) { name = n; }
    string getName() const { return name; }

    void addRuns(int r) {
        runs += r;
        if (runs >= 50 && runs < 100 && halfCenturies == 0) halfCenturies++;
        if (runs >= 100 && centuries == 0) centuries++;
    }

    void addOver() { overs++; }
    void addWicket() { wickets++; }

    int getRuns() const { return runs; }
    int getOvers() const { return overs; }
    int getWickets() const { return wickets; }
    int getHalfCenturies() const { return halfCenturies; }
    int getCenturies() const { return centuries; }

    static bool verifyPlayer(const string& name) {
        ifstream file("username.txt");
        string line;
        unordered_set<string> usernames;
        while (getline(file, line)) usernames.insert(line);
        return usernames.count(name) > 0;
    }
};

class Players {
protected:
    int n;
    string team1, team2;
    vector<string> t1players, t2players, teams;
    string name;
    int totalOversToBePlayed;
    string choice, tossWinner, tossLoser;

public:
    Players() {
        cout << "Enter number of overs: ";
        cin >> totalOversToBePlayed;

        for (int i = 0; i < 2; ++i) {
            cout << "Enter name for TEAM " << i+1 << ": ";
            if (i == 0) {
                cin >> team1;
                teams.push_back(team1);
            } else {
                cin >> team2;
                teams.push_back(team2);
            }

            cout << "Enter number of players in TEAM " << i+1 << ": ";
            cin >> n;
            cin.ignore();

            for (int j = 0; j < n; ++j) {
                cout << "Player " << j+1 << ": ";
                cin >> name;
                while (!CricketPlayer::verifyPlayer(name)) {
                    cout << "Player not registered. Enter again: ";
                    cin >> name;
                }
                if (i == 0) t1players.push_back(name);
                else t2players.push_back(name);
            }
        }

        srand(time(0));
        tossWinner = teams[rand() % 2];
        tossLoser = (tossWinner == team1) ? team2 : team1;
        cout << tossWinner << " wins the toss. Choose bat/bowl: ";
        cin >> choice;
    }
};

class BatsmanBowler : public Players {
    CricketPlayer p1, p2, bowler;
    string onStrike, runningEnd;
    int b1Runs = 0, b2Runs = 0, ballsBowled = 0, overs = 0, wickets = 0;
    static int oversThrown, runsScored, wicketsDown;

public:
    BatsmanBowler() {
        cout << "Enter batsman on strike: "; cin >> onStrike;
        cout << "Enter batsman on non-striker's end: "; cin >> runningEnd;
        cout << "Enter bowler's name: "; cin >> name;

        p1.setName(onStrike);
        p2.setName(runningEnd);
        bowler.setName(name);
    }

    void updateScore(int runs) {
        if (onStrike == p1.getName()) p1.addRuns(runs);
        else p2.addRuns(runs);

        runsScored += runs;
        ballsBowled++;

        if (ballsBowled == 6) {
            overs++;
            oversThrown++;
            bowler.addOver();
            ballsBowled = 0;
        }

        if (runs % 2 != 0) swap(onStrike, runningEnd);
    }

    void printStats() {
        cout << "\nPlayer: " << p1.getName() << ", Runs: " << p1.getRuns()
             << ", 50s: " << p1.getHalfCenturies() << ", 100s: " << p1.getCenturies() << endl;
        cout << "Player: " << p2.getName() << ", Runs: " << p2.getRuns()
             << ", 50s: " << p2.getHalfCenturies() << ", 100s: " << p2.getCenturies() << endl;
        cout << "Bowler: " << bowler.getName() << ", Overs: " << bowler.getOvers() << endl;
    }

    void saveStatsToFile() {
        ofstream file("playerstats.txt", ios::app);
        file << p1.getName() << " " << p1.getRuns() << " " << p1.getHalfCenturies()
             << " " << p1.getCenturies() << "\n";
        file << p2.getName() << " " << p2.getRuns() << " " << p2.getHalfCenturies()
             << " " << p2.getCenturies() << "\n";
        file << bowler.getName() << " " << bowler.getOvers() << "\n";
        file.close();
    }
};

int BatsmanBowler::oversThrown = 0;
int BatsmanBowler::runsScored = 0;
int BatsmanBowler::wicketsDown = 0;

int main() {
    BatsmanBowler match;
    int deliveries;
    cout << "Enter number of deliveries to simulate: ";
    cin >> deliveries;
    for (int i = 0; i < deliveries; ++i) {
        int runs;
        cout << "Enter runs for ball " << i+1 << ": ";
        cin >> runs;
        match.updateScore(runs);
    }
    match.printStats();
    match.saveStatsToFile();
    return 0;
}
