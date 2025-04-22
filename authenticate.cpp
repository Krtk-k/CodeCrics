#include "headerFiles/authenticate.hpp"
#include <iostream>
#include "headerFiles/textStyles.hpp"

using namespace std;

Path::Path() {
    mainDirPath = "mainDir/loginInfo";
}
ofstream Path::signUp() {
    ofstream signup(mainDirPath + "/userLogin.txt", ios::app);
    // Add a check here to find if the file is created successfully
    // Use error messages ie: error handling
    return (signup);
}
ifstream Path::logIn() {
    ifstream login(mainDirPath + "/userLogin.txt");
    // Add a check here to find if the file is created successfully
    // Use error messages ie: error handling
    return (login);
}

ofstream Path::author() {
    ofstream a(mainDirPath + "/authors", ios::app);
    return (a);
}

ifstream Path::authorc() {
    ifstream a(mainDirPath + "/authors");
    return (a);
}

ifstream Path::viewMatchChoices() {
    ifstream a("mainDir/totalMatchesOnPlatformDetails.txt");
    return a;
}

ifstream Path::battingFile(string matchNum, string team) {
    ifstream a("mainDir/matchInfo"+matchNum + "." + team + "." + "batting.txt");
    return a;
}

ifstream Path::ballingFile(string matchNum, string team) {
    ifstream a("mainDir/matchInfo"+matchNum + "." + team + "." + "bowling.txt");
    return a;
}

bool authenticate(string name, string pass, Path directory){
    ifstream file = directory.logIn();
    string line;
    bool matchFound = false;
    while(getline(file,line)){
        int pos = line.find('\0');
        string username = line.substr(0,pos);
        if (username == name){
            matchFound = true;
            string password = line.substr(pos+1,line.length());
            if (password == pass){
                cout << endl << GREEN << "LOGIN SUCCESSFUL !! Welcome" << RESET;
                file.close();
                return true;
            }else{
                cout << endl << RED << "Incorrect Password !!" << RESET;
                file.close();
                return false;
            }
            break;
        }
    }
    if(matchFound == false){
        cout << endl << RED << "You are not an existing user !! SignUp first !!" << RESET;
    }
    file.close();
    return false;
}

bool writeUser(string name, string pass, Path directory) {
    ofstream file_write = directory.signUp();
    ifstream file_read = directory.logIn();
    // Add error handling if required

    string line;
    bool matchFound = false;
    while(getline(file_read,line)){
        int pos = line.find('\0');
        string username = line.substr(0,pos);
        if (username == name){
            matchFound = true;
            cout<<endl<< RED << "Username Already Exists !! Try a different one !!"<<endl << RESET;
            return false;
            break;
            // Add exception handling here
        }
    }
    if(matchFound == false){
        file_write.seekp(0, ios::end);
        file_write << name << '\0' << pass << '\n';
        cout << GREEN << endl << "ACCOUNT CREATED SUCCESSFULLY !!" << RESET;
    }
    file_write.close();
    file_read.close();
    return  true;
}

void writeAuthor(string name, string pass, Path directory) {
    ofstream file_write = directory.author();
    file_write.seekp(0, ios::end);
    file_write << name << '\0' << pass << '\n';
}

bool checkAuthor(string name, string pass, Path directory) {
    ifstream file = directory.authorc();
    string line;
    bool matchFound = false;
    while(getline(file,line)){
        int pos = line.find('\0');
        string username = line.substr(0,pos);
        if (username == name){
            matchFound = true;
            string password = line.substr(pos+1,line.length());
            if (password == pass){
                file.close();
                return true;
            }
            else{
                file.close();
                return false;
            }
            break;
        }
    }
    if(matchFound == false){
        file.close();
        return false;
    }
}

Path::~Path(){}

string line1 = "\t\tWelcome to CodeCrics", line2 = "\t\t1->Login, 2->Signup";
string inpErr = "Invalid input";
