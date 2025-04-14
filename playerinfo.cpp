// playerinfo.cpp

#include "headerFiles/playerinfo.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

// Actual storage
map<string, PlayerStats> allPlayersStats;

bool isPlayerRegistered(const string& playerName) {
    ifstream file("username.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open username.txt" << endl;
        return false;
    }
    string name;
    while (getline(file, name)) {
        if (name == playerName) return true;
    }
    return false;
}

void loadPlayerStats() {
    ifstream file("playerinfo.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open playerinfo.txt" << endl;
        return;
    }

    string name;
    while (file >> name) {
        PlayerStats stats;
        file >> stats.runs >> stats.overs >> stats.wickets >> stats.halfCenturies >> stats.centuries;
        allPlayersStats[name] = stats;
    }
}

void savePlayerStats() {
    ofstream file("playerinfo.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open playerinfo.txt for writing" << endl;
        return;
    }
    for (const auto& [name, stats] : allPlayersStats) {
        file << name << " "
             << stats.runs << " "
             << stats.overs << " "
             << stats.wickets << " "
             << stats.halfCenturies << " "
             << stats.centuries << "\n";
    }
}

void updateStats(const string& name, int runs, int overs, int wickets) {
    if (allPlayersStats.find(name) == allPlayersStats.end()) {
        cerr << "Error: Player " << name << " not found in stats" << endl;
        return;
    }

    PlayerStats& stats = allPlayersStats[name];
    stats.runs += runs;
    stats.overs += overs;
    stats.wickets += wickets;

    if (stats.runs >= 50 && stats.halfCenturies == 0)
        stats.halfCenturies++;
    if (stats.runs >= 100 && stats.centuries == 0)
        stats.centuries++;
}

void printPlayerStats(const string& name) {
    if (allPlayersStats.find(name) != allPlayersStats.end()) {
        const PlayerStats& stats = allPlayersStats[name];
        cout << "Player: " << name << "\n";
        cout << "Runs: " << stats.runs << "\n";
        cout << "Overs: " << stats.overs << "\n";
        cout << "Wickets: " << stats.wickets << "\n";
        cout << "Half-Centuries: " << stats.halfCenturies << "\n";
        cout << "Centuries: " << stats.centuries << "\n";
    } else {
        cout << "No stats found for player: " << name << endl;
    }
}

void printAllPlayerStats() {
    if (allPlayersStats.empty()) {
        cout << "No player stats available." << endl;
        return;
    }

    for (const auto& pair : allPlayersStats) {
        const PlayerStats& stats = pair.second;
        cout << "\n👤 Player: " << pair.first
             << "\n🏏 Runs: " << stats.runs
             << "\n🎯 Overs Thrown: " << stats.overs
             << "\n🔥 Wickets: " << stats.wickets
             << "\n🥈 Half-Centuries: " << stats.halfCenturies
             << "\n🥇 Full-Centuries: " << stats.centuries
             << "\n-----------------------------\n";
    }
}