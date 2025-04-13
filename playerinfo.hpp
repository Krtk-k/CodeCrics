// playerinfo.h

#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <string>
#include <map>

struct PlayerStats {
    int runs = 0;
    int overs = 0;
    int wickets = 0;
    int halfCenturies = 0;
    int centuries = 0;
};

// Function declarations
bool isPlayerRegistered(const std::string& playerName);
void loadPlayerStats();
void savePlayerStats();
void updateStats(const std::string& name, int runs, int overs, int wickets);
void printPlayerStats(const std::string& name);

// Shared map of all players
extern std::map<std::string, PlayerStats> allPlayersStats;

#endif
