#include <iostream>
#include "headerFiles/textStyles.hpp"
#include "headerFiles/scoreboard.hpp"
#include <vector>
#include <algorithm>

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
            b1Balls = 0;
            b2Balls = 0;
            totalBalls = 6;
            ballsBowled = 0;
            overs = 0;
            wickets = 0;
            runsGiven = 0;

        }

        void strikeChange(int runs = 0, string event = ""){
            if (runs%2 == 0 && batsman1==onStrike){
                // if (event!="Leg Byes"||event!="Byes"||event!="")
                b1Runs += runs;
                
                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<< " : "  <<b1Runs<<" runs in "<<b1Balls<<" balls"<<RESET<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<"\t  "<<runningEnd<<" : " <<b2Runs<<" runs in "<<b2Balls<<" balls"<<"\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<"\tRUNS : "<<runsGiven<<endl;

                b1Balls++;

            }else if (runs%2 == 0 && batsman2==onStrike){

                b2Runs += runs;

                cout<<"\t  "<<runningEnd<<" : " <<b1Runs<<" runs in "<<b1Balls<<" balls"<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<< " : " <<b2Runs<<" runs in "<<b2Balls<<" balls"<<RESET<<"\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<"\tRUNS : "<<runsGiven<<endl;

                b2Balls++;

            }else if (runs%2 != 0 && batsman1==onStrike){

                b1Runs += runs;

                string temp = onStrike;
                onStrike = runningEnd;
                runningEnd = temp;

                cout<<"\t  "<<runningEnd<<" : "<<b1Runs<<" runs in "<<b1Balls<<" balls"<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<<" : " <<b2Runs<<" runs in "<<b2Balls<<" balls"<<RESET<<"\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<"\tRUNS : "<<runsGiven<<endl;

                b1Balls++;

            }else if (runs%2 != 0 && batsman2==onStrike){

                b2Runs += runs;
                
                string temp = onStrike;
                onStrike = runningEnd;
                runningEnd = temp;

                cout<<BOLD<<BRIGHT_GREEN<<"\t* "<<onStrike<< " : " <<b1Runs<<" runs in "<<b1Balls<<" balls"<<RESET<<"\t\t\t\t\t\t"<<GOLD<<bowler<<" : "<<ballsBowled<<"/"<<totalBalls<<RESET<<endl;
                cout<<"\t  "<<runningEnd<<" : " <<b2Runs<<" runs in "<<b2Balls<<" balls"<<"\t\t\t\t"<<"OVERS : "<<overs<<"\tWICKETS : "<<wickets<<"\tRUNS : "<<runsGiven<<endl;

                b2Balls++;

            }else{
                cout<<"ERROR in strikeChange() !!";
            }
        }

        /// Function for changing batsman and bowler separately
        
        // Friend Function
        friend string input(BatsmanBowler&);
        friend void scoreboard(string , BatsmanBowler&);

        ~BatsmanBowler(){}
};

// INITIALIZING STATIC VARIABLES OF BatsmanBowler CLASS
int BatsmanBowler::oversThrown = 0;
int BatsmanBowler::runsScored = 0;
int BatsmanBowler::wicketsDown = 0;

//Function to check whether an over has been ended or not
void overUp(){}

