#pragma once

using namespace std;

class matchInfo{
    int matchNumber;
    string temp;

    public:
        void createMatchFiles(vector<string> teams, vector<string> t1players, vector<string> t2players, string tossWinner = "", string choice = "");
        void setBatsman(string name, int runs, int balls, string teamName);
        void setBowler(string name,int overs,int wickets,int runs,string teamName);
        vector<int> getBatsman(string name,string teamName);
        vector<int> getBowler(string name,string teamName);
        vector<int> getBatsmanForView(string name, string team, string matchNum);
        vector<int> getBowlerForView(string name, string team, string matchNum);
        void totalMatchesOnPlatformDetails(vector<string> teams, string matchWinner);
};
