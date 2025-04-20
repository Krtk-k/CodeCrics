#include <iostream>
#include "headerFiles/textStyles.h"
#include "headerFiles/scorecard.h"
#include <vector>
#include <algorithm>
#include <fstream>

// For TOSS
#include <cstdlib>
#include <ctime>

using namespace std;

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

    public:

        Players(){
            cout<<endl<<"\t\t\t🎾🏏⚾️"<<UNDERLINE<<BOLD<<BRIGHT_WHITE<<" WELCOME TO THE SCORING AREA "<<RESET<<"⚾️🏏🎾"<<endl;
            cout<<endl<<"HOW MANY OVERS YOU WANT TO PLAY : ";
            cin>>totalOversToBePlayed;

            for(int i = 0;i<2;i++){
                if (i == 0){
                    cout<<"ENTER NAME of TEAM 1 : ";
                    cin>>team1;
                    teams.push_back(team1);
                }else{
                    cout<<"ENTER NAME of TEAM 2 : ";
                    cin>>team2;
                    teams.push_back(team2);
                }
                cin.ignore();

                cout<<"\nEnter Number of Players in TEAM "<<i+1<<" : ";
                cin>>n;
                cout<<"\nEnter Players (Make sure that the Player is Already Registered)\n\n";

                for(int j = 0;j<n;j++){

                    cout<<"Player "<<j+1<<" : ";
                    cin>>name;
                    if (i==0){
                        t1players.push_back(name);
                    }else{
                        t2players.push_back(name);
                    }
                    
                }
                cout<<endl;
                cin.ignore();
            }

            srand(time(0));
            cout<<endl<<BOLD<<YELLOW<<"COIN TOSSED !!"<<RESET<<endl;
            tossWinner = teams[rand() % 2];
            cout<<BOLD<<MAGENTA<<tossWinner<<YELLOW<<" WINS THE TOSS !!"<<endl<<endl;
            cout<<ORANGE<<"What do you want to choose (bat/bowl) : "<<RESET;
            cin>>choice;

            if (tossWinner == team1){
                tossLoser = team2;
            }else{
                tossLoser = team1;
            }

            cin.ignore();
        }

        ~Players(){}

};
struct Batsman{
    string name;
    string team;
    int runs;
    int balls;
};
struct Bowler{
string name;
string team;
int overs;
int runsGiven;
int wickets;
};
class Matchinfo {
public:
        void createMatchFile(vector<string> teams, vector<string> team1players, vector<string> team2players, string tosswinner, string choice, string match) {
        ofstream file("Match_" + match + ".txt");
        if (file.is_open()) {
            cout<<"Match: "<<match<<endl;
            cout<<"Teams: "<< teams[0] <<" vs "<< teams[1] <<endl;
            cout<<"Toss winner: " << tosswinner << endl;
            cout<<"choice: " << choice << endl;
            cout<<"Team 1 players: \n";
            for (string p : team1players) cout<< p <<endl;
            cout<< "Team 2 players: \n";
            for (string p : team2players) cout<< p <<endl;
            cout<<"Batsman stats: \n"; 
            file.close();
        }
    }

    void setBatsman(string name,int runs,int balls,string teamName,string match) {
        string fileName = "match" + match + "_" + teamName + "_batting.txt";
        vector<Batsman> allPlayers;
        Batsman player;

        ifstream inFile(fileName);
        if (inFile.is_open()) {
            while (inFile >> player.name >> player.team >> player.runs >> player.balls) {
                allPlayers.push_back(player);
            }
            inFile.close();
        }

        bool found = false;
        for (auto& p : allPlayers) {
            if (p.name == name && p.team == teamName) {
                p.runs += runs;
                p.balls += balls;
                found = true;
                break;
            }
        }


        ofstream outFile(fileName);
        if (outFile.is_open()) {
            for(auto& p : allPlayers) {
                outFile<<p.name <<" "<<p.team<<" "<<p.runs<<" "<<p.balls<<endl;
            }
        
            outFile.close();
            cout<<"Batsman "<<name<<"'s stats saved to "<<fileName<<endl;
        } else {
            cout << "Error opening file for writing: " << fileName << endl;
        }
    }