//Input Function for Taking User Input
string input(BatsmanBowler& matchDetails){
    int event;
    cout<<"SELECT EVENT"<<endl<<endl;
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
    cout<<"PRESS 11 : Retired Out"<<endl<<endl;
    cout<<"Enter Number : ";
    cin>>event;

    if (event == 1){
        matchDetails.runsScoredOnThisBall = 0;
        matchDetails.ballsBowled ++;
        return "Dot Ball";
    }
    else if(event == 2){
        matchDetails.runsScoredOnThisBall = 4;
        matchDetails.ballsBowled ++;
        matchDetails.runsGiven += 4;
        matchDetails.runsScored += 4;
        return "Four";
    }
    else if(event == 3){
        matchDetails.runsScoredOnThisBall = 6;
        matchDetails.ballsBowled ++;
        matchDetails.runsGiven += 6;
        matchDetails.runsScored += 6;
        return "Six";
    }
    else if(event == 4){
        cout<<"\nEnter Runs Taken : ";
        cin>>matchDetails.runsScoredOnThisBall;
        matchDetails.ballsBowled ++;
        matchDetails.runsGiven += matchDetails.runsScoredOnThisBall;
        matchDetails.runsScored += matchDetails.runsScoredOnThisBall;
        return "Regular Runs";
    }
    else if(event == 5){
        cout<<"\nEnter Runs Taken : ";
        cin>>matchDetails.runsScoredOnThisBall;
        matchDetails.ballsBowled ++;
        matchDetails.runsGiven += matchDetails.runsScoredOnThisBall;
        matchDetails.runsScored += matchDetails.runsScoredOnThisBall;
        return "Leg Byes";
    }
    else if(event == 6){
        cout<<"\nEnter Runs Taken : ";
        cin>>matchDetails.runsScoredOnThisBall;
        matchDetails.ballsBowled ++;
        matchDetails.runsGiven += matchDetails.runsScoredOnThisBall;
        matchDetails.runsScored += matchDetails.runsScoredOnThisBall;
        return "Byes";
    }
    else if(event == 7){
        cout<<"\nEnter Runs Taken : ";
        cin>>matchDetails.runsScoredOnThisBall;
        matchDetails.runsGiven += (matchDetails.runsScoredOnThisBall+1);
        matchDetails.runsScored += (matchDetails.runsScoredOnThisBall+1);
        return "No Ball";
    }
    else if(event == 8){
        cout<<"\nEnter Runs Taken : ";
        cin>>matchDetails.runsScoredOnThisBall;
        matchDetails.runsGiven += (matchDetails.runsScoredOnThisBall+1);
        matchDetails.runsScored += (matchDetails.runsScoredOnThisBall+1);
        return "Wide Ball";
    }
    else if(event == 9){
        string n;
        cout<<"SELECT TYPE OF DISMISSAL"<<endl<<endl;
        cout<<"PRESS 1 : Bowled"<<endl;
        cout<<"PRESS 2 : Caught"<<endl;
        cout<<"PRESS 3 : LBW"<<endl;
        cout<<"PRESS 4 : Run Out"<<endl;
        cout<<"PRESS 5 : Stumped"<<endl;
        cout<<"PRESS 6 : Hit Wicket"<<endl<<endl;
        cout<<"Enter Number : ";
        cin>>n;

        if(n == "1"){
            matchDetails.ballsBowled++;
            matchDetails.wickets++;
            matchDetails.wicketsDown++;
        }
        else if(n == "2"){
            matchDetails.ballsBowled++;
            matchDetails.wickets++;
            matchDetails.wicketsDown++;
        }
        else if(n == "3"){
            matchDetails.ballsBowled++;
            matchDetails.wickets++;
            matchDetails.wicketsDown++;
        }
        else if(n == "4"){

        }

        // name of new batsman
        return "Out";
    }
    else if(event == 10){
        int retiredHurt;
        string newBatsman;

        cout<<"\nWho is Retired Hurt ?\n\nPRESS 1 for Batsman at Striking End\nPRESS 2 for Batsman at Running End\n\n";
        cout<<"Enter Number : ";
        cin>>retiredHurt;
        cout<<"Enter Name of New Batsman : ";
        cin>>newBatsman;
        //include check whether new batsman is in team or not

        if (retiredHurt == 1){
            if (matchDetails.batsman1 == matchDetails.onStrike){
                matchDetails.batsman1 = newBatsman;
                matchDetails.onStrike = newBatsman;
            }
            else{
                matchDetails.batsman2 = newBatsman;
                matchDetails.onStrike = newBatsman;
            }
        }
        else if(retiredHurt == 2){
            if (matchDetails.batsman1 == matchDetails.runningEnd){
                matchDetails.batsman1 = newBatsman;
                matchDetails.runningEnd = newBatsman;
            }
            else{
                matchDetails.batsman2 = newBatsman;
                matchDetails.runningEnd = newBatsman;
            }
        }
        else{
            cout<<"\nINVALID INPUT !!\n\n";
        }

        return "Retired Hurt";
    }
    else if(event == 11){
        int retiredOut;
        string newBatsman;
        
        cout<<"\nWho is Retired Out ?\n\nPRESS 1 for Batsman at Striking End\nPRESS 2 for Batsman at Running End\n\n";
        cout<<"Enter Number : ";
        cin>>retiredOut;
        cout<<"Enter Name of New Batsman : ";
        cin>>newBatsman;
        //include check whether new batsman is in team or not

        if (retiredOut == 1){
            if (matchDetails.batsman1 == matchDetails.onStrike){
                matchDetails.batsman1 = newBatsman;
                matchDetails.onStrike = newBatsman;
            }
            else{
                matchDetails.batsman2 = newBatsman;
                matchDetails.onStrike = newBatsman;
            }
            matchDetails.wicketsDown++;
        }
        else if(retiredOut == 2){
            if (matchDetails.batsman1 == matchDetails.runningEnd){
                matchDetails.batsman1 = newBatsman;
                matchDetails.runningEnd = newBatsman;
            }
            else{
                matchDetails.batsman2 = newBatsman;
                matchDetails.runningEnd = newBatsman;
            }
            matchDetails.wicketsDown++;
        }
        else{
            cout<<"\nINVALID INPUT !!\n\n";
        }

        return "Retired Out";
    }
    else{
        cout<<"\nINVALID INPUT !!\n\n";
    }
}

