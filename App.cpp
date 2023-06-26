#include <iostream>
#include <cstring>
#include <windows.h>
#include <unistd.h>
#include <conio.h> // Include the conio.h header for _getch() function
#include "Account.h"
#include "Account.cpp"

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Account account;
int width, height;
vector<string> previousPage;

void gotoxy(int x, int y);
void drawBox(int x, int y, int width, int height);
void back();
void home();
void login();
void changePassword();
void accountInformation();
void updateAccount(string username);
void forgotPassword();
void activityLog();
void activityLog(string username);

int main()
{
    // Ẩn hiện con trỏ nhấp nháy
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 50;
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

    // Lấy kích thước của cửa sổ console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // Thiết lập kích thước cho vùng cửa sổ cuộn
    SMALL_RECT scrollRect;
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = width - 1;
    scrollRect.Bottom = height - 1;

    // Thiết lập kích thước bộ đệm cho vùng cửa sổ cuộn
    COORD scrollBufferSize;
    scrollBufferSize.X = width;
    scrollBufferSize.Y = height;

    // Thiết lập vùng cửa sổ cuộn
    SetConsoleWindowInfo(consoleHandle, TRUE, &scrollRect);
    SetConsoleScreenBufferSize(consoleHandle, scrollBufferSize);
    login();
    return 0;
}

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

/**
 * @brief back to previous page
 * Home
 * AccountInfo
 * ChangePassword
 * UpdateAccount
 * ActivityLog
 */
void back()
{
    string previousName = previousPage[previousPage.size() - 1];
    if (previousName == "Home")
    {
        home();
    }

    if (previousName == "AccountInfo")
    {
        accountInformation();
    }
}

void home()
{
    system("cls");
    previousPage.push_back("Home");

    // Tạo một cửa sổ con để hiển thị giao diện đăng nhập
    int homeWinHeight = 10;
    int homeWinWidth = 40;
    int homeWinY = (height - homeWinHeight) / 2;
    int homeWinX = (width - homeWinWidth) / 2;

    drawBox(homeWinX, homeWinY, homeWinWidth, homeWinHeight);
    gotoxy(homeWinX + 2, homeWinY + 2);
    cout << "\t\tMenu";
    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(homeWinX + 2, homeWinY + 4);
        if (selectedOption == 1)
            cout << "-> 1. Account info.";
        else
            cout << "   1. Account info.";

        gotoxy(homeWinX + 2, homeWinY + 5);
        if (selectedOption == 2)
            cout << "-> 2. Account list.";
        else
            cout << "   2. Account list.";

        gotoxy(homeWinX + 2, homeWinY + 6);
        if (selectedOption == 3)
            cout << "-> 3. Activity logs.";
        else
            cout << "   3. Activity logs.";

        gotoxy(homeWinX + 2, homeWinY + 7);
        if (selectedOption == 4)
            cout << "-> 4. Logout";
        else
            cout << "   4. Logout";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 4)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        accountInformation();
        break;
    case 2:
        // Handle Account list option
        break;
    case 3:
        // Handle Activity logs option
        activityLog();
        break;
    case 4:
        // Handle Logout option
        break;
    default:
        break;
    }
}

void login()
{
    system("cls");

    // Tạo một cửa sổ con để hiển thị giao diện đăng nhập
    int loginWinHeight = 10;
    int loginWinWidth = 40;
    int loginWinY = (height - loginWinHeight) / 2;
    int loginWinX = (width - loginWinWidth) / 2;

    drawBox(loginWinX, loginWinY, loginWinWidth, loginWinHeight);

    gotoxy(loginWinX + 2, loginWinY + 2);
    cout << "\tLogin";

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(loginWinX + 10, loginWinY + 7);
        if (selectedOption == 1)
            cout << "[ Submit ]";
        else
            cout << "  Submit  ";

        gotoxy(loginWinX + 10, loginWinY + 8);
        if (selectedOption == 2)
            cout << "[ Forgot password? ]";
        else
            cout << "  Forgot password?  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 3)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    gotoxy(loginWinX + 2, loginWinY + 4);
    cout << "Username: ";

    gotoxy(loginWinX + 2, loginWinY + 5);
    cout << "Password: ";

    char username[20];
    char password[20];

    gotoxy(loginWinX + 18, loginWinY + 4);
    cin >> username;

    gotoxy(loginWinX + 18, loginWinY + 5);
    // Vô hiệu hóa hiển thị ký tự trên màn hình
    DWORD mode;
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(handle, &mode);
    SetConsoleMode(handle, mode & ~ENABLE_ECHO_INPUT);
    cin >> password;
    // Bật lại hiển thị ký tự trên màn hình
    SetConsoleMode(handle, mode);

    gotoxy(loginWinX + 2, loginWinY + 3);
    SetConsoleTextAttribute(hConsole, 14);

    int msg = account.checkInfo(username, password);
    switch (selectedOption)
    {
    case 1:
        if (username == NULL || password == NULL)
        {
            cout << "Fill full the information." << endl;
        }
        else
        {
            if (msg == -1)
                cout << "Username Not Found!" << endl;
            else if (msg == -2)
                cout << "Incorrect Password!" << endl;
            else if (msg == -3)
            {
                cout << "You need to change password." << endl;
                sleep(3);
                changePassword();
            }
            else if (msg == -4)
                cout << "Your account has been ban." << endl;
            else if (msg == 1)
            {
                cout << "Login success." << endl;
                account.writeActLog(username, "login success.");

                SetConsoleTextAttribute(hConsole, 15);
                sleep(2);
                home();
            }
            else
                cout << "Unknown Error." << endl;
        }
        break;
    case 2:
        forgotPassword();
        break;
    default:
        break;
    }
}