    vector<int> getBatsman(string name, string teamName, string match) {
        string fileName = "match" + match +"_"+teamName + "_batting.txt";
        ifstream file(fileName);
        string fileNameName, fileTeam;
        int runs, balls;
        vector<int> result;

        if (file.is_open()) {
            while (file >> fileNameName >> fileTeam >> runs >> balls) {
                if (fileNameName == name && fileTeam == teamName) {
                    result.push_back(runs);
                    result.push_back(balls);
                    break;
                }
            }
            file.close();
        } else {
            cout <<"Error opening file for reading: "<< fileName << endl;
        }

        return result;
    }
    void setBowler(string name, int overs, int runsGiven, int wickets, string teamName, string match) {
        string fileName = "match" + match + "_" + teamName + "_bowling.txt";
        vector<Bowler> allBowlers;
        Bowler bowler;

        ifstream inFile(fileName);
        if (inFile.is_open()) {
            while (inFile >>bowler.name >> bowler.team >> bowler.overs >> bowler.runsGiven >> bowler.wickets) {
                allBowlers.push_back(bowler);
            }
            inFile.close();
        }

        bool found = false;
        for (auto& b : allBowlers) {
            if (b.name == name && b.team == teamName) {
                b.overs += overs;
                b.runsGiven += runsGiven;
                b.wickets += wickets;
                found = true;
                break;
            }
        }

        ofstream outFile(fileName);
        if (outFile.is_open()) {
            for (auto& b : allBowlers) {
                outFile << b.name << " " << b.team << " " << b.overs << " " << b.runsGiven << " " << b.wickets << endl;
            }
            outFile.close();
            cout << "Bowler "<<name<< "'s stats saved to " << fileName << endl;
        } else {
            cout <<"Error in opening for writing: "<< fileName << endl;
        }
    }

    vector<int> getBowler(string name, string teamName, string match) {
        string fileName = "match" + match + "_" + teamName + "_bowling.txt";
        ifstream file(fileName);
        string bowlerName, bowlerTeam;
        int overs, runsGiven, wickets;
        vector<int> result;

        if (file.is_open()) {
            while (file >>bowlerName >>bowlerTeam >>overs >>runsGiven >>wickets) {
                if (bowlerName == name && bowlerTeam == teamName) {
                    result.push_back(overs);
                    result.push_back(runsGiven);
                    result.push_back(wickets);
                    break;
                }
            }
            file.close();
        } else {
            cout << "Error in opening the file for reading: " << fileName << endl;
        }

        return result;
    }
};

class BatsmanBowler:public Players{

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

        BatsmanBowler(){

            cout<<"\nEnter Name of Batsman on Striking End : ";
            cin>>onStrike;

            cout<<"Enter Name of Batsman on Running End : ";
            cin>>runningEnd;

            cout<<"Enter Name of Bowler : ";
            cin>>bowler;

            batsman1=onStrike;
            batsman2=runningEnd;
            runsScoredOnThisBall = 0;

            b1Runs = 0;
            b2Runs = 0;
            totalBalls = 6;
            ballsBowled = 0;
            overs = 0;
            wickets = 0;

        }

        void strikeChange(int runs = 0){
            if (runs%2 == 0 && batsman1==onStrike){

                b1Runs += runs;
                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<< " : "  <<b1Runs<<RESET<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<"\t  "<<runningEnd<<" : " <<b2Runs<<"\t\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<endl;

            }else if (runs%2 == 0 && batsman2==onStrike){

                b2Runs += runs;
                cout<<"\t  "<<runningEnd<<" : " <<b1Runs<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<< " : " <<b2Runs<<RESET<<"\t\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<endl;

            }else if (runs%2 != 0 && batsman1==onStrike){

                b1Runs += runs;
                string temp = onStrike;
                onStrike = runningEnd;
                runningEnd = temp;

                cout<<"\t  "<<runningEnd<<" : "<<b1Runs<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<<" : " <<b2Runs<<RESET<<"\t\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<endl;

            }else if (runs%2 != 0 && batsman2==onStrike){

                b2Runs += runs;
                string temp = onStrike;
                onStrike = runningEnd;
                runningEnd = temp;

                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<< " : " <<b1Runs<<RESET<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<"\t  "<<runningEnd<<" : " <<b2Runs<<"\t\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<endl;

            }else{
                cout<<"ERROR in strikeChange() !!";
            }
        }

        /// Function for changing batsman and bowler separately
        
        // Friend Function
        friend void scorecard(string , BatsmanBowler);

        ~BatsmanBowler(){}
};

// INITIALIZING STATIC VARIABLES OF BatsmanBowler CLASS
int BatsmanBowler::oversThrown = 0;
int BatsmanBowler::runsScored = 0;
int BatsmanBowler::wicketsDown = 0;

