#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
using namespace std;

struct Info {
    string fullName;
    string email;
    string phoneNumber;
    string username;
    string password;
    string typeAccount;
    bool isDisable;
    int changePassword;
};

vector<Info> readUserFile(const string& fileName) {
    vector<Info> infos;

    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string fullName, email, phoneNumber, username, password, typeAccount;
            bool isDisable;
            int changePassword;

            getline(ss, fullName, '|');
            getline(ss, email, '|');
            getline(ss, phoneNumber, '|');
            getline(ss, username, '|');
            getline(ss, password, '|');
            getline(ss, typeAccount, '|');
            ss >> isDisable;
            ss.ignore();
            ss >> changePassword;

            Info info;
            info.fullName = fullName;
            info.email = email;
            info.phoneNumber = phoneNumber;
            info.username = username;
            info.password = password;
            info.typeAccount = typeAccount;
            info.isDisable = isDisable;
            info.changePassword = changePassword;

            infos.push_back(info);
        }
        file.close();
    } else {
        cout << "Unable to open file: " << fileName << endl;
    }

    return infos;
}
int width, height;
vector<string> previousPage;
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void drawBox(int x, int y, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                gotoxy(x + j, y + i);
                cout << "*";
            }
        }
    }
}
Info* getUser(const string& username, const vector<Info>& infos) {
    for (const auto& info : infos) {
        if (info.username == username) {
            return new Info(info);
        }
    }
    return nullptr;
}

void provideFileManagementPermissions(const Info& info) {
    system("cls");
    previousPage.push_back("provideFileManagementPermissions");

    int permissionsWinHeight = 13;
    int permissionsWinWidth = 50;
    int permissionsWinY = (height - permissionsWinHeight) / 2;
    int permissionsWinX = (width - permissionsWinWidth) / 2;

    drawBox(permissionsWinX, permissionsWinY, permissionsWinWidth, permissionsWinHeight);

    gotoxy(permissionsWinX + 2, permissionsWinY + 2);
    cout << "\t\tFile Management Options";

    
    int currentLine = permissionsWinY + 4;
    cout << "1. Create a file" << endl;
    cout << "2. Read a file" << endl;
    cout << "3. Edit a file" << endl;
    if (info.typeAccount == "administrator") {
        cout << "4. Rename a file" << endl;
        cout << "5. Delete a file" << endl;
    }
    cout << "0. Exit" << endl;
}


void CreateFile() {
    system("cls");
    previousPage.push_back("CreateFile");

    int createFileWinHeight = 15;
    int createFileWinWidth = 60;
    int createFileWinY = (height - createFileWinHeight) / 2;
    int createFileWinX = (width - createFileWinWidth) / 2;

    drawBox(createFileWinX, createFileWinY, createFileWinWidth, createFileWinHeight);

    gotoxy(createFileWinX + 2, createFileWinY + 2);
    cout << "\t\tCreate File";

    string fileName;
    gotoxy(createFileWinX + 2, createFileWinY + 4);
    cout << "Enter file name: ";
    cin >> fileName;

    ofstream file(fileName);
    if (file.is_open()) {
        gotoxy(createFileWinX + 2, createFileWinY + 6);
        cout << "Enter file content (type 'q' to finish):";

        cin.ignore();
        string line;
        int currentLine = createFileWinY + 8;
        while (true) {
            gotoxy(createFileWinX + 2, currentLine);
            getline(cin, line);
            if (line == "q") {
                break;
            }
            file << line << endl;
            currentLine++;
        }

        cout << "File created successfully.\n";
        file.close();
    } else {
        cout << "Unable to create file.\n";
    }
}


void ReadFile() {
    system("cls");
    previousPage.push_back("ReadFile");

    int readFileWinHeight = 15;
    int readFileWinWidth = 60;
    int readFileWinY = (height - readFileWinHeight) / 2;
    int readFileWinX = (width - readFileWinWidth) / 2;

    drawBox(readFileWinX, readFileWinY, readFileWinWidth, readFileWinHeight);

    gotoxy(readFileWinX + 2, readFileWinY + 2);
    cout << "\t\tRead File";

    string fileName;
    gotoxy(readFileWinX + 2, readFileWinY + 4);
    cout << "Enter file name: ";
    cin >> fileName;

    ifstream file(fileName);
    if (file.is_open()) {
        gotoxy(readFileWinX + 2, readFileWinY + 6);
        cout << "File content:";

        string line;
        int currentLine = readFileWinY + 8;
        while (getline(file, line)) {
            gotoxy(readFileWinX + 2, currentLine);
            cout << line << endl;
            currentLine++;
        }
        file.close();
    } else {
        cout << "Unable to open file.\n";
    }
}


