#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct PlayerStats {
    int runs = 0;
    int overs = 0;
    int wickets = 0;
    int halfCenturies = 0;
    int centuries = 0;
};

// Function to load existing stats from file
PlayerStats loadStatsFromFile(const string& playerName) {
    PlayerStats stats;
    ifstream inFile(playerName + ".txt");
    if (inFile.is_open()) {
        string label;
        char ignoreChar;
        inFile >> label >> ignoreChar >> stats.runs;
        inFile >> label >> ignoreChar >> stats.overs;
        inFile >> label >> ignoreChar >> stats.wickets;
        inFile >> label >> ignoreChar >> stats.halfCenturies;
        inFile >> label >> ignoreChar >> stats.centuries;
        inFile.close();
    }
    return stats;
}

// Function to save updated stats to file
void saveStatsToFile(const string& playerName, const PlayerStats& stats) {
    ofstream outFile(playerName + ".txt");
    if (outFile.is_open()) {
        outFile << "username0/_____" << playerName << "\n";
        outFile << "Total runs scored0/_____" << stats.runs << "\n";
        outFile << "Total overs thrown 0/_____" << stats.overs << "\n";
        outFile << "Total wickets taken0/_____" << stats.wickets << "\n";
        outFile << "Total 50s(Half century)0/_____" << stats.halfCenturies << "\n";
        outFile << "Total 100s(Full century)0/_____" << stats.centuries << "\n";
        outFile.close();
    }
}

// Update stats: Runs
void updatePlayerRuns(const string& playerName, int newRuns) {
    PlayerStats stats = loadStatsFromFile(playerName);
    stats.runs += newRuns;
    if (newRuns >= 50 && newRuns < 100) stats.halfCenturies++;
    if (newRuns >= 100) stats.centuries++;
    saveStatsToFile(playerName, stats);
}

// Update stats: Overs
void updatePlayerOvers(const string& playerName, int ballsBowled) {
    PlayerStats stats = loadStatsFromFile(playerName);
    stats.overs += ballsBowled / 6;
    saveStatsToFile(playerName, stats);
}

// Update stats: Wickets
void updatePlayerWickets(const string& playerName, int newWickets) {
    PlayerStats stats = loadStatsFromFile(playerName);
    stats.wickets += newWickets;
    saveStatsToFile(playerName, stats);
}