void scorecard(string inning, BatsmanBowler matchDetails){

    int totalTeamPlayers;
    if (inning =="(INNING : 1)"){
        if (matchDetails.choice == "bat"){
            if (matchDetails.tossWinner == matchDetails.team1){
                totalTeamPlayers = matchDetails.t1players.size();
            }else{
                totalTeamPlayers = matchDetails.t2players.size();
            }
        }else{
            if (matchDetails.tossLoser == matchDetails.team1){
                totalTeamPlayers = matchDetails.t1players.size();
            }else{
                totalTeamPlayers = matchDetails.t2players.size();
            }
        }
    }else{
        if (matchDetails.choice == "bat"){
            if (matchDetails.tossLoser == matchDetails.team1){
                totalTeamPlayers = matchDetails.t1players.size();
            }else{
                totalTeamPlayers = matchDetails.t2players.size();
            }
        }else{
            if (matchDetails.tossWinner == matchDetails.team1){
                totalTeamPlayers = matchDetails.t1players.size();
            }else{
                totalTeamPlayers = matchDetails.t2players.size();
            }
        }
    }

    while (matchDetails.totalOversToBePlayed != matchDetails.oversThrown && matchDetails.wicketsDown != (totalTeamPlayers-1) ){
        
        cout << endl << BOLD << UNDERLINE << BRIGHT_WHITE << "\t\t\t\t SCORECARD " << RESET <<endl;
        cout << endl << "\t\t                "<< ORANGE << inning <<RESET<<endl<<endl<<endl;
        cout << "\t\t\t "<< BLUE << matchDetails.tossWinner<<" CHOSE TO "<<matchDetails.choice<<" FIRST" <<RESET<<endl<<endl<<endl<<endl;
        
        if (inning =="(INNING : 1)"){
            if (matchDetails.choice == "bat"){
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossWinner<<"\t\t\t\t\t    "<<matchDetails.tossLoser<<RESET<<endl<<endl;
            }else{
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossLoser<<"\t\t\t\t\t    "<<matchDetails.tossWinner<<RESET<<endl<<endl;
            }
        }else{
            if (matchDetails.choice == "bat"){
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossLoser<<"\t\t\t\t\t    "<<matchDetails.tossWinner<<RESET<<endl<<endl;
            }else{
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossWinner<<"\t\t\t\t\t    "<<matchDetails.tossLoser<<RESET<<endl<<endl;
            }
        }
        matchDetails.strikeChange(matchDetails.runsScoredOnThisBall);
        cout<<endl<<endl<<BOLD<<BRIGHT_WHITE<<"\t\t\t\t  RUNS : "<<matchDetails.runsScored<<endl<<endl;
        cout<<BLUE<<"\t\t\t WICKETS/TOTAL WICKETS : "<<matchDetails.wicketsDown<<"/"<<(totalTeamPlayers-1)<<endl<<endl;
        cout<<BRIGHT_WHITE<<"\t\t\t   OVERS/TOTAL OVERS : "<<matchDetails.oversThrown<<"/"<<matchDetails.totalOversToBePlayed<<RESET<<endl<<endl;

        if (inning == "(INNING : 2)"){
            cout << "\t\t\t       "<< BG_BRIGHT_YELLOW << "TARGET" <<" : "<<matchDetails.target<<RESET<<endl<<endl;
            if (matchDetails.runsScored >= matchDetails.target){
                break;
            }

        }
// break is Just for trial
break;
    }

    if (inning == "(INNING : 1)"){
        matchDetails.target = matchDetails.runsScored;
    }

}

void enteringScoringArea(){

    BatsmanBowler matchDetails;
    cout<<endl<<endl<<BRIGHT_WHITE<<BOLD<<"THE MATCH BEGINS !!"<<RESET<<endl<<endl;
    scorecard("(INNING : 1)",matchDetails);
    cout<<endl<<endl<<BRIGHT_WHITE<<BOLD<<"INNINGS BREAK !!"<<RESET<<endl<<endl;
    scorecard("(INNING : 2)",matchDetails);
    cout<<endl<<endl<<BRIGHT_WHITE<<BOLD<<"MATCH ENDS !!"<<RESET<<endl<<endl;

}

int main() {
    enteringScoringArea();
}

// totalTeamPlayers problem to be resolved
// uske baad scoring kaise karni hai wo dekhna