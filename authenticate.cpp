#include "headerFiles/authenticate.hpp"
#include <iostream>

using namespace std;

Path::Path() {
    mainDirPath = "mainDir/loginInfo";
}
ofstream Path::signUp() {
    ofstream signup(mainDirPath + "/userSign.txt", ios::app);
    // Add a check here to find if the file is created successfully
    // Use error messages ie: error handling
    return (signup);
}
ifstream Path::logIn() {
    ifstream login(mainDirPath + "/userSign.txt");
    // Add a check here to find if the file is created successfully
    // Use error messages ie: error handling
    return (login);
}

// ofstream Path::userUpdate() {
//     ofstream file(mainDirPath + "/userSign.txt", ios::app);
//     // Add exception handling
//     return (file);
// }

// ifstream Path::readUser() {
//     ifstream file(mainDirPath + "/userSign.txt");
//     // Add exception handling
//     return (file);
// }

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
                cout << endl << "LOGIN SUCCESSFUL !! Welcome";
                file.close();
                return true;
            }else{
                cout << endl << "Incorrect Password !!";
                return false;
            }
            break;
        }
    }
    if(matchFound == false){
        cout << endl << "You are not an existing user !! SignUp first !!";
    }
    file.close();
    return false;
}

void writeUser(string name, string pass, Path directory) {
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
            cout<<endl<<"Username Already Exists !! Try a different one !!"<<endl;
            break;
        }
    }
    if(matchFound == false){
        file_write.seekp(0, ios::end);
        file_write << name << '\0' << pass << '\n';
        cout << endl << "ACCOUNT CREATED SUCCESSFULLY !!";
    }
    file_write.close();
    file_read.close();
}

string line1 = "\t\tWelcome to CodeCrics", line2 = "\t\t1->Login, 2->Signup";
string inpErr = "Invalid input";
