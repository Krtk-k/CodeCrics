#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Path {
    private:
    string mainDirPath;

    public:
    Path() {
        mainDirPath = "mainDir/loginInfo";
    }
    ofstream signUp() {
        ofstream signup(mainDirPath + "/userSign.txt", ios::app);
        // Add a check here to find if the file is created successfully
        // Use error messages ie: error handling
        return (signup);
    }
    ifstream logIn() {
        ifstream login(mainDirPath + "/userSign.txt");
        // Add a check here to find if the file is created successfully
        // Use error messages ie: error handling
        return (login);
    }

    ofstream userUpdate() {
        ofstream file(mainDirPath + "/userSign.txt", ios::app);
        // Add exception handling
        return (file);
    }

    ifstream readUser() {
        ifstream file(mainDirPath + "/userSign.txt");
        // Add exception handling
        return (file);
    }

    ~Path() {}
};


Path user_path;

int findPersonIndex(string username, string pass, Path p);

class User {
    protected:
    string username;
    string password;
    bool is_author;
    int index;

    public:
    User(string username, string pass, bool is_author) {
        this->username = username;
        this->password = pass;
        this->is_author = is_author;
        this->index = findPersonIndex(username, pass, user_path);
    }

    void change_username(string name) {
        // Authenticate first
        // Add exception handling

        string line;
        ifstream r_file = user_path.readUser();
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
        // remove("mainDir/loginInfo/userSign.txt");
        // rename("mainDir/loginInfo/temp.txt", "mainDir/loginInfo/userSign.txt");
    }

    void change_password(string pass) {
        // Authenticate first
        // Add exception handling

        string line;
        ifstream r_file = user_path.readUser();
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
        // remove("mainDir/loginInfo/userSign.txt");
        // rename("mainDir/loginInfo/temp.txt", "mainDir/loginInfo/userSign.txt");
    }

    // Add more functions if needed
};

int findPersonIndex(string username, string password, Path p) {
    ifstream r_file = p.readUser();
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

int main() {
    User obj("kartik", "hello", true);

    obj.change_username("kavi");
    return 0;
}
