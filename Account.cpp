#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

Account::Account()
{
    isLogin = false;
    readFileAccount();
}

void Account::addToList(Info info)
{
    list.push_back(info);
}

void Account::removeToList(string username)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].username == username)
        {
            list.erase(list.begin() + i);
            break;
        }
    }
}

void Account::setIsLogin(bool status)
{
    this->isLogin = status;
}

bool Account::getIsLogin()
{
    return isLogin;
}

void Account::setInfo(Info info)
{
    this->info = info;
}

Account::Info Account::getInfo()
{
    return info;
}

void Account::setList(vector<Info> list)
{
    this->list = list;
}

vector<Account::Info> Account::getList()
{
    return this->list;
}

bool Account::checkInfo(string username)
{
    return true;
}

void Account::readFileAccount()
{
    ifstream fin("./data/info.txt");
    if (!fin)
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    string line;
    while (getline(fin, line))
    {
        istringstream iss(line);
        Info info;
        string disable;
        string changePassword;

        getline(iss, info.fullName, '|');
        getline(iss, info.email, '|');
        getline(iss, info.phoneNumber, '|');
        getline(iss, info.username, '|');
        getline(iss, info.password, '|');
        getline(iss, info.typeAccount, '|');
        getline(iss, disable, '|');
        getline(iss, changePassword, '|');

        info.isDisable = (disable == "1") ? true : false;
        info.changePassword = stoi(changePassword);
        list.push_back(info);
    }

    fin.close();
}

void Account::writeFileAccount()
{
    fstream fOut;
    fOut.open("./data/info.txt", ios::out);
    for (int i = 0; i < list.size(); i++)
    {
        fOut << list[i].fullName << "|" << list[i].email << "|" << list[i].phoneNumber << "|"
             << list[i].username << "|" << list[i].password << "|"
             << list[i].typeAccount << "|"
             << (list[i].isDisable ? "1" : "0") << "|" << list[i].changePassword << "|" << endl;
    }
    fOut.close();
}

void Account::printList()
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << list[i].username << list[i].password << endl;
    }
}

void Account::printInfo()
{
    cout << info.username << info.password << endl;
}

/**
 * @brief check account information
 * * Message Error
 * 1: Correct
 * -1: Not found
 * -2: Username or password incorrect
 * -3: You need to change password
 * -4: Account is disabled
 * @param username
 * @param password
 * @return int
 */
int Account::checkInfo(string username, string password)
{
    Info check;
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].username == username)
        {
            check = list[i];
            break;
        }
    }

    if (check.fullName == "")
        return -1;
    else if (check.password != password)
        return -2;
    else if (check.changePassword)
    {
        setInfo(check);
        setIsLogin(true);
        return -3;
    }
    else if (check.isDisable)
        return -4;
    else
    {
        setInfo(check);
        setIsLogin(true);

        return 1;
    }
}

/**
 * @brief update account info by username
 *
 * @param username
 * @param fullName
 * @param email
 * @param phoneNumber
 */
void Account::updateInfo(string username, string fullName, string email, string phoneNumber)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (info.username == username)
        {
            info.fullName = fullName;
            info.email = email;
            info.phoneNumber = phoneNumber;
            if (list[i].username == username)
            {
                list[i] = info;
            }
            writeActLog(info.username, " update information.");
            break;
        }
        else if (list[i].username == username)
        {
            list[i].fullName = fullName;
            list[i].email = email;
            list[i].phoneNumber = phoneNumber;
            writeActLog(info.username, "update information of " + username);
            break;
        }
    }
    writeFileAccount();
}

/**
 * @brief Change password
 * *Message error:
 * 1: Success
 * -1: Old password incorrect
 * -2: New password and renew password aren't the same
 * -3: The length of the new password less than 8
 * -4: New password without numbers or special characters
 * @param oldPassword
 * @param newPassword
 * @param reNewPassword
 * @return int
 */
int Account::changePassword(string oldPassword, string newPassword, string reNewPassword)
{
    if (oldPassword != info.password)
        return -1;
    if (newPassword != reNewPassword)
        return -2;
    if (newPassword.length() < 8)
        return -3;

    bool numberDigit = false;
    bool specialDigit = false;
    for (char c : newPassword)
    {
        if (isdigit(c))
            numberDigit = true;

        if (ispunct(c))
            specialDigit = true;

        if (numberDigit && specialDigit)
            break;
    }

    if (!numberDigit && !specialDigit)
        return -4;

    info.password = newPassword;
    info.changePassword = 0;
    // update to list
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].username == info.username)
        {
            list[i].password = info.password;
            list[i].changePassword = info.changePassword;
            break;
        }
    }
    // update to file
    writeFileAccount();
    return 1;
}

void Account::writeActLog(string username, string actName)
{
    // Get the current time using the system clock
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    // Convert the time to a string with the desired format
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%H:%M:%S %d-%m-%Y", localtime(&currentTime));

    // Print the formatted time
    // cout << "Current time: " << buffer << endl;

    fstream fout;
    fout.open("./log/" + username + ".txt", ios::app);

    if (fout.is_open())
    {
        fout << buffer << "|" << actName << endl;
        fout.close();
    }
    else
    {
        cout << "Can't open file.";
    }
}

void Account::activityLog(vector<pair<string, string>> &data, string username)
{
    username = (username == "") ? info.username : username;
    fstream f;
    f.open("./log/" + username + ".txt", ios::in);

    string line;
    int index = 0;
    while (getline(f, line))
    {
        istringstream iss(line);

        string time, event;
        getline(iss, time, '|');
        getline(iss, event, '|');

        data.emplace_back(time, event);
        index++;
    }
}