#ifndef PLAYER_H
#define PLAYER_H

#include <string>

// Struct to hold player stats
struct PlayerStats {
    int runs;
    int overs;
    int wickets;
    int halfCenturies;
    int centuries;
};

// Functions to update player stats
void updatePlayerRuns(const std::string& playerName, int newRuns);
void updatePlayerOvers(const std::string& playerName, int ballsBowled);
void updatePlayerWickets(const std::string& playerName, int newWickets);

#endif // PLAYER_H
