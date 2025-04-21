#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "headerFiles/authenticate.hpp"
#include "headerFiles/classes.hpp"
#include "headerFiles/scorecard.hpp"

using namespace std;





int findPersonIndex(string username, string pass, Path p);

class User { // This should be an abstract class (no instances)
    protected:
    string username;
    string password;
    bool isAuthor;
    int index;

    public:
    User(string username, string pass, bool isAuthor) {
        this->username = username;
        this->password = pass;
        this->isAuthor = isAuthor;
        this->index = findPersonIndex(username, pass, user_path);
    }

    void change_username(string name) {
        // Authenticate first
        // Add exception handling

        string line;
        ifstream r_file = user_path.logIn();
        ofstream file("mainDir/loginInfo/temp.txt");
        for(int i = 1; i<index; i++) {
            getline(r_file, line);
            file << line << '\n';
        }
        file << name << '\0' << password << '\n';

        // r_file.seekg(name.length() + 2 + pass.length(), ios::cur);
        getline(r_file, line);

        while(getline(r_file, line)) {
            getline(r_file, line);
            file << line << '\n';
        }

        r_file.close();
        file.close();
        remove("mainDir/loginInfo/userSign.txt");
        rename("mainDir/loginInfo/temp.txt", "mainDir/loginInfo/userSign.txt");
    }

    void change_password(string pass) {
        // Authenticate first
        // Add exception handling

        string line;
        ifstream r_file = user_path.logIn();
        ofstream file("mainDir/loginInfo/temp.txt");
        for(int i = 1; i<index; i++) {
            getline(r_file, line);
            file << line << '\n';
        }
        file << username << '\0' << pass << '\n';
        getline(r_file, line);

        while(getline(r_file, line)) {
            getline(r_file, line);
            file << line << '\n';
        }

        r_file.close();
        file.close();
        remove("mainDir/loginInfo/userSign.txt");
        rename("mainDir/loginInfo/temp.txt", "mainDir/loginInfo/userSign.txt");
    }

    // Add more functions if needed
};

int findPersonIndex(string username, string password, Path p) {
    ifstream r_file = p.logIn();
    int index = 0;
    string line, name, pass;

    while(getline(r_file, line)) {
        int pos = line.find('\0');
        name = line.substr(0, pos);
        pass = line.substr(pos+1, line.length());
        index++;
        if((name == username) && (pass == password)) {
            break;
        }
    }
    r_file.close();
    return index;
}

class Viewer : public User {
    private:
    Match *match;

    public:
    Viewer(string username, string pass, bool isAuthor) : User(username, pass, isAuthor) {
        this->index = findPersonIndex(username, pass, user_path);
    }

    void show_batting() {

    }
    
    void show_bowling() {
        
    }
};

class Author : public Viewer {
    private:

    public:
    Author(string username, string pass, bool isAuthor) : Viewer(username, pass, isAuthor) {
        this->index = findPersonIndex(username, pass, user_path);
    }
};

// class Match{
//     private:
//     string name;
//     ifstream runPtr, batsMen, bowlers;
//     vector<vector<pair<int, int>>> viewVector;

//     public:
//     Match(string name) {
//         this->name = name;
//         // Three file pointers pointing to all the files of the match
//         runPtr.open("matches/" + name + "runs");
//         batsMen.open("matches/" + name + "batsMen");
//         bowlers.open("matches/" + name + "bowlers");
//     }
//     ifstream* returnRunPtr() {
//         return &runPtr;
//     }
//     ifstream* returnBatsMenPtr() {
//         return &batsMen;
//     }
//     ifstream* returnBowlersPtr() {
//         return &bowlers;
//     }

//     void ini_viewVector() {
        
//     }
// };


int main() {
    User obj("kartik", "hello", true);

    obj.change_username("kavi");
    return 0;
}
