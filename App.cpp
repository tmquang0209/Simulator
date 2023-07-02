#include <iostream>
#include <cstring>
#include <windows.h>
#include <unistd.h>
#include <conio.h> // Include the conio.h header for _getch() function
#include "Account.h"
#include "Account.cpp"

using namespace std;

string checkName;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Account account;
int width, height;

void gotoxy(int x, int y);
void drawBox(int x, int y, int width, int height);
void home();
void login();
void changePassword();
void forgotPassword();
void forgotPage();
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
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
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

void home()
{
    system("cls");
    cout << "Menu" << endl;
}

void login()
{
    // Tạo một cửa sổ con để hiển thị giao diện đăng nhập
    int loginWinHeight = 8;
    int loginWinWidth = 40;
    int loginWinY = (height - loginWinHeight) / 2;
    int loginWinX = (width - loginWinWidth) / 2;

    drawBox(loginWinX, loginWinY, loginWinWidth, loginWinHeight);

    gotoxy(loginWinX + 2, loginWinY + 2);
    cout << "\tLogin";

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

    // Bật lại hiển thị ký tự trên màn hình
    SetConsoleMode(handle, mode);

    // Xóa cửa sổ đăng nhập
    system("cls");
    if (username == NULL || password == NULL)
    {
        cout << "Fill in information: " << endl;
    }
    else
    {
        int msg = account.checkInfo(username, password);

        if (msg == -1)
            cout << "Username Not Found!" << endl;
        else if (msg == -2)
            cout << "Incorrect Password!" << endl;
        else if (msg == -3)
        {
            cout << "You need to change password." << endl;
            sleep(3);
            system("cls");
            changePassword();
        }
        else if (msg == -4)
            cout << "Your account has been ban." << endl;
        else if (msg == 1)
        {
            cout << "Login success." << endl;
            sleep(2);
            home();
        }
        else
            cout << "Unknown Error." << endl;
    }
}

void changePassword()
{
    // Tạo một cửa sổ con để hiển thị giao diện đăng nhập
    int changePasswordWinHeight = 10;
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
    cout << "Renew Password : ";

    char oldPassword[20];
    char newPassword[20];
    char reNewPassword[20];

    gotoxy(changePasswordWinX + 25, changePasswordWinY + 4);
    cin >> oldPassword;

    gotoxy(changePasswordWinX + 25, changePasswordWinY + 5);
    cin >> newPassword;

    gotoxy(changePasswordWinX + 25, changePasswordWinY + 6);
    cin >> reNewPassword;

    int msg = account.changePassword(oldPassword, newPassword, reNewPassword);
    gotoxy(changePasswordWinX + 2, changePasswordWinY + 3);
    if (msg != 1)
    {
        system("cls");
        if (msg == -1)
            cout << "Old password is incorrect, Check again!" << endl;
        else if (msg == -2)
            cout << "New password aren't same with the new one." << endl;
        else if (msg == -3)
            cout << "Password has to be at least 8 letter." << endl;
        else if (msg == -4)
            cout << "Password have at least 1 number and 1 special letter." << endl;
        changePassword();
    }
    else
    {
        system("cls");
        cout << "Change password success!" << endl;
        sleep(2);
        home();
    }
}

