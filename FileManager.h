#include <iostream>
#include <string>
#include <vector>
#include "Account.h"
#include "Struct.h"

using namespace std;

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

class FileManager : Account
{
public:
    FileManager();
    bool checkPermission(string username, string typeCheck, Permission fileAccess);
    void getInfoFile(string dirName, string fileName, FileInfo &fileInfo, Permission &fileAccess);
    void writeInfoFile(string dirName, string fileName, FileInfo fileInfo, Permission fileAccess);
    void createFile(string dirName, string fileName);
    // void viewFile(string dirname, string targetFile, FileInfo filleInfo, Permission fileAccess);
    int moveFile(string currentDir, string targetDir, string fileName, FileInfo fileInfo, Permission fileAccess);
    int copyFile(string currentDir, string targetDir, string fileName, FileInfo fileInfo, Permission fileAccess);
    int renameFile(string dirName, string targetFile, string newFileName, FileInfo fileInfo, Permission fileAccess);
    int deleteFile(string dirname, string targetFile, FileInfo fileInfo, Permission fileAccess);
    int permissionsFile(string targetUser, string targetFile, vector<string> permission, FileInfo &fileInfo, Permission &fileAccess); // assign permissions to other users
    void setUserInfo(string &username);
};

#endif