void scoreboard(string inning, BatsmanBowler& matchDetails){

    int totalTeamPlayers;
    string event = "";
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
        
        cout << endl << BOLD << UNDERLINE << BRIGHT_WHITE << "\t\t\t\t SCOREBOARD " << RESET <<endl;
        cout << endl << "\t\t                "<< ORANGE << inning <<RESET<<endl<<endl<<endl;
        cout << "\t\t\t "<< BLUE << matchDetails.tossWinner<<" CHOSE TO "<<matchDetails.choice<<" FIRST" <<RESET<<endl<<endl<<endl<<endl;
        
        if (inning =="(INNING : 1)"){
            if (matchDetails.choice == "bat"){
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossWinner<<"\t\t\t\t\t\t"<<matchDetails.tossLoser<<RESET<<endl<<endl;
            }else{
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossLoser<<"\t\t\t\t\t\t"<<matchDetails.tossWinner<<RESET<<endl<<endl;
            }
        }else{
            if (matchDetails.choice == "bat"){
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossLoser<<"\t\t\t\t\t\t"<<matchDetails.tossWinner<<RESET<<endl<<endl;
            }else{
                cout<<"\t  "<<BOLD<<UNDERLINE<<BRIGHT_WHITE<<matchDetails.tossWinner<<"\t\t\t\t\t\t"<<matchDetails.tossLoser<<RESET<<endl<<endl;
            }
        }
        matchDetails.strikeChange(matchDetails.runsScoredOnThisBall,event);
        cout<<endl<<endl<<BOLD<<BRIGHT_WHITE<<"\t\t\t\t  RUNS : "<<matchDetails.runsScored<<endl<<endl;
        cout<<BLUE<<"\t\t\t WICKETS/TOTAL WICKETS : "<<matchDetails.wicketsDown<<"/"<<(totalTeamPlayers-1)<<endl<<endl;
        cout<<BRIGHT_WHITE<<"\t\t\t   OVERS/TOTAL OVERS : "<<matchDetails.oversThrown<<"/"<<matchDetails.totalOversToBePlayed<<RESET<<endl<<endl;

        if (inning == "(INNING : 2)"){
            cout << "\t\t\t         "<< BG_BRIGHT_YELLOW << "TARGET" <<" : "<<matchDetails.target<<RESET<<endl<<endl;
            if (matchDetails.runsScored >= matchDetails.target){
                break;
            }
        }

        // Taking User Input for Scoring
        event = input(matchDetails);
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
    scoreboard("(INNING : 1)",matchDetails);
    cout<<endl<<endl<<BRIGHT_WHITE<<BOLD<<"INNINGS BREAK !!"<<RESET<<endl<<endl;
    scoreboard("(INNING : 2)",matchDetails);
    cout<<endl<<endl<<BRIGHT_WHITE<<BOLD<<"MATCH ENDS !!"<<RESET<<endl<<endl;

}

int main() {
    enteringScoringArea();
}

// uske baad scoring kaise karni hai wo dekhna
// jo number choice ke liye input le rahe ho use integer ki jagah char ya string kar sakte hai
// loop lagana hai kaafi jagah, we can use go-to or while loop
// validity of players ka function add karna hai
