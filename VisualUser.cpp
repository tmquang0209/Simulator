#include <bits/stdc++.h>
#include <fstream>
#include <windows.h>
#include <sstream>

void gotoxy(int x, int y);
void drawBox(int x, int y, int width, int height);
void drawUserList(int width, int height);

int main()
{
    system("cls");
    // Lấy kích thước của cửa sổ console
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    drawUserList(width, height);

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
    // Vẽ viền trên
    gotoxy(x, y);
    std::cout << char(218); // Góc trên bên trái
    for (int i = 1; i < width - 1; i++)
        std::cout << char(196); // Đường ngang
    std::cout << char(191); // Góc trên bên phải

    // Vẽ viền dọc
    for (int i = 1; i < height - 1; i++)
    {
        gotoxy(x, y + i);
        std::cout << char(179); // Đường dọc

        gotoxy(x + width - 1, y + i);
        std::cout << char(179); // Đường dọc
    }

    // Vẽ viền dưới
    gotoxy(x, y + height - 1);
    std::cout << char(192); // Góc dưới bên trái
    for (int i = 1; i < width - 1; i++)
        std::cout << char(196); // Đường ngang
    std::cout << char(217); // Góc dưới bên phải
}

void drawUserList(int width, int height)
{
    int userListHeight = 10;
    int userListWidth = 140;
    int userListY = (height - userListHeight) / 2;
    int userListX = (width - userListWidth) / 2;

    drawBox(userListX, userListY, userListWidth, userListHeight);

    // In tiêu đề danh sách người dùng
    gotoxy(userListX + 3, userListY + 2);
    std::cout << "STT";
    gotoxy(userListX + 10, userListY + 2);
    std::cout << "Name";
    gotoxy(userListX + 30, userListY + 2);
    std::cout << "Gmail";
    gotoxy(userListX + 55, userListY + 2);
    std::cout << "Phone";
    gotoxy(userListX + 75, userListY + 2);
    std::cout << "Username";
    gotoxy(userListX + 90, userListY + 2);
    std::cout << "Role";
    gotoxy(userListX + 110, userListY + 2);
    std::cout << "Block";
    gotoxy(userListX + 120, userListY + 2);
    std::cout << "Change PW";

    // Đọc dữ liệu từ file và hiển thị trong danh sách
    std::ifstream file("./data/info.txt");
    if (file)
    {
        std::string line;
        int row = 4; // Dòng bắt đầu in dữ liệu người dùng
        int stt = 1; // Số thứ tự
        while (std::getline(file, line))
        {
            std::string name, email, phone, username,pw, role, block, changePw;
            std::istringstream iss(line);
            std::getline(iss, name, '|');
            std::getline(iss, email, '|');
            std::getline(iss, phone, '|');
            std::getline(iss, username, '|');
            std::getline(iss, pw, '|');
            std::getline(iss, role, '|');
            std::getline(iss, block, '|');
            std::getline(iss, changePw, '|');

            gotoxy(userListX + 3, userListY + row);
            std::cout << stt;
            gotoxy(userListX + 10, userListY + row);
            std::cout << name;
            gotoxy(userListX + 30, userListY + row);
            std::cout << email;
            gotoxy(userListX + 55, userListY + row);
            std::cout << phone;
            gotoxy(userListX + 75, userListY + row);
            std::cout << username;
            gotoxy(userListX + 90, userListY + row);
            std::cout << role;
            gotoxy(userListX + 110, userListY + row);
            std::cout << block;
            gotoxy(userListX + 120, userListY + row);
            std::cout << changePw;
            row++;
            stt++;
        }
        file.close();
    }

    // Chờ người dùng nhấn phím để thoát
    gotoxy(userListX + (userListWidth - 14) / 2, userListY + userListHeight - 2);
    std::cout << "Press enter to exit...";
    std::cin.ignore();
}


