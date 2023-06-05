#include <iostream>
#include <vector>

using namespace std;

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
private:
    struct Info
    {
        string fullName;
        string email;
        string phoneNumber;
        string username;
        string password;
        string typeAccount;
        bool isDisable;
        int changePassword;
    };

    vector<Info> list;
    bool isLogin;
    Info info;

public:
    Account();
    void addToList(Info info);
    void removeToList(string username);
    void setIsLogin(bool status);
    bool getIsLogin();
    void setInfo(Info info);
    Info getInfo();
    void setList(vector<Info> list);
    vector<Info> getList();
    bool checkInfo(string username);
    void readFileAccount();
    void writeFileAccount();
    void printList();
    void printInfo();
    int checkInfo(string username, string password);
    int changePassword(string oldPassword, string newPassword, string reNewPassword);
    int forgotPassword(string username, int type);
};

#endif