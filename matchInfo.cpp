#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "headerFiles/matchInfo.hpp"

using namespace std;

void matchInfo::createMatchFiles(vector<string> teams, vector<string> t1players, vector<string> t2players, string tossWinner, string choice){
           
    ifstream getTotalMatchesPlayedOnOurPlatform("mainDir/totalMatchesPlayedOnOurPlatform");
    getline(getTotalMatchesPlayedOnOurPlatform, temp);
    matchNumber = stoi(temp) + 1;
    getTotalMatchesPlayedOnOurPlatform.close();

    ofstream setTotalMatchesPlayedOnOurPlatform("mainDir/totalMatchesPlayedOnOurPlatform");
    setTotalMatchesPlayedOnOurPlatform << matchNumber;
    setTotalMatchesPlayedOnOurPlatform.close();

    ofstream team1BattingFile("mainDir/matchInfo/match"+to_string(matchNumber)+"."+teams[0]+".batting.txt");
    ofstream team1BowlingFile("mainDir/matchInfo/match"+to_string(matchNumber)+"."+teams[0]+".bowling.txt");
    ofstream team2BattingFile("mainDir/matchInfo/match"+to_string(matchNumber)+"."+teams[1]+".batting.txt");
    ofstream team2BowlingFile("mainDir/matchInfo/match"+to_string(matchNumber)+"."+teams[1]+".bowling.txt");

    for (int i = 0; i < t1players.size(); i++){
        team1BattingFile<<t1players[i]<<"_"<<0<<"."<<0<<"\n";
        team1BowlingFile<<t1players[i]<<"_"<<0<<"."<<0<<"/"<<0<<"\n";
    }
    for (int i = 0; i < t2players.size(); i++){
        team2BattingFile<<t2players[i]<<"_"<<0<<"."<<0<<"\n";
        team2BowlingFile<<t2players[i]<<"_"<<0<<"."<<0<<"/"<<0<<"\n";
    }

    team1BattingFile.close();
    team1BowlingFile.close();
    team2BattingFile.close();
    team2BowlingFile.close();

}

void matchInfo::setBatsman(string name, int runs, int balls, string teamName){
    ifstream readTeamFile("mainDir/matchInfo/match"+to_string(matchNumber)+"."+teamName+".batting.txt");
    vector<string> lines;
    string line;

    while (getline(readTeamFile, line)) {
        lines.push_back(line);
    }

    readTeamFile.close();

    for(int i = 0;i<lines.size();i++){
        int underscorePosition = lines[i].find('_');
        string batsman = lines[i].substr(0,underscorePosition);
        if (batsman == name){
            // int dotPosition = lines[i].find('.');
            // int oldRuns = stoi(lines[i].substr(underscorePosition+1,dotPosition));
            int updatedRuns = runs;

            // int oldBalls = stoi(lines[i].substr(dotPosition+1,lines[i].length()));
            int updatedBalls = balls;

            string updatedLine = batsman + "_" + to_string(updatedRuns) + "." + to_string(updatedBalls);
            lines[i] = updatedLine;
            break;
        }
    }

    ofstream updateTeamFile("mainDir/matchInfo/match"+to_string(matchNumber)+"."+teamName+".batting.txt");
    for(int i = 0;i<lines.size();i++){
        updateTeamFile<<lines[i]<<"\n";
    }
    updateTeamFile.close();
}

void matchInfo::setBowler(string name,int overs,int wickets,int runs,string teamName){
    ifstream readTeamFile("mainDir/matchInfo/match"+to_string(matchNumber)+"."+teamName+".bowling.txt");
    vector<string> lines;
    string line;

    while (getline(readTeamFile, line)) {
        lines.push_back(line);
    }

    readTeamFile.close();

    for(int i = 0;i<lines.size();i++){
        int underscorePosition = lines[i].find('_');
        string bowler = lines[i].substr(0,underscorePosition);
        if (bowler == name){
            // int dotPosition = lines[i].find('.');
            // int oldOvers = stoi(lines[i].substr(underscorePosition+1,dotPosition));
            int updatedOvers = overs;

            // int slashPosition = lines[i].find('/');
            // int oldWickets = stoi(lines[i].substr(dotPosition+1,slashPosition));
            int updatedWickets = wickets;

            // int oldRuns = stoi(lines[i].substr(slashPosition+1,lines[i].length()));
            int updatedRuns = runs;

            string updatedLine = bowler + "_" + to_string(updatedOvers) + "." + to_string(updatedWickets) + "/" + to_string(updatedRuns);
            lines[i] = updatedLine;
            break;
        }
    }

    ofstream updateTeamFile("mainDir/matchInfo/match"+to_string(matchNumber)+"."+teamName+".bowling.txt");
    for(int i = 0;i<lines.size();i++){
        updateTeamFile<<lines[i]<<"\n";
    }
    updateTeamFile.close();
}

vector<int> matchInfo::getBatsman(string name,string teamName){
    ifstream readTeamFile("mainDir/matchInfo/match"+to_string(matchNumber)+"."+teamName+".batting.txt");
    vector<int> batsmanDetails;
    string line;

    while (getline(readTeamFile, line)) {
        int underscorePosition = line.find('_');
        string batsman = line.substr(0,underscorePosition);
        if (batsman == name){
            int dotPosition = line.find('.');
            int runs = stoi(line.substr(underscorePosition+1,dotPosition));
            batsmanDetails.push_back(runs);

            int balls = stoi(line.substr(dotPosition+1,line.length()));
            batsmanDetails.push_back(balls);
            
            readTeamFile.close();
            return batsmanDetails;
        }
    }
}

vector<int> matchInfo::getBowler(string name,string teamName){
    ifstream readTeamFile("mainDir/matchInfo/match"+to_string(matchNumber)+"."+teamName+".bowling.txt");
    vector<int> bowlerDetails;
    string line;

    while (getline(readTeamFile, line)) {
        int underscorePosition = line.find('_');
        string bowler = line.substr(0,underscorePosition);
        if (bowler == name){
            int dotPosition = line.find('.');
            int overs = stoi(line.substr(underscorePosition+1,dotPosition));
            bowlerDetails.push_back(overs);

            int slashPosition = line.find('/');
            int wickets = stoi(line.substr(dotPosition+1,slashPosition));
            bowlerDetails.push_back(wickets);

            int runs = stoi(line.substr(slashPosition+1,line.length()));
            bowlerDetails.push_back(runs);
            
            readTeamFile.close();
            return bowlerDetails;
        }
    }
}

void matchInfo::totalMatchesOnPlatformDetails(vector<string> teams, string matchWinner){
    ofstream file("mainDir/totalMatchesOnPlatformDetails.txt", ios::app);
    string line = "match" + to_string(matchNumber) + ":" + teams[0] + "&" + teams[1] + "_" + matchWinner;
    file << line << "\n";
    file.close();
}