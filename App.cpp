#include <iostream>
#include <cstring>
#include <windows.h>
#include <unistd.h>
#include "Account.h"
#include "Account.cpp"

using namespace std;
Account account;
int width, height;

void gotoxy(int x, int y);
void drawBox(int x, int y, int width, int height);
void home(int width, int height);
void login(int width, int height);
void changePassword(int width, int height);

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
    login(width, height);
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

void home(int width, int height)
{
    system("cls");
    cout << "Đây là trang chủ." << endl;
}

void login(int width, int height)
{
    // Tạo một cửa sổ con để hiển thị giao diện đăng nhập
    int loginWinHeight = 8;
    int loginWinWidth = 40;
    int loginWinY = (height - loginWinHeight) / 2;
    int loginWinX = (width - loginWinWidth) / 2;

    drawBox(loginWinX, loginWinY, loginWinWidth, loginWinHeight);

    gotoxy(loginWinX + 2, loginWinY + 2);
    cout << "\tĐăng nhập";

    gotoxy(loginWinX + 2, loginWinY + 4);
    cout << "Tên đăng nhập: ";

    gotoxy(loginWinX + 2, loginWinY + 5);
    cout << "Mật khẩu: ";

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

    // Xóa cửa sổ đăng nhập
    system("cls");
    if (username == NULL || password == NULL)
    {
        cout << "Nhập đủ thông tin" << endl;
    }
    else
    {
        int msg = account.checkInfo(username, password);

        if (msg == -1)
            cout << "Không tìm thấy tài khoản." << endl;
        else if (msg == -2)
            cout << "Mật khẩu không chính xác." << endl;
        else if (msg == -3)
        {
            cout << "Bạn cần thay đổi mật khẩu." << endl;
            account.printList();
            sleep(3);
            system("cls");
            changePassword(width, height);
        }
        else if (msg == -4)
            cout << "Tài khoản của bạn bị khóa." << endl;
        else if (msg == 1)
        {
            cout << "Đăng nhập thành công." << endl;
            sleep(2);
            home(width, height);
        }
        else
            cout << "Lỗi không xác định." << endl;
    }
}

void changePassword(int width, int height)
{
    // Tạo một cửa sổ con để hiển thị giao diện đăng nhập
    int changePasswordWinHeight = 10;
    int changePasswordWinWidth = 50;
    int changePasswordWinY = (height - changePasswordWinHeight) / 2;
    int changePasswordWinX = (width - changePasswordWinWidth) / 2;

    drawBox(changePasswordWinX, changePasswordWinY, changePasswordWinWidth, changePasswordWinHeight);

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 2);
    cout << "\t\tĐổi mật khẩu";

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 4);
    cout << "Mật khẩu cũ: ";

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 5);
    cout << "Mật khẩu mới: ";

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 6);
    cout << "Nhập lại khẩu mới: ";

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
            cout << "Mật khẩu cũ không chính xác." << endl;
        else if (msg == -2)
            cout << "Mật khẩu nhập lại không chính xác." << endl;
        else if (msg == -3)
            cout << "Độ dài mật khẩu có ít nhất 8 ký tự." << endl;
        else if (msg == -4)
            cout << "Mật khẩu phải bao gồm ít nhất 1 số và 1 ký tự đặc biệt." << endl;
        changePassword(width, height);
    }
    else
    {
        system("cls");
        cout << "Đổi mật khẩu thành công" << endl;
        sleep(2);
        home(width, height);
    }
}