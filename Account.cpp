#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <string.h>
#include <math.h>
#include <chrono>
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

bool Account::checkVerify(const vector<string> &dataCode, const string &searchString)
{
    for (const string &data : dataCode)
    {
        if (data == searchString)
        {
            return true; // String found in the vector
        }
    }
    return false; // String not found in the vector
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
    cout << "Current time: " << buffer << endl;

    fstream fout;
    fout.open("./log/" + username + ".txt", ios::app);

    if (fout.is_open())
    {
        fout << buffer << ": " << actName << endl;
        fout.close();
    }
    else
    {
        cout << "Can't open file.";
    }
}

/**
 * @brief Forgot Page
 * *Message error:
 * 1: Success
 * -1: Your verify code isn't correct
 * -2: New password and renew password aren't the same
 * -3: The length of the new password less than 8
 * -4: New password without numbers or special characters
 * @param nCode
 * @param newPassword
 * @param reNewPassword
 * @return int
 */
int Account::forgotPassword(string nCode, string newPassword, string reNewPassword)
{
    vector<string> dataCode;
    string verifyCode;
    // sending verify code
    fstream writeFile;
    char c;
    int r;
    srand(time(NULL));
    writeFile.open("dataCode.txt", ios::out);
    for (int i = 0; i < 8; i++)
    {
        r = rand() % 26;
        c = 'A' + r;
        writeFile << c;
    }
    writeFile << endl;
    writeFile.close();
    // read from file
    fstream readFile;
    readFile.open("dataCode.txt", ios::in);
    if (!readFile)
    {
        cout << "Failed to open the file." << endl;
        return 0;
    }
    while (getline(readFile, verifyCode))
    {
        dataCode.push_back(verifyCode);
    }
    cout << "input: " << endl;
    getline(cin, nCode);
    bool check = checkVerify(dataCode, nCode);
    if (check)
    {
        cout << "Verify success!" << endl;
    }
    else
        return -1;
    readFile.close();
    if (newPassword != reNewPassword)
    {
        return -2;
    }
    if (newPassword.length() < 8)
    {
        return -3;
    }
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

/**
 * @brief Forgot Password
 * *Message error:
 * 1: Success
 * -1: Your email/phone number do not found!
 * -2: Your username do not found!
 * @param type
 * @param username
 * @return int
 */
int Account::forgotPassword(string type, string username)
{
    Info check;
    for (int i = 0; i < list.size(); i++)
    {
        if ((list[i].email == type || list[i].phoneNumber == type) && list[i].username == username)
        {
            check = list[i];
            break;
        }
        else if (check.email != type)
            return -1;
        else if (check.username != username)
            return -2;
    }
    return 1;
}