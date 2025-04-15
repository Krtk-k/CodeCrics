#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Path {
    private:
    string mainDirPath;

    public:
    Path() {
        mainDirPath = "mainDir/loginInfo";
    }
    ofstream signUp() {
        ofstream signup(mainDirPath + "/userLogin.txt", ios::app);
        // Add a check here to find if the file is created successfully
        // Use error messages ie: error handling
        return (signup);
    }
    ifstream logIn() {
        ifstream login(mainDirPath + "/userLogin.txt");
        // Add a check here to find if the file is created successfully
        // Use error messages ie: error handling
        return (login);
    }f

    ~Path() {}
};

string line1 = "\t\tWelcome to CodeCrics", line2 = "\t\t1->Login, 2->Signup";
string inpErr = "Invalid input";

void authenticate(string name, string pass, Path directory){
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
            }else{
                cout << endl << "Incorrect Password !!";
            }
            break;
        }
    }
    if(matchFound == false){
        cout << endl << "You are not an existing user !! SignUp first !!";
    }
    file.close();
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

int main() {
    cout << endl << line1;
    Path mdp;
    
    cout << endl << line2 << endl;
    int userIn;
    cout<<"Enter Number : ";
    cin >> userIn;
    cin.ignore(); 

    string username, pwd;
    ofstream file;
    switch(userIn) {
        case 1: // Login
            cout << endl << "Username : ";
            getline(cin,username);
            cout << endl << "Password : ";
            getline(cin,pwd);
            authenticate(username, pwd, mdp);
            break;

        case 2: // Signup
            cout << endl << "Username : ";
            getline(cin,username);
            cout << endl << "Password : ";
            getline(cin,pwd);
            writeUser(username, pwd, mdp);
            break;

        default:
            cout << inpErr;
    }

    return 0;
}
