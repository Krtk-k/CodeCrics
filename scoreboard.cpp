#include <iostream>
#include "headerFiles/textStyles.hpp"
#include "headerFiles/scoreboard.hpp"
#include "headerFiles/matchInfo.hpp"
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>


// For TOSS
#include <cstdlib>
#include <ctime>

// For isdigit()
#include <cctype>

using namespace std;

// For converting string to lowercase
void toLowerCase(string& name){
    for(int i = 0;i<name.length();i++){
        if (name[i]>= 65 && name[i]<=90){
            name[i] = name[i] + 32;
        }
    }
}

// For converting string to uppercase
void toUpperCase(string& name){
    for(int i = 0;i<name.length();i++){
        if (name[i]>= 97 && name[i]<=122){
            name[i] = name[i] - 32;
        }
    }
}

// For checking whether the entered string is a valid number or not
bool isValidInteger(string& n){
    if (n.empty()) return false;

    for(int i = 0;i<n.length();i++){
        if (!isdigit(n[i])){
            return false;
        }
    }
    return true;
}

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

        Players(){
            cout<<endl<<"\t\t\t🎾🏏⚾️"<<UNDERLINE<<BOLD<<BRIGHT_WHITE<<" WELCOME TO THE SCORING AREA "<<RESET<<"⚾️🏏🎾"<<endl;

            while (1) {
                try{
                    string temp;
                    cout<<endl<<"HOW MANY OVERS YOU WANT TO PLAY : ";
                    cin>>temp;
                    if (isValidInteger(temp)){
                        totalOversToBePlayed = stoi(temp);
                        if (totalOversToBePlayed > 0){
                            break;
                        }
                        else{
                            throw "OVERS MUST BE GREATER THAN 0 !!";
                        }
                    }
                    else{
                        throw "KINDLY ENTER A VALID NUMBER !!";
                    }
                }
                catch (const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }

            cin.ignore();
            for(int i = 0;i<2;i++){
                if (i == 0){
                    cout<<"ENTER NAME of TEAM 1 : ";
                    getline(cin,team1);
                    teams.push_back(team1);
                }else{
                    while(1){
                        try{
                            cout<<"ENTER NAME of TEAM 2 : ";
                            getline(cin,team2);
                            if (team1 == team2){
                                throw "TEAM 1 and TEAM 2 cannot have the SAME NAME !!";
                            }
                            else{
                                teams.push_back(team2);
                                break;
                            }  
                        }
                        catch (const char * str){
                            cout<<BRIGHT_RED<<BOLD<<str<<endl<<"KINDLY ENTER A DIFFERENT TEAM NAME !!"<<RESET<<endl<<endl;
                        }
                    }
                }
                cin.ignore();

                while (1){
                    try{
                        string temp;
                        cout<<"Enter Number of Players in TEAM "<<teams[i]<<" : ";
                        cin>>temp;
                        if(isValidInteger(temp)){
                            n = stoi(temp);
                            if (n >= 2) break;
                            else throw 1;
                        }
                        else{
                            throw "KINDLY ENTER A VALID NUMBER !!";
                        }
                    }
                    catch(int i){
                        cout<<BRIGHT_RED<<BOLD<<"TEAM MUST HAVE 2 or MORE THAN 2 PLAYERS !!"<<RESET<<endl<<endl;
                    }
                    catch (const char * str){
                        cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                    }
                }
                cin.ignore();

                cout<<"\nEnter Players"<<BRIGHT_GREEN<<BOLD<<" (Make sure that the Player is Already Registered)"<<RESET<<endl;

                for(int j = 0;j<n;j++){
                    while (1){
                        try{
                            cout<<"Player "<<j+1<<" : ";
                            getline(cin,name);
                            toLowerCase(name);
                            if (playerExistsInDatabase(name)){
                                if (i==0){
                                    if (playerExistsInTeam(name,t1players)){
                                        cout<<BOLD<<BRIGHT_RED<<"CAN'T ADD PLAYER "<<YELLOW<<name<<BRIGHT_RED<<" AS "<<YELLOW<<name<<BRIGHT_RED<<" IS ALREADY IN TEAM "<<teams[0]<<" !!"<<RESET<<endl<<endl;
                                    }
                                    else{
                                        t1players.push_back(name);
                                        break;
                                    }
                                    
                                }
                                else{
                                    if (playerExistsInTeam(name,t1players)){
                                        cout<<BOLD<<BRIGHT_RED<<"CAN'T ADD PLAYER "<<YELLOW<<name<<BRIGHT_RED<<" AS "<<YELLOW<<name<<BRIGHT_RED<<" IS ALREADY IN TEAM "<<teams[0]<<" !!"<<RESET<<endl<<endl;
                                    }
                                    else if(playerExistsInTeam(name,t2players)){
                                        cout<<BOLD<<BRIGHT_RED<<"CAN'T ADD PLAYER "<<YELLOW<<name<<BRIGHT_RED<<" AS "<<YELLOW<<name<<BRIGHT_RED<<" IS ALREADY IN TEAM "<<teams[1]<<" !!"<<RESET<<endl<<endl;
                                    }
                                    else{
                                        t2players.push_back(name);
                                        break;
                                    }
                                }
                                
                            }
                            else{
                                throw "USERNAME NOT REGISTERED IN DATABASE";
                            }
                        }
                        catch(const char* str){
                            cout<<YELLOW<<BOLD<<name<<BRIGHT_RED<<" IS NOT REGISTERED !!"<<endl<<"KINDLY ENTER REGISTERED PLAYERS ONLY !!"<<RESET<<endl<<endl;
                        }
                    }
                }
                cout<<endl;
            }

            match.createMatchFiles(teams,t1players,t2players);

            srand(time(0));
            cout<<endl<<BOLD<<YELLOW<<"COIN TOSSED !!"<<RESET<<endl;
            tossWinner = teams[rand() % 2];
            cout<<BOLD<<MAGENTA<<tossWinner<<YELLOW<<" WINS THE TOSS !!"<<RESET<<endl<<endl;

            while (1){
                try{
                    cout<<BOLD<<ORANGE<<"What do you want to choose (BAT/BOWL) : "<<RESET;
                    cin>>choice;
                    toUpperCase(choice);
                    if (choice == "BAT" || choice == "BOWL"){
                        break;
                    }
                    else{
                        throw "KINDLY ENTER BAT / BOWL ONLY !!";
                    }
                }
                catch(const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }
            cout<<endl;
            
            // Storing TossWinner & TossLoser
            if (tossWinner == team1){
                tossLoser = team2;
            }
            else{
                tossLoser = team1;
            }

            // Storing BattingTeamPlayers & BowlingTeamPlayers....these wil get swap in INNINGS 2
            if (choice == "BAT"){
                if (tossWinner == team1){
                    battingTeamPlayers = t1players;
                    bowlingTeamPlayers = t2players;
                }
                else{
                    battingTeamPlayers = t2players;
                    bowlingTeamPlayers = t1players;
                }
            }
            else{
                if (tossWinner == team1){
                    battingTeamPlayers = t2players;
                    bowlingTeamPlayers = t1players;
                }
                else{
                    battingTeamPlayers = t1players;
                    bowlingTeamPlayers = t2players;
                }
            }
            cin.ignore();
        }

        // Checks whether the player entered by the user exists in our database or not
        bool playerExistsInDatabase(const string& player){
            ifstream file("mainDir/loginInfo/userLogin.txt");
            string line;
            while(getline(file,line)){
                int pos = line.find('\0');
                string username = line.substr(0,pos);
                if (username == player){
                    file.close();
                    return true;
                }
            }
            file.close();
            return false;
        }

        // Checks whether the player entered by the user is in team or not
        bool playerExistsInTeam(const string& player, const vector<string>& teamPlayers){
            return find(teamPlayers.begin(), teamPlayers.end(), player) != teamPlayers.end();
        }

        ~Players(){}
        
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

        BatsmanBowler(){

            while(1){
                try{
                    cout<<"Enter Name of Batsman on Striking End : ";
                    getline(cin,onStrike);
                    toLowerCase(onStrike);
                    if (playerExistsInTeam(onStrike,battingTeamPlayers)){
                        break;
                    }
                    else{
                        throw "PLAYER NOT IN TEAM !!";
                    }
                }
                catch (const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }

            while(1){
                try{
                    cout<<"Enter Name of Batsman on Running End : ";
                    getline(cin,runningEnd);
                    toLowerCase(runningEnd);
                    if (playerExistsInTeam(runningEnd,battingTeamPlayers)){
                        break;
                    }
                    else{
                        throw "PLAYER NOT IN TEAM !!";
                    }
                }
                catch (const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }

            while(1){
                try{
                    cout<<"Enter Name of Bowler : ";
                    getline(cin,bowler);
                    toLowerCase(bowler);
                    if (playerExistsInTeam(bowler,bowlingTeamPlayers)){
                        break;
                    }
                    else{
                        throw "PLAYER NOT IN TEAM !!";
                    }
                }
                catch (const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }
            cin.ignore();

            batsman1=onStrike;
            batsman2=runningEnd;
            runsScoredOnThisBall = 0;

            b1Runs = 0;
            b2Runs = 0;
            b1Balls = 0;
            b2Balls = 0;
            totalBalls = 6;
            ballsBowled = 0;
            overs = 0;
            wickets = 0;
            runsGiven = 0;

        }

        void initializingSecondInnings(){

            // Swapping BattingTeamPlayers and BowlingTeamPlayers Vectors
            swap(battingTeamPlayers,bowlingTeamPlayers);

            while(1){
                try{
                    cout<<"Enter Name of Batsman on Striking End : ";
                    getline(cin,onStrike);
                    toLowerCase(onStrike);
                    if (playerExistsInTeam(onStrike,battingTeamPlayers)){
                        break;
                    }
                    else{
                        throw "PLAYER NOT IN TEAM !!";
                    }
                }
                catch (const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }

            while(1){
                try{
                    cout<<"Enter Name of Batsman on Running End : ";
                    getline(cin,runningEnd);
                    toLowerCase(runningEnd);
                    if (playerExistsInTeam(runningEnd,battingTeamPlayers)){
                        break;
                    }
                    else{
                        throw "PLAYER NOT IN TEAM !!";
                    }
                }
                catch (const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }

            while(1){
                try{
                    cout<<"Enter Name of Bowler : ";
                    getline(cin,bowler);
                    toLowerCase(bowler);
                    if (playerExistsInTeam(bowler,bowlingTeamPlayers)){
                        break;
                    }
                    else{
                        throw "PLAYER NOT IN TEAM !!";
                    }
                }
                catch (const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }
            cin.ignore();

            batsman1=onStrike;
            batsman2=runningEnd;
            runsScoredOnThisBall = 0;

            b1Runs = 0;
            b2Runs = 0;
            b1Balls = 0;
            b2Balls = 0;
            totalBalls = 6;
            ballsBowled = 0;
            overs = 0;
            wickets = 0;
            runsGiven = 0;

            oversThrown = 0;
            runsScored = 0;
            wicketsDown = 0;

            outBatsmans.clear();

        }
        void strikeChange(int runs = 0, int balls = 0 ,string event = ""){
            if (runs%2 == 0 && batsman1==onStrike){
                if (event != "Leg Byes" && event != "Byes" && event != "Wide Ball" && event != "Bowled" && event != "Caught" && event != "LBW" && event != "Stumped" && event != "Hit Wicket" && event != "Retired Hurt" && event != "Retired Out" && event != "OVER UP"&& event != "Run Out"){
                    b1Runs += runs;
                }

                if (event != "No Ball" && event != "Wide Ball" && event != "Retired Hurt" && event != "Retired Out" && event != "OVER UP" && event != "Bowled" && event != "Caught" && event != "LBW" && event != "Stumped" && event != "Hit Wicket" && event != "Run Out"){
                    b1Balls += balls;
                }

                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<< " : "  <<b1Runs<<" runs in "<<b1Balls<<" balls"<<RESET<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<"\t  "<<runningEnd<<" : " <<b2Runs<<" runs in "<<b2Balls<<" balls"<<"\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<"\tRUNS : "<<runsGiven<<endl;

            }else if (runs%2 == 0 && batsman2==onStrike){
                if (event != "Leg Byes" && event != "Byes" && event != "Wide Ball" && event != "Bowled" && event != "Caught" && event != "LBW" && event != "Stumped" && event != "Hit Wicket" && event != "Retired Hurt" && event != "Retired Out" && event != "OVER UP"&& event != "Run Out"){
                    b2Runs += runs;
                }
                
                if (event != "No Ball" && event != "Wide Ball" && event != "Retired Hurt" && event != "Retired Out" && event != "OVER UP" && event != "Bowled" && event != "Caught" && event != "LBW" && event != "Stumped" && event != "Hit Wicket" && event != "Run Out"){
                    b2Balls += balls;
                }

                cout<<"\t  "<<runningEnd<<" : " <<b1Runs<<" runs in "<<b1Balls<<" balls"<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<< " : " <<b2Runs<<" runs in "<<b2Balls<<" balls"<<RESET<<"\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<"\tRUNS : "<<runsGiven<<endl;
                
            }else if (runs%2 != 0 && batsman1==onStrike){

                if (event != "Leg Byes" && event != "Byes" && event != "Wide Ball" && event != "Bowled" && event != "Caught" && event != "LBW" && event != "Stumped" && event != "Hit Wicket" && event != "Retired Hurt" && event != "Retired Out" && event != "OVER UP"&& event != "Run Out"){
                    b1Runs += runs;
                }

                if (event != "No Ball" && event != "Wide Ball" && event != "Retired Hurt" && event != "Retired Out" && event != "OVER UP"&& event != "Bowled" && event != "Caught" && event != "LBW" && event != "Stumped" && event != "Hit Wicket" && event != "Run Out"){
                    b1Balls += balls;
                }

                string temp = onStrike;
                onStrike = runningEnd;
                runningEnd = temp;

                cout<<"\t  "<<runningEnd<<" : "<<b1Runs<<" runs in "<<b1Balls<<" balls"<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<<" : " <<b2Runs<<" runs in "<<b2Balls<<" balls"<<RESET<<"\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<"\tRUNS : "<<runsGiven<<endl;
                
            }else if (runs%2 != 0 && batsman2==onStrike){

                if (event != "Leg Byes" && event != "Byes" && event != "Wide Ball" && event != "Bowled" && event != "Caught" && event != "LBW" && event != "Stumped" && event != "Hit Wicket" && event != "Retired Hurt" && event != "Retired Out" && event != "OVER UP"&& event != "Run Out"){
                    b2Runs += runs;
                }
                
                if (event != "No Ball" && event != "Wide Ball" && event != "Retired Hurt" && event != "Retired Out" && event != "OVER UP"&& event != "Bowled" && event != "Caught" && event != "LBW" && event != "Stumped" && event != "Hit Wicket" && event != "Run Out"){
                    b2Balls += balls;
                }

                string temp = onStrike;
                onStrike = runningEnd;
                runningEnd = temp;

                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<< " : " <<b1Runs<<" runs in "<<b1Balls<<" balls"<<RESET<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<"\t  "<<runningEnd<<" : " <<b2Runs<<" runs in "<<b2Balls<<" balls"<<"\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<"\tRUNS : "<<runsGiven<<endl;

            }else{
                cout<<"ERROR in strikeChange() !!";
            }
        }

        //  Function to check whether an over has been ended or not
        bool overUp(int balls){
            if (balls == totalBalls){
                return true;
            }
            else{
                return false;
            }
        }

        // Function to change Batsman when Batsman is OUT or HURT
        void changeBatsman(const string& outBatsman, string type = "OUT"){

            // Updating data of outBatsman
            if (battingTeamPlayers == t1players){
                if (outBatsman == batsman1){
                    match.setBatsman(outBatsman,b1Runs,b1Balls,team1);
                }
                else{
                    match.setBatsman(outBatsman,b2Runs,b2Balls,team1);
                }
            }
            else{
                if (outBatsman == batsman1){
                    match.setBatsman(outBatsman,b1Runs,b1Balls,team2);
                }
                else{
                    match.setBatsman(outBatsman,b2Runs,b2Balls,team2);
                }
            }

            string newBatsman;

            if (type == "OUT"){
                outBatsmans.push_back(outBatsman);
            }

            cin.ignore();
            while(1){
                cout<<"Enter Name of New Batsman : ";
                getline(cin,newBatsman);
                if (playerExistsInTeam(newBatsman,battingTeamPlayers)){
                    if (!playerExistsInTeam(newBatsman,outBatsmans) && newBatsman != onStrike && newBatsman != runningEnd){
                        if (outBatsman  == onStrike){
                            if (outBatsman == batsman1){
                                batsman1 = newBatsman;
                                b1Runs = 0;
                                b1Balls = 0;
                            }
                            else{
                                batsman2 = newBatsman;
                                b2Runs = 0;
                                b2Balls = 0;
                            }
                            onStrike = newBatsman;
                        }
                        else{
                            if (outBatsman == batsman1){
                                batsman1 = newBatsman;
                                b1Runs = 0;
                                b1Balls = 0;
                            }
                            else{
                                batsman2 = newBatsman;
                                b2Runs = 0;
                                b2Balls = 0;
                            }
                            runningEnd = newBatsman;
                        }
                        break;
                    }
                    else{
                        cout<<BRIGHT_RED<<BOLD<<"THIS PLAYER IS ALREADY OUT or THIS PLAYER IS ALREADY ON CREASE !!"<<RESET<<endl<<endl;
                    }
                }
                else{
                    cout<<BRIGHT_RED<<BOLD<<"PLAYER NOT IN TEAM !!"<<RESET<<endl<<endl;
                }
            }
        }

        // Function to change Bowler on overUp
        void changeBowler(){
            string newBowler;
            
            cin.ignore();
            while(1){
                try{
                    cout<<"Enter Name of New Bowler : ";
                    getline(cin,newBowler);
                    if (playerExistsInTeam(newBowler,bowlingTeamPlayers)){
                        if (newBowler != bowler){
                            vector<int> newBowlerData;
                            // Updating current bowler data & Retrieving new bowler data
                            if (bowlingTeamPlayers == t1players){
                                match.setBowler(bowler,overs, wickets, runsGiven , team1);
                                newBowlerData = match.getBowler(newBowler,team1);
                            }
                            else{
                                match.setBowler(bowler,overs, wickets, runsGiven , team2);
                                newBowlerData = match.getBowler(newBowler,team2);
                            }

                            bowler = newBowler;
                            ballsBowled = 0;
                            overs = newBowlerData[0];
                            wickets = newBowlerData[1];
                            runsGiven = newBowlerData[2];
                            
                            break;
                        }
                        else{
                            throw 1;
                        }
                    }
                    else{
                        throw "PLAYER NOT IN TEAM !!";
                    }
                }
                catch(int n){
                    cout<<BRIGHT_RED<<BOLD<<"SAME PLAYER CAN'T BOWL 2 OVERS CONTINUOUSLY !!"<<RESET<<endl<<endl;
                }
                catch(const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }
        }
        
        // Friend Function
        friend string input(BatsmanBowler&);
        friend void scoreboard(string , BatsmanBowler&);

        ~BatsmanBowler(){}
};

// INITIALIZING STATIC VARIABLES OF BatsmanBowler CLASS
int BatsmanBowler::oversThrown = 0;
int BatsmanBowler::runsScored = 0;
int BatsmanBowler::wicketsDown = 0;
bool BatsmanBowler::displayingRawScoreboard = true;

//Input Function for Taking User Input
string input(BatsmanBowler& matchDetails){
    
    string event;
    cout<<CYAN<<"SELECT EVENT"<<endl<<endl;
    cout<<"PRESS 1 : Dot Ball"<<endl;
    cout<<"PRESS 2 : Four"<<endl;
    cout<<"PRESS 3 : Six"<<endl;
    cout<<"PRESS 4 : Regular Runs"<<endl;
    cout<<"PRESS 5 : Leg Byes"<<endl;
    cout<<"PRESS 6 : Byes"<<endl;
    cout<<"PRESS 7 : No Ball"<<endl;
    cout<<"PRESS 8 : Wide Ball"<<endl;
    cout<<"PRESS 9 : Out"<<endl;
    cout<<"PRESS 10 : Retired Hurt"<<endl;
    cout<<"PRESS 11 : Retired Out"<<RESET<<endl<<endl;

    while(1){
        cout<<"Enter Number : ";
        cin>>event;
    
        if (event == "1"){
            matchDetails.runsScoredOnThisBall = 0;
            matchDetails.ballsBowled ++;
            return "Dot Ball";
        }
        else if(event == "2"){
            matchDetails.runsScoredOnThisBall = 4;
            matchDetails.ballsBowled ++;
            matchDetails.runsGiven += 4;
            matchDetails.runsScored += 4;
            return "Four";
        }
        else if(event == "3"){
            matchDetails.runsScoredOnThisBall = 6;
            matchDetails.ballsBowled ++;
            matchDetails.runsGiven += 6;
            matchDetails.runsScored += 6;
            return "Six";
        }
        else if(event == "4"){
            while (1){
                try{
                    string temp;
                    cout<<"\nEnter Runs Taken : ";
                    cin>>temp;
                    if (isValidInteger(temp)){
                        matchDetails.runsScoredOnThisBall = stoi(temp);
                        matchDetails.ballsBowled ++;
                        matchDetails.runsGiven += matchDetails.runsScoredOnThisBall;
                        matchDetails.runsScored += matchDetails.runsScoredOnThisBall;
                        return "Regular Runs";
                    }
                    else{
                        throw "KINDLY ENTER VALID RUNS !!";
                    }
                }
                catch (const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }
        }
        else if(event == "5"){
            while(1){
                try{
                    string temp;
                    cout<<"\nEnter Runs Taken : ";
                    cin>>temp;
                    if (isValidInteger(temp)){
                        matchDetails.runsScoredOnThisBall = stoi(temp);
                        matchDetails.ballsBowled ++;
                        matchDetails.runsGiven += matchDetails.runsScoredOnThisBall;
                        matchDetails.runsScored += matchDetails.runsScoredOnThisBall;
                        return "Leg Byes";
                    }
                    else{
                        throw "KINDLY ENTER VALID RUNS !!";
                    }
                }
                catch(const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }
        }
        else if(event == "6"){
            while(1){
                try{
                    string temp;
                    cout<<"\nEnter Runs Taken : ";
                    cin>>temp;
                    if (isValidInteger(temp)){
                        matchDetails.runsScoredOnThisBall = stoi(temp);
                        matchDetails.ballsBowled ++;
                        matchDetails.runsGiven += matchDetails.runsScoredOnThisBall;
                        matchDetails.runsScored += matchDetails.runsScoredOnThisBall;
                        return "Byes";
                    }
                    else{
                        throw "KINDLY ENTER VALID RUNS !!";
                    }
                }
                catch(const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }
        }
        else if(event == "7"){
            while(1){
                try{
                    string temp;
                    cout<<"\nEnter Runs Taken : ";
                    cin>>temp;
                    if (isValidInteger(temp)){
                        matchDetails.runsScoredOnThisBall = stoi(temp);
                        matchDetails.runsGiven += (matchDetails.runsScoredOnThisBall+1);
                        matchDetails.runsScored += (matchDetails.runsScoredOnThisBall+1);
                        return "No Ball";
                    }
                    else{
                        throw "KINDLY ENTER VALID RUNS !!";
                    }
                }
                catch(const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }
        }
        else if(event == "8"){
            while(1){
                try{
                    string temp;
                    cout<<"\nEnter Runs Taken : ";
                    cin>>temp;
                    if (isValidInteger(temp)){
                        matchDetails.runsScoredOnThisBall = stoi(temp);
                        matchDetails.runsGiven += (matchDetails.runsScoredOnThisBall+1);
                        matchDetails.runsScored += (matchDetails.runsScoredOnThisBall+1);
                        return "Wide Ball";
                    }
                    else{
                        throw "KINDLY ENTER VALID RUNS !!";
                    }
                }
                catch(const char * str){
                    cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                }
            }
        }
        else if(event == "9"){
            string n;
            cout<<CYAN<<"\nSELECT TYPE OF DISMISSAL"<<endl<<endl;
            cout<<"PRESS 1 : Bowled"<<endl;
            cout<<"PRESS 2 : Caught"<<endl;
            cout<<"PRESS 3 : LBW"<<endl;
            cout<<"PRESS 4 : Run Out"<<endl;
            cout<<"PRESS 5 : Stumped"<<endl;
            cout<<"PRESS 6 : Hit Wicket"<<RESET<<endl<<endl;

            while(1){
                cout<<"Enter Number : ";
                cin>>n;
                if(n == "1"){
                    matchDetails.runsScoredOnThisBall = 0;
                    matchDetails.ballsBowled++;
                    matchDetails.wickets++;
                    matchDetails.wicketsDown++;

                    if (matchDetails.wicketsDown < (matchDetails.totalTeamPlayers-1)){
                        matchDetails.changeBatsman(matchDetails.onStrike);
                    }
                    
                    return "Bowled";
                }
                else if(n == "2"){
                    matchDetails.runsScoredOnThisBall = 0;
                    matchDetails.ballsBowled++;
                    matchDetails.wickets++;
                    matchDetails.wicketsDown++;

                    if (matchDetails.wicketsDown < (matchDetails.totalTeamPlayers-1)){
                        matchDetails.changeBatsman(matchDetails.onStrike);
                    }

                    return "Caught";
                }
                else if(n == "3"){
                    matchDetails.runsScoredOnThisBall = 0;
                    matchDetails.ballsBowled++;
                    matchDetails.wickets++;
                    matchDetails.wicketsDown++;

                    if (matchDetails.wicketsDown < (matchDetails.totalTeamPlayers-1)){
                        matchDetails.changeBatsman(matchDetails.onStrike);
                    }

                    return "LBW";
                }
                else if(n == "4"){
                    matchDetails.wicketsDown++;
                    while(1){
                        try{
                            string temp;
                            cout<<"\nEnter Runs Taken : ";
                            cin>>temp;
                            if (isValidInteger(temp)){
                                matchDetails.runsScoredOnThisBall = stoi(temp);
                                matchDetails.runsGiven += matchDetails.runsScoredOnThisBall;
                                matchDetails.runsScored += matchDetails.runsScoredOnThisBall;
                                break;
                            }
                            else{
                                throw "KINDLY ENTER VALID RUNS !!";
                            }
                        }
                        catch(const char * str){
                            cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                        }
                    }

                    cin.ignore();
                    while (1){
                        try{
                            string name;
                            cout<<"\nEnter Name of Batsman who got RUN OUT : ";
                            getline(cin,name);
                            if (name == matchDetails.onStrike || name == matchDetails.runningEnd){
                                if (name == matchDetails.batsman1){
                                    matchDetails.b1Runs += matchDetails.runsScoredOnThisBall;
                                    matchDetails.b1Balls++;
                                }
                                else{
                                    matchDetails.b2Runs += matchDetails.runsScoredOnThisBall;
                                    matchDetails.b2Balls++;
                                }

                                if (matchDetails.wicketsDown < (matchDetails.totalTeamPlayers-1)){
                                    matchDetails.changeBatsman(name);
                                }
                                break;
                            }
                            else{
                                throw "PLAYER NOT ON CREASE !!";
                            }
                        }
                        catch (const char * str){
                            cout<<BRIGHT_RED<<BOLD<<str<<RESET<<endl<<endl;
                        }
                    }
                    return "Run Out";        
                }
                else if(n == "5"){
                    matchDetails.runsScoredOnThisBall = 0;
                    matchDetails.ballsBowled++;
                    matchDetails.wickets++;
                    matchDetails.wicketsDown++;

                    if (matchDetails.wicketsDown < (matchDetails.totalTeamPlayers-1)){
                        matchDetails.changeBatsman(matchDetails.onStrike);
                    }

                    return "Stumped";
                }
                else if(n == "6"){
                    matchDetails.runsScoredOnThisBall = 0;
                    matchDetails.ballsBowled++;
                    matchDetails.wickets++;
                    matchDetails.wicketsDown++;

                    if (matchDetails.wicketsDown < (matchDetails.totalTeamPlayers-1)){
                        matchDetails.changeBatsman(matchDetails.onStrike);
                    }

                    return "Hit Wicket";
                }
                else{
                    cout<<BOLD<<BRIGHT_RED<<"\nINVALID INPUT !!\n\n"<<RESET;
                }
            }
        }
        else if(event == "10"){
            string retiredHurt;
            string newBatsman;
            while(1){
                cout<<"\nWho is Retired Hurt ?\n\nPRESS 1 for Batsman at Striking End\nPRESS 2 for Batsman at Running End\n\n";
                cout<<"Enter Number : ";
                cin>>retiredHurt;
                if (isValidInteger(retiredHurt)){
                    if (retiredHurt == "1" || retiredHurt == "2"){
                        break;
                    }
                }
                cout<<BOLD<<BRIGHT_RED<<"\nINVALID INPUT !!\n\n"<<RESET;
            }

            if (matchDetails.wicketsDown < (matchDetails.totalTeamPlayers-1) && ((matchDetails.totalTeamPlayers-1) - matchDetails.wicketsDown) != 1){
                if (retiredHurt == "1"){
                    matchDetails.changeBatsman(matchDetails.onStrike,"HURT");
                }
                else if(retiredHurt == "2"){
                    matchDetails.changeBatsman(matchDetails.runningEnd,"HURT");
                }
            }
            else{
                matchDetails.wicketsDown++;
            }
            matchDetails.runsScoredOnThisBall = 0;
            return "Retired Hurt";
        }
        else if(event == "11"){
            string retiredOut;
            string newBatsman;
            matchDetails.wicketsDown++;
            while(1){
                cout<<"\nWho is Retired Out ?\n\nPRESS 1 for Batsman at Striking End\nPRESS 2 for Batsman at Running End\n\n";
                cout<<"Enter Number : ";
                cin>>retiredOut;
                if (isValidInteger(retiredOut)){
                    if (retiredOut == "1" || retiredOut == "2"){
                        break;
                    }
                }
                cout<<BOLD<<BRIGHT_RED<<"\nINVALID INPUT !!\n\n"<<RESET;
            }
            
            if (matchDetails.wicketsDown < (matchDetails.totalTeamPlayers-1)){
                if (retiredOut == "1"){
                    matchDetails.changeBatsman(matchDetails.onStrike);
                }
                else if(retiredOut == "2"){
                    matchDetails.changeBatsman(matchDetails.runningEnd);
                }
            }
            matchDetails.runsScoredOnThisBall = 0;
            return "Retired Out";
        }
        else{
            cout<<BOLD<<BRIGHT_RED<<"\nINVALID INPUT !!\n\n"<<RESET;
        }
    }
}

void scoreboard(string inning, BatsmanBowler& matchDetails){

    string event;
    if (inning =="(INNING : 1)"){
        if (matchDetails.choice == "BAT"){
            if (matchDetails.tossWinner == matchDetails.team1){
                matchDetails.totalTeamPlayers = matchDetails.t1players.size();
            }else{
                matchDetails.totalTeamPlayers = matchDetails.t2players.size();
            }
        }else{
            if (matchDetails.tossLoser == matchDetails.team1){
                matchDetails.totalTeamPlayers = matchDetails.t1players.size();
            }else{
                matchDetails.totalTeamPlayers = matchDetails.t2players.size();
            }
        }
    }
    else{
        if (matchDetails.choice == "BAT"){
            if (matchDetails.tossLoser == matchDetails.team1){
                matchDetails.totalTeamPlayers = matchDetails.t1players.size();
            }else{
                matchDetails.totalTeamPlayers = matchDetails.t2players.size();
            }
        }else{
            if (matchDetails.tossWinner == matchDetails.team1){
                matchDetails.totalTeamPlayers = matchDetails.t1players.size();
            }else{
                matchDetails.totalTeamPlayers = matchDetails.t2players.size();
            }
        }
    }

    bool battingTeamWon = false;
    while (matchDetails.totalOversToBePlayed >= matchDetails.oversThrown && matchDetails.wicketsDown <= (matchDetails.totalTeamPlayers-1) ){
        
        cout << endl << BOLD << UNDERLINE << BRIGHT_WHITE << "\t\t\t\t SCOREBOARD " << RESET <<endl;
        cout << endl << "\t\t                "<< ORANGE << inning <<RESET<<endl<<endl<<endl;
        cout << "\t\t\t "<< BLUE << matchDetails.tossWinner<<" CHOSE TO "<<matchDetails.choice<<" FIRST" <<RESET<<endl<<endl<<endl<<endl;
        
        if (inning =="(INNING : 1)"){
            if (matchDetails.choice == "BAT"){
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossWinner<<"\t\t\t\t\t\t\t"<<matchDetails.tossLoser<<RESET<<endl<<endl;
            }else{
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossLoser<<"\t\t\t\t\t\t\t"<<matchDetails.tossWinner<<RESET<<endl<<endl;
            }
        }else{
            if (matchDetails.choice == "BAT"){
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossLoser<<"\t\t\t\t\t\t\t"<<matchDetails.tossWinner<<RESET<<endl<<endl;
            }else{
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossWinner<<"\t\t\t\t\t\t\t"<<matchDetails.tossLoser<<RESET<<endl<<endl;
            }
        }

        if(matchDetails.displayingRawScoreboard == true){
            matchDetails.strikeChange();
            matchDetails.displayingRawScoreboard = false;
        }
        else{
            matchDetails.strikeChange(matchDetails.runsScoredOnThisBall,1,event);
        }
        
        cout<<endl<<endl<<BOLD<<BRIGHT_WHITE<<"\t\t\t\t  RUNS : "<<matchDetails.runsScored<<endl<<endl;
        cout<<BLUE<<"\t\t\t WICKETS/TOTAL WICKETS : "<<matchDetails.wicketsDown<<"/"<<(matchDetails.totalTeamPlayers-1)<<endl<<endl;
        cout<<BRIGHT_WHITE<<"\t\t\t   OVERS/TOTAL OVERS : "<<matchDetails.oversThrown<<"/"<<matchDetails.totalOversToBePlayed<<RESET<<endl<<endl;

        if (inning == "(INNING : 2)"){
            cout << "\t\t\t         "<< BG_BRIGHT_YELLOW << "TARGET" <<" : "<<matchDetails.target<<RESET<<endl<<endl;
            if (matchDetails.runsScored >= matchDetails.target){
                if(matchDetails.battingTeamPlayers == matchDetails.t1players){
                    cout<<endl<<BOLD<<BG_GREEN<<matchDetails.team1<<" won by "<< ((matchDetails.totalTeamPlayers-1) - matchDetails.wicketsDown) << " wickets !!"<<RESET<<endl;
                    matchDetails.match.totalMatchesOnPlatformDetails(matchDetails.teams, matchDetails.team1);
                }
                else{
                    cout<<endl<<BOLD<<BG_GREEN<<matchDetails.team2<<" won by "<< ((matchDetails.totalTeamPlayers-1) - matchDetails.wicketsDown) << " wickets !!"<<RESET<<endl;
                    matchDetails.match.totalMatchesOnPlatformDetails(matchDetails.teams, matchDetails.team2);
                }
                battingTeamWon = true;

                // Updating data of last Batsmans & last Bowler
                if (matchDetails.battingTeamPlayers == matchDetails.t1players){
                    matchDetails.match.setBatsman(matchDetails.batsman1,matchDetails.b1Runs,matchDetails.b1Balls,matchDetails.team1);    
                    matchDetails.match.setBatsman(matchDetails.batsman2,matchDetails.b2Runs,matchDetails.b2Balls,matchDetails.team1);  
                    matchDetails.match.setBowler(matchDetails.bowler,matchDetails.overs, matchDetails.wickets, matchDetails.runsGiven , matchDetails.team2); 
                }
                else{
                    matchDetails.match.setBatsman(matchDetails.batsman1,matchDetails.b1Runs,matchDetails.b1Balls,matchDetails.team2);    
                    matchDetails.match.setBatsman(matchDetails.batsman2,matchDetails.b2Runs,matchDetails.b2Balls,matchDetails.team2); 
                    matchDetails.match.setBowler(matchDetails.bowler,matchDetails.overs, matchDetails.wickets, matchDetails.runsGiven , matchDetails.team1);
                }

                break;
            }
        }

        if (matchDetails.totalOversToBePlayed == matchDetails.oversThrown || matchDetails.wicketsDown == (matchDetails.totalTeamPlayers - 1)){
            
            // Updating data of last Batsmans & last Bowler
            if (matchDetails.battingTeamPlayers == matchDetails.t1players){
                matchDetails.match.setBatsman(matchDetails.batsman1,matchDetails.b1Runs,matchDetails.b1Balls,matchDetails.team1);    
                matchDetails.match.setBatsman(matchDetails.batsman2,matchDetails.b2Runs,matchDetails.b2Balls,matchDetails.team1);  
                matchDetails.match.setBowler(matchDetails.bowler,matchDetails.overs, matchDetails.wickets, matchDetails.runsGiven , matchDetails.team2); 
            }
            else{
                matchDetails.match.setBatsman(matchDetails.batsman1,matchDetails.b1Runs,matchDetails.b1Balls,matchDetails.team2);    
                matchDetails.match.setBatsman(matchDetails.batsman2,matchDetails.b2Runs,matchDetails.b2Balls,matchDetails.team2); 
                matchDetails.match.setBowler(matchDetails.bowler,matchDetails.overs, matchDetails.wickets, matchDetails.runsGiven , matchDetails.team1);
            }

            break;
        }

        event = "";
        if (matchDetails.overUp(matchDetails.ballsBowled)){
            cout<<endl<<BOLD<<BG_GREEN<<"OVER UP !!"<<RESET<<endl<<endl;
            matchDetails.overs++;
            matchDetails.oversThrown++;
            matchDetails.changeBowler();
            event = "OVER UP";
            matchDetails.runsScoredOnThisBall = 1;
            cout<<endl<<BOLD<<BG_GREEN<<"BOWLER CHANGED !!"<<RESET<<endl<<endl;
        }

        // Taking User Input for Scoring
        if (event != "OVER UP"){
            event = input(matchDetails);
        }
       
// // break is Just for trial
// break;
    }

    if (inning == "(INNING : 1)"){
        string n;
        matchDetails.target = matchDetails.runsScored + 1;
        cout<<endl<<endl<<BRIGHT_WHITE<<BOLD<<"INNINGS BREAK !!"<<RESET<<endl<<endl;
        matchDetails.displayingRawScoreboard = true;
        while(1){
            cout<<"PRESS 1 to INITIALIZE INNINGS 2 : ";
            cin>>n;
            if (n == "1"){
                cout<<endl<<endl<<BRIGHT_GREEN<<BOLD<<"INITIALIZING INNINGS 2 !!"<<RESET<<endl<<endl;
                cin.ignore();
                matchDetails.initializingSecondInnings();
                break;
            }
        }
        
    }

    if (inning == "(INNING : 2)" && battingTeamWon == false){
        if(matchDetails.bowlingTeamPlayers == matchDetails.t1players){
            cout<<endl<<BOLD<<BG_GREEN<<matchDetails.team1<<" won by "<< ((matchDetails.target - 1) -  matchDetails.runsScored) << " runs !!"<<RESET<<endl;
            matchDetails.match.totalMatchesOnPlatformDetails(matchDetails.teams, matchDetails.team1);
        }
        else{
            cout<<endl<<BOLD<<BG_GREEN<<matchDetails.team2<<" won by "<< ((matchDetails.target - 1) -  matchDetails.runsScored) << " runs !!"<<RESET<<endl;
            matchDetails.match.totalMatchesOnPlatformDetails(matchDetails.teams, matchDetails.team2);
        }
    }
}

void enteringScoringArea(){

    BatsmanBowler matchDetails;
    cout<<endl<<endl<<BRIGHT_WHITE<<BOLD<<"THE MATCH BEGINS !!"<<RESET<<endl<<endl;
    scoreboard("(INNING : 1)",matchDetails);
    cout<<endl<<endl<<BRIGHT_WHITE<<BOLD<<"INNINGS 2 BEGINS !!"<<RESET<<endl<<endl;
    scoreboard("(INNING : 2)",matchDetails);
    cout<<endl<<endl<<BRIGHT_WHITE<<BOLD<<"MATCH ENDS !!"<<RESET<<endl<<endl;

}

// ye main fn hatadena
int main() {
    enteringScoringArea();
}

// jo number choice ke liye input le rahe ho use integer ki jagah string kar sakte hai - this file is done
// agar is file ko aur header files me separate kar sakte hi to kardena, like some general functions like toLowercase and toUpperCase