void EditFile() {
    system("cls");
    previousPage.push_back("EditFile");

    int editFileWinHeight = 15;
    int editFileWinWidth = 60;
    int editFileWinY = (height - editFileWinHeight) / 2;
    int editFileWinX = (width - editFileWinWidth) / 2;

    drawBox(editFileWinX, editFileWinY, editFileWinWidth, editFileWinHeight);

    gotoxy(editFileWinX + 2, editFileWinY + 2);
    cout << "\t\tEdit File";

    string fileName;
    gotoxy(editFileWinX + 2, editFileWinY + 4);
    cout << "Enter file name: ";
    cin >> fileName;
    cin.ignore();

    fstream file(fileName, ios::in | ios::out);
    if (file.is_open()) {
        gotoxy(editFileWinX + 2, editFileWinY + 6);
        cout << "Current content of the file:";

        gotoxy(editFileWinX + 2, editFileWinY + 8);
        cout << file.rdbuf();

        file.seekp(0, ios::end);

        gotoxy(editFileWinX + 2, editFileWinY + 10);
        cout << "Enter new content (Enter '.' on a new line to finish):";

        string line;
        int currentLine = editFileWinY + 12;
        while (getline(cin, line) && line != ".") {
            file << line << endl;
            currentLine++;
        }

        cout << "File edited successfully.\n";
        file.close();
    } else {
        cout << "Unable to open file.\n";
    }
}


void RenameFile() {
    system("cls");
    previousPage.push_back("RenameFile");

    int renameFileWinHeight = 13;
    int renameFileWinWidth = 60;
    int renameFileWinY = (height - renameFileWinHeight) / 2;
    int renameFileWinX = (width - renameFileWinWidth) / 2;

    drawBox(renameFileWinX, renameFileWinY, renameFileWinWidth, renameFileWinHeight);

    gotoxy(renameFileWinX + 2, renameFileWinY + 2);
    cout << "\t\tRename File";

    string oldFileName, newFileName;
    gotoxy(renameFileWinX + 2, renameFileWinY + 4);
    cout << "Enter the file name to be renamed: ";
    cin >> oldFileName;

    gotoxy(renameFileWinX + 2, renameFileWinY + 6);
    cout << "Enter the new file name: ";
    cin >> newFileName;

    if (rename(oldFileName.c_str(), newFileName.c_str()) == 0) {
        cout << "File renamed successfully.\n";
    } else {
        cout << "Unable to rename file.\n";
    }
}


void DeleteFile() {
    system("cls");
    previousPage.push_back("DeleteFile");

    int deleteFileWinHeight = 11;
    int deleteFileWinWidth = 60;
    int deleteFileWinY = (height - deleteFileWinHeight) / 2;
    int deleteFileWinX = (width - deleteFileWinWidth) / 2;

    drawBox(deleteFileWinX, deleteFileWinY, deleteFileWinWidth, deleteFileWinHeight);

    gotoxy(deleteFileWinX + 2, deleteFileWinY + 2);
    cout << "\t\tDelete File";

    string fileName;
    gotoxy(deleteFileWinX + 2, deleteFileWinY + 4);
    cout << "Enter the file name to be deleted: ";
    cin >> fileName;

    if (remove(fileName.c_str()) == 0) {
        cout << "File deleted successfully.\n";
    } else {
        cout << "Unable to delete file.\n";
    }
}


void executeFileManagementOption(const Info& info, int option) {
    while (true) {
        system("cls");

        int fileManagementWinHeight = 17;
        int fileManagementWinWidth = 60;
        int fileManagementWinY = (height - fileManagementWinHeight) / 2;
        int fileManagementWinX = (width - fileManagementWinWidth) / 2;

        drawBox(fileManagementWinX, fileManagementWinY, fileManagementWinWidth, fileManagementWinHeight);

        gotoxy(fileManagementWinX + 2, fileManagementWinY + 2);
        cout << "\t\tFile Management";

        gotoxy(fileManagementWinX + 2, fileManagementWinY + 4);
        cout << "Logged in as: " << info.username;
        gotoxy(fileManagementWinX + 2, fileManagementWinY + 5);
        cout << "Account type: " << info.typeAccount;

        provideFileManagementPermissions(info);

        gotoxy(fileManagementWinX + 2, fileManagementWinY + 10);
        cout << "Enter your choice: ";
        cin >> option;

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
                if (info.typeAccount == "administrator") {
                    RenameFile();
                }
                break;
            case 5:
                if (info.typeAccount == "administrator") {
                    DeleteFile();
                }
                break;
            case 0:
                return;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
}

int main() {
    string userFileName = "userinfo.txt";
    string loggedInUsername;

    cout << "Welcome to the file management system.\n";

    vector<Info> infos = readUserFile(userFileName);

    cout << "Enter your username: ";
    cin >> loggedInUsername;

    Info* loggedInInfo = getUser(loggedInUsername, infos);

    if (loggedInInfo == nullptr) {
        cout << "Invalid username.\n";
        return 0;
    }

    string password;
    cout << "Enter your password: ";
    cin >> password;

    if (loggedInInfo->password != password) {
        cout << "Invalid password.\n";
        return 0;
    }

    cout << "Login successful.\n";
    cout << "Welcome, " << loggedInInfo->fullName << "!\n";

    provideFileManagementPermissions(*loggedInInfo);

    int option;
    cout << "Enter your choice: ";
    cin >> option;

    executeFileManagementOption(*loggedInInfo, option);

    return 0;
}
