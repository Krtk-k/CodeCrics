#ifndef PLAYERINFO_HPP
#define PLAYERINFO_HPP

#include <string>
#include <map>
using namespace std;

struct PlayerStats {
    int runs = 0;
    int overs = 0;
    int wickets = 0;
    int halfCenturies = 0;
    int centuries = 0;
};

extern map<string, PlayerStats> allPlayersStats;

bool isPlayerRegistered(const string& playerName);
void loadPlayerStats();
void savePlayerStats();
void updateStats(const string& name, int runs, int overs, int wickets);
void printPlayerStats(const string& name);
void printAllPlayerStats();

#endif
