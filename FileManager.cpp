#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct User {
    string username;
    string password;
    string gmail;
    string contact;
    string role;
};

vector<User> readUserFile(const string& fileName) {
    vector<User> users;

    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, password, gmail, contact, loginname, role;
            getline(ss, username, '|');
            getline(ss, password, '|');
            getline(ss, gmail, '|');
            getline(ss, contact, '|');
            getline(ss, loginname, '|');
            getline(ss, role, '|');

            User user;
            user.username = username;
            user.password = password;
            user.gmail = gmail;
            user.contact = contact;
            user.role = role;

            users.push_back(user);
        }
        file.close();
    } else {
        cout << "Unable to open file: " << fileName << endl;
    }

    return users;
}


User* getUser(const string& username, const vector<User>& users) {
    for (const auto& user : users) {
        if (user.username == username) {
            return const_cast<User*>(&user);
        }
    }
    return nullptr;
}

void createUserFile(const string& fileName) {
    ofstream file(fileName);
    if (file.is_open()) {
        cout << "Enter user details (type 'q' to finish):\n";
        string line;
        while (true) {
            getline(cin, line);
            if (line == "q") {
                break;
            }
            file << line << endl;
        }
        cout << "User file created successfully.\n";
        file.close();
    } else {
        cout << "Unable to create user file.\n";
    }
}

void provideFileManagementPermissions(const User& user) {
    if (user.role == "administrator") {
        cout << "File management options: " << endl;
        cout << "1. Create a file" << endl;
        cout << "2. Read a file" << endl;
        cout << "3. Edit a file" << endl;
        cout << "4. Rename a file" << endl;
        cout << "5. Delete a file" << endl;
        cout << "6. Exit" << endl;  
    } else if (user.role == "user") {
        cout << "File management options: " << endl;
        cout << "1. Create a file" << endl;
        cout << "2. Read a file" << endl;
        cout << "3. Edit a file" << endl;
        cout << "4. Exit" << endl;  
    }
}


void CreateFile() {
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;

    ofstream file(fileName);
    if (file.is_open()) {
        cout << "Enter file content (type 'q' to finish):\n";
        string line;
        cin.ignore();
        while (true) {
            getline(cin, line);
            if (line == "q") {
                break;
            }
            file << line << endl;
        }

        cout << "File created successfully.\n";
        file.close();
    } else {
        cout << "Unable to create file.\n";
    }
}

void ReadFile() {
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;

    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        cout << "File content:\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file.\n";
    }
}

void EditFile() {
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    cin.ignore();

    fstream file(fileName, ios::in | ios::out);
    if (file.is_open()) {
        cout << "Current content of the file:\n";
        cout << file.rdbuf();

        file.seekp(0, ios::end);

        cout << "Enter new content (Enter '.' on a new line to finish):\n";
        string line;
        while (getline(cin, line) && line != ".") {
            file << line << endl;
        }

        cout << "File edited successfully.\n";
        file.close();
    } else {
        cout << "Unable to open file.\n";
    }
}

void RenameFile() {
    string oldFileName, newFileName;
    cout << "Enter the file name to be renamed: ";
    cin >> oldFileName;
    cout << "Enter the new file name: ";
    cin >> newFileName;

    if (rename(oldFileName.c_str(), newFileName.c_str()) == 0) {
        cout << "File renamed successfully.\n";
    } else {
        cout << "Unable to rename file.\n";
    }
}

void DeleteFile() {
    string fileName;
    cout << "Enter the file name to be deleted: ";
    cin >> fileName;

    if (remove(fileName.c_str()) == 0) {
        cout << "File deleted successfully.\n";
    } else {
        cout << "Unable to delete file.\n";
    }
}

void executeFileManagementOption(const User& user, int option) {
    while (true) {
        switch (option) {
            case 1:
                CreateFile();
                break;
            case 2:
                ReadFile();
                break;
            case 3:
                EditFile();
                break;
            case 4:
                if (user.role == "administrator") {
                    RenameFile();
                } else {
                    cout << "You do not have permission to perform this action.\n";
                }
                break;
            case 5:
                if (user.role == "administrator") {
                    DeleteFile();
                } else {
                    cout << "You do not have permission to perform this action.\n";
                }
                break;
            case 6:  
                cout << "Exiting the program.\n";
                return;
            default:
                cout << "Invalid option.\n";
                break;
        }
        
        cout << endl;
        provideFileManagementPermissions(user);
        
        cout << "Enter your choice: ";
        cin >> option;
    }
}


int main() {
    string userFileName = "userinfo.txt";
    string loggedInUsername;

    cout << "Welcome to the file management system.\n";

    vector<User> users = readUserFile(userFileName);

    cout << "Enter your username: ";
    cin >> loggedInUsername;

    User* loggedInUser = getUser(loggedInUsername, users);

    if (loggedInUser == nullptr) {
        cout << "Invalid username.\n";
        return 0;
    }

    string password;
    cout << "Enter your password: ";
    cin >> password;

    if (loggedInUser->password != password) {
        cout << "Invalid password.\n";
        return 0;
    }

    cout << "Login successful.\n";
    cout << "Welcome, " << loggedInUser->username << "!\n";

    provideFileManagementPermissions(*loggedInUser);

    int option;
    cout << "Enter your choice: ";
    cin >> option;

    executeFileManagementOption(*loggedInUser, option);

    return 0;
}
