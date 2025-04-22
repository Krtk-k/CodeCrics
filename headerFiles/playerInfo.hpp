#pragma once

using namespace std;

class matchInfo{
    
    public:
        void createPlayerFile(string username);
        void displayPlayerInfo(string username);
        void updatePlayerInfo(int runs = 0, int overs = 0, int wickets = 0, int _50s = 0, int _100s = 0);
};