void accountInformation()
{
    system("cls");

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
        previousName = "AccountInfo";
        updateAccount();
        break;
    case 2:
        previousName = "AccountInfo";
        changePassword();
        break;
    case 3:
        back();
        break;
    default:
        break;
    }
}
/*
void updateAccount()
{
}
*/
void forgotPage()
{
    int forgotPageWinHeight = 10;
    int forgotPageWinWidth = 50;
    int forgotPageWinY = (height - forgotPageWinHeight) / 2;
    int forgotPageWinx = (width - forgotPageWinWidth) / 2;

    drawBox(forgotPageWinx, forgotPageWinY, forgotPageWinWidth, forgotPageWinHeight);

    gotoxy(forgotPageWinx + 2, forgotPageWinY + 2);
    cout << "\t\tForgot Password";

    gotoxy(forgotPageWinx + 2, forgotPageWinY + 4);
    cout << "Email/PhoneNumber: ";

    gotoxy(forgotPageWinx + 2, forgotPageWinY + 5);
    cout << "Username: ";

    char emailPhoneNum[30];
    char username[20];
    gotoxy(forgotPageWinx + 25, forgotPageWinY + 4);
    cin >> emailPhoneNum;

    gotoxy(forgotPageWinx + 25, forgotPageWinY + 5);
    cin >> username;
    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected
    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(forgotPageWinx + 10, forgotPageWinY + 8);
        if (selectedOption == 1)
            cout << "[ Submit ]";
        else
            cout << "  Submit  ";

        gotoxy(forgotPageWinx + 10, forgotPageWinY + 9);
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
        int msg = account.forgotPassword(emailPhoneNum, username);
        gotoxy(forgotPageWinx + 2, forgotPageWinY + 3);
        if (msg != 1)
        {
            system("cls");
            if (msg == -1)
            {
                cout << "Email or phone number is incorrect, please check again!" << endl;
            }
            else if (msg == -2)
            {
                cout << "Username not found, please check again!" << endl;
            }
        }
        else
        {
            system("cls");
            cout << "Verify and Change your password" << endl;
            sleep(2);
            system("cls");
            forgotPassword();
        }
    }
}
void forgotPassword()
{
    int forgotPageWinHeight = 10;
    int forgotPageWinWidth = 50;
    int forgotPageWinY = (height - forgotPageWinHeight) / 2;
    int forgotPageWinx = (width - forgotPageWinWidth) / 2;

    drawBox(forgotPageWinx, forgotPageWinY, forgotPageWinWidth, forgotPageWinHeight);

    gotoxy(forgotPageWinx + 2, forgotPageWinY + 2);
    cout << "\t\tVerify and change";

    gotoxy(forgotPageWinx + 5, forgotPageWinY + 4);
    cout << "Enter Code: ";

    gotoxy(forgotPageWinx + 5, forgotPageWinY + 5);
    cout << "New Password: ";

    gotoxy(forgotPageWinx + 5, forgotPageWinY + 6);
    cout << "Renew Password : ";

    char nCode[20];
    char newPassword[20];
    char reNewPassword[20];

    gotoxy(forgotPageWinx + 25, forgotPageWinY + 4);
    cin >> nCode;

    gotoxy(forgotPageWinx + 25, forgotPageWinY + 5);
    cin >> newPassword;

    gotoxy(forgotPageWinx + 25, forgotPageWinY + 6);
    cin >> reNewPassword;

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(forgotPageWinx + 10, forgotPageWinY + 8);
        if (selectedOption == 1)
            cout << "[ Submit ]";
        else
            cout << "  Submit  ";

        gotoxy(forgotPageWinx + 10, forgotPageWinY + 9);
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

        int msg = account.forgotPassword(nCode, newPassword, reNewPassword);
        gotoxy(forgotPageWinx + 2, forgotPageWinY + 3);
        if (msg != 1)
        {
            system("cls");
            if (msg == -1)
                cout << "Your verify code is incorrect, please check again!" << endl;
            else if (msg == -2)
                cout << "New password aren't same with the new one." << endl;
            else if (msg == -3)
                cout << "Password has to be at least 8 letter." << endl;
            else if (msg == -4)
                cout << "Password have at least 1 number and 1 special letter." << endl;
            forgotPage();
        }
        else
        {
            system("cls");
            cout << "Change password success!" << endl;
            sleep(2);
            login();
        }
    }
}

void activityLog()
{
    system("cls");
    previousPage.push_back("ActivityLog");

    gotoxy(forgotPageWinx + 5, forgotPageWinY + 6);
    cout << "Renew Password : ";

    char nCode[20];
    char newPassword[20];
    char reNewPassword[20];

    gotoxy(forgotPageWinx + 25, forgotPageWinY + 4);
    cin >> nCode;

    gotoxy(forgotPageWinx + 25, forgotPageWinY + 5);
    cin >> newPassword;

    gotoxy(forgotPageWinx + 25, forgotPageWinY + 6);
    cin >> reNewPassword;

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(forgotPageWinx + 10, forgotPageWinY + 8);
        if (selectedOption == 1)
            cout << "[ Submit ]";
        else
            cout << "  Submit  ";

        gotoxy(forgotPageWinx + 10, forgotPageWinY + 9);
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

        int msg = account.forgotPassword(nCode, newPassword, reNewPassword);
        gotoxy(forgotPageWinx + 2, forgotPageWinY + 3);
        if (msg != 1)
        {
            system("cls");
            if (msg == -1)
                cout << "Your verify code is incorrect, please check again!" << endl;
            else if (msg == -2)
                cout << "New password aren't same with the new one." << endl;
            else if (msg == -3)
                cout << "Password has to be at least 8 letter." << endl;
            else if (msg == -4)
                cout << "Password have at least 1 number and 1 special letter." << endl;
            forgotPage();
        }
        else
        {
            system("cls");
            cout << "Change password success!" << endl;
            sleep(2);
            system("cls");
            login();
        }
    }
}
