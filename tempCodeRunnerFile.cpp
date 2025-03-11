void authenticate(string name, string pass, Path directory) {
    // This function checks for existing user
    string fname = NULL, fpass = NULL;
    ifstream l_file = directory.logIn();
    // Add error handling if required
    char ch;
    bool matchFound = false;
    while(1) {
        while((l_file.get(ch)) && (ch != '\0')) {
            fname.push_back(ch);
        }
        l_file.seekg(ios::cur + 1);
        while(l_file.get(ch) && (ch != '\n')) {
            fpass.push_back(ch);
        }

        if((name == fname) && (pass == fpass)) {
            cout << endl << "User Found, Welcome";
            matchFound = true;
            break;
        }
    }

    if(matchFound == false) {
        cout << endl << "You are not an existing user, signup first";
        exit(0);
    }
}