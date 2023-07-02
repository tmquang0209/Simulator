#include <iostream>
#include <vector>
#include <utility>

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
    bool checkVerify(const vector<string> &, const string &);
    void updateInfo(string username, string fullName, string email, string phoneNumber);
    void readFileAccount();
    void writeFileAccount();
    void printList();
    void printInfo();
    int checkInfo(string username, string password);
    int changePassword(string oldPassword, string newPassword, string reNewPassword);
    void writeActLog(string username, string actName);
    int forgotPassword(string type, string username);
    int forgotPassword(string nCode, string newPassword, string reNewPassword);
    void activityLog(vector<pair<string, string>> &data, string username = "");
};

#endif