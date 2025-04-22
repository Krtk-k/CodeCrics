#pragma once

using namespace std;

void toLowerCase(string& name);
void toUpperCase(string& name);
bool isValidInteger(string& n);

class Players{
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
        matchInfo match;

        // TEAMS
        vector<string> battingTeamPlayers;
        vector<string> bowlingTeamPlayers;

    public:

        Players();

        // Checks whether the player entered by the user exists in our database or not
        bool playerExistsInDatabase(const string& player);

        // Checks whether the player entered by the user is in team or not
        bool playerExistsInTeam(const string& player, const vector<string>& teamPlayers);

        ~Players();
};

class BatsmanBowler:public Players{

    // BATSMAN
    string onStrike;
    string runningEnd;
    string batsman1;
    string batsman2;
    int b1Runs;
    int b2Runs;
    int b1Balls;
    int b2Balls;
    int runsScoredOnThisBall;
    int target;
    vector<string> outBatsmans;

    // BOWLER
    string bowler;
    int totalBalls;
    int ballsBowled;
    int overs;
    int wickets;
    int runsGiven;

    // STATIC VARIABLES
    static int oversThrown;
    static int runsScored;
    static int wicketsDown;
    static bool displayingRawScoreboard;

    int totalTeamPlayers;

    public:
        BatsmanBowler();
        void initializingSecondInnings();
        void strikeChange(int runs = 0, int balls = 0 ,string event = "");
        
        //  Function to check whether an over has been ended or not
        bool overUp(int balls);

        // Function to change Batsman when Batsman is OUT or HURT
        void changeBatsman(const string& outBatsman, string type = "OUT");

        // Function to change Bowler on overUp
        void changeBowler();

        // Friend Function
        friend string input(BatsmanBowler&);
        friend void scoreboard(string , BatsmanBowler&);

        ~BatsmanBowler();
};

void enteringScoringArea();