void changePassword()
{
    system("cls");
    previousPage.push_back("ChangePassword");

    // Tạo một cửa sổ con để hiển thị giao diện đăng nhập
    int changePasswordWinHeight = 13;
    int changePasswordWinWidth = 50;
    int changePasswordWinY = (height - changePasswordWinHeight) / 2;
    int changePasswordWinX = (width - changePasswordWinWidth) / 2;

    drawBox(changePasswordWinX, changePasswordWinY, changePasswordWinWidth, changePasswordWinHeight);

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 2);
    cout << "\t\tChange Password";

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 4);
    cout << "Old Password: ";

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 5);
    cout << "New Password: ";

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 6);
    cout << "Renew Passwrod : ";

    char oldPassword[20];
    char newPassword[20];
    char reNewPassword[20];

    gotoxy(changePasswordWinX + 25, changePasswordWinY + 4);
    cin >> oldPassword;

    gotoxy(changePasswordWinX + 25, changePasswordWinY + 5);
    cin >> newPassword;

    gotoxy(changePasswordWinX + 25, changePasswordWinY + 6);
    cin >> reNewPassword;

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(changePasswordWinX + 10, changePasswordWinY + 8);
        if (selectedOption == 1)
            cout << "[ Submit ]";
        else
            cout << "  Submit  ";

        gotoxy(changePasswordWinX + 10, changePasswordWinY + 9);
        if (selectedOption == 2)
            cout << "[ Back ]";
        else
            cout << "  Back  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 4)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    int msg = account.changePassword(oldPassword, newPassword, reNewPassword);
    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        gotoxy(changePasswordWinX + 2, changePasswordWinY + 3);
        if (msg != 1)
        {
            gotoxy(changePasswordWinX + 2, changePasswordWinY + 3);
            if (msg == -1)
                cout << "Old password is incorrect, Check again!" << endl;
            else if (msg == -2)
                cout << "New password aren't same with the new one." << endl;
            else if (msg == -3)
                cout << "Password has to be at least 8 letter." << endl;
            else if (msg == -4)
                cout << "Password have at least 1 number and 1 special letter." << endl;

            sleep(3);
            changePassword();
        }
        else
        {
            system("cls");
            cout << "Change password success!" << endl;
            sleep(2);
            home();
        }
        break;
    case 2:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void accountInformation()
{
    system("cls");
    previousPage.push_back("AccountInfo");

    int accountInfoWinHeight = 15;
    int accountInfoWinWidth = 50;
    int accountInfoWinY = (height - accountInfoWinHeight) / 2;
    int accountInfoWinX = (width - accountInfoWinWidth) / 2;

    drawBox(accountInfoWinX, accountInfoWinY, accountInfoWinWidth, accountInfoWinHeight);

    gotoxy(accountInfoWinX + 2, accountInfoWinY + 2);
    cout << "\t\tAccount information";

    gotoxy(accountInfoWinX + 5, accountInfoWinY + 4);
    cout << "Fullname: ";
    gotoxy(accountInfoWinX + 5, accountInfoWinY + 5);
    cout << "Email: ";
    gotoxy(accountInfoWinX + 5, accountInfoWinY + 6);
    cout << "Phone number: ";
    gotoxy(accountInfoWinX + 5, accountInfoWinY + 7);
    cout << "Username: ";
    gotoxy(accountInfoWinX + 5, accountInfoWinY + 8);
    cout << "Type account: ";

    gotoxy(accountInfoWinX + 20, accountInfoWinY + 4);
    cout << account.getInfo().fullName;

    gotoxy(accountInfoWinX + 20, accountInfoWinY + 5);
    cout << account.getInfo().email;

    gotoxy(accountInfoWinX + 20, accountInfoWinY + 6);
    cout << account.getInfo().phoneNumber;

    gotoxy(accountInfoWinX + 20, accountInfoWinY + 7);
    cout << account.getInfo().username;

    gotoxy(accountInfoWinX + 20, accountInfoWinY + 8);
    cout << account.getInfo().typeAccount;

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(accountInfoWinX + 10, accountInfoWinY + 11);
        if (selectedOption == 1)
            cout << "[ Update information ]";
        else
            cout << "  Update information  ";

        gotoxy(accountInfoWinX + 10, accountInfoWinY + 12);
        if (selectedOption == 2)
            cout << "[ Change password ]";
        else
            cout << "  Change password  ";

        gotoxy(accountInfoWinX + 10, accountInfoWinY + 13);
        if (selectedOption == 3)
            cout << "[ Back ]";
        else
            cout << "  Back  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 4)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        updateAccount(account.getInfo().username);
        break;
    case 2:
        changePassword();
        break;
    case 3:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void updateAccount(string username)
{
    system("cls");
    previousPage.push_back("UpdateAccount");

    int accountWinHeight = 15;
    int accountWinWidth = 50;
    int accountWinY = (height - accountWinHeight) / 2;
    int accountWinX = (width - accountWinWidth) / 2;

    drawBox(accountWinX, accountWinY, accountWinWidth, accountWinHeight);

    gotoxy(accountWinX + 2, accountWinY + 2);
    cout << "\t\tChange information";

    // Info
    string fullName = account.getInfo().fullName;
    string email = account.getInfo().email;
    string phoneNumber = account.getInfo().phoneNumber;

    gotoxy(accountWinX + 5, accountWinY + 4);
    cout << "Full name: ";
    cout << fullName;

    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!fullName.empty())
            {
                cout << "\b \b";
                fullName.pop_back();
            }
        }
        else
        {
            cout << ch;
            fullName += ch;
        }
    }

    gotoxy(accountWinX + 5, accountWinY + 5);
    cout << "Phone number: ";
    cout << phoneNumber;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!phoneNumber.empty())
            {
                cout << "\b \b";
                phoneNumber.pop_back();
            }
        }
        else
        {
            cout << ch;
            phoneNumber += ch;
        }
    }

    gotoxy(accountWinX + 5, accountWinY + 6);
    cout << "Email: ";
    cout << email;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!email.empty())
            {
                cout << "\b \b";
                email.pop_back();
            }
        }
        else
        {
            cout << ch;
            email += ch;
        }
    }

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(accountWinX + 10, accountWinY + 11);
        if (selectedOption == 1)
            cout << "[ Submit ]";
        else
            cout << "  Submit  ";

        gotoxy(accountWinX + 10, accountWinY + 12);
        if (selectedOption == 2)
            cout << "[ Cancel ]";
        else
            cout << "  Cancel  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 4)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        account.updateInfo(username, fullName, email, phoneNumber);
        cout << "Update success.";
        previousPage.pop_back();
        back();
        break;
    case 2:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void forgotPassword()
{
}

void activityLog()
{
    system("cls");
    previousPage.push_back("ActivityLog");

    vector<pair<string, string>> data;
    account.activityLog(data);

    int accountWinHeight = 10 + data.size();
    int accountWinWidth = 60;
    int accountWinY = (height - accountWinHeight) / 3;
    int accountWinX = (width - accountWinWidth) / 2;

    drawBox(accountWinX, accountWinY, accountWinWidth, accountWinHeight);

    gotoxy(accountWinX + 5, accountWinY + 2);
    cout << "\t\tActivity log";

    int i;
    for (i = 0; i < data.size(); i++)
    {
        gotoxy(accountWinX + 2, accountWinY + 4 + i);
        cout << data[i].first << ":\t" << data[i].second;
    }

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(accountWinX + 2, accountWinY + accountWinHeight - 5);
        if (selectedOption == 1)
            cout << "[ Back ]";
        else
            cout << "  Back  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        if (key == 13)
            optionSelected = true;
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void activityLog(string username)
{
}