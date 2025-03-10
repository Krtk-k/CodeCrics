#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Path {
    private:
    string mainDirPath;

    public:
    Path() {
        cout << endl << "Enter the main directory path: ";
        cin >> mainDirPath;
    }
    ofstream signUp() {
        ofstream signup(mainDirPath + "/userLog.txt", ios::app);
        return (signup);
    }
    ifstream logIn() {
        ifstream login(mainDirPath + "/userLog.txt");
        return (login);
    }

    ~Path() {}
};

string line1 = "\t\tWelcome to CodeCrics", line2 = "\t\t1->Login, 2->Signup";
string inpErr = "Invalid input";

int main() {
    cout << endl << line1;
    Path mdp;
    
    cout << endl << line2 << "\t";
    int userIn;
    cin >> userIn;

    cin.ignore(); 
    string usernameL, pwdL, usernameS, pwdS;
    switch(userIn) {
        case 1: // Login
            cout << endl << "Username: ";
            cin.ignore(); 
            getline(cin, usernameL);
            cout << endl << "Password: ";
            getline(cin, pwdL);
            break;

        case 2: // Signup
            cout << endl << "Username: ";
            cin.ignore(); 
            getline(cin, usernameS);
            cout << endl << "Password: ";
            getline(cin, pwdS);
            break;

        default:
            cout << inpErr;
    }

    return 0;
}
