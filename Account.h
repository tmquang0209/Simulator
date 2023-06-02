#include <bits/stdc++.h>
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
    };
    vector<Info> list;

public:
    Account();
    void addToList(Info info);
    void removeToList(string username);
};
#endif