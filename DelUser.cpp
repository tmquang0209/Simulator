#include <bits/stdc++.h>
#include <fstream>
#include <windows.h>
#include <sstream>

void gotoxy(int x, int y);
void drawBox(int x, int y, int width, int height);
void drawUserList(int width, int height);
void displayUserList(const std::string& filename, int userListX, int userListY, int rowStart);
bool deleteUser(const std::string& filename, const std::string& username, const std::string& password);
void drawInputBox(int x, int y, const std::string& label, std::string& input);
bool checkUserInfo(const std::string& filename, const std::string& username, const std::string& password);

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
    displayUserList("./data/info.txt", userListX, userListY, 4);

    // Nhập thông tin người dùng cần xóa
    std::string username, password;
    drawInputBox(userListX + 3, userListY + userListHeight + 2, "\nUsername: ", username);
    drawInputBox(userListX + 3, userListY + userListHeight + 3, "Password: ", password);

    // Kiểm tra thông tin người dùng trước khi xóa
    bool userInfoCorrect = checkUserInfo("./data/info.txt", username, password);

    if (userInfoCorrect)
    {
        // Xóa người dùng và ghi lại danh sách người dùng mới
        bool deleted = deleteUser("./data/info.txt", username, password);

        // Xóa nội dung bảng
        for (int row = 4; row < userListHeight - 1; row++)
        {
            gotoxy(userListX + 3, userListY + row);
            std::cout << std::string(userListWidth - 6, ' ');
        }

        // Hiển thị kết quả xóa người dùng
        gotoxy(userListX + (userListWidth - 14) / 2, userListY + userListHeight + 5);
        if (deleted)
            std::cout << "\nUser deleted successfully.";
        else
            std::cout << "\nFailed to delete user.";

        // Chờ 1 giây để hiển thị trạng thái xóa
        std::this_thread::sleep_for(std::chrono::seconds(1));

        system("cls");

        // Vẽ lại drawBox
        drawBox(userListX, userListY, userListWidth, userListHeight);

        // In lại tiêu đề danh sách người dùng
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
        displayUserList("./data/info.txt", userListX, userListY, 4);
    }
    else
    {
        gotoxy(userListX + (userListWidth - 18) / 2, userListY + userListHeight + 5);
        std::cout << "\nIncorrect username or password.";

        // Chờ 1 giây để hiển thị thông báo
        std::this_thread::sleep_for(std::chrono::seconds(1));

        system("cls");

        drawUserList(width, height);
    }
}


bool checkUserInfo(const std::string& filename, const std::string& username, const std::string& password)
{
    std::ifstream file(filename);
    if (file)
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::vector<std::string> userFields;
            std::string field;
            while (std::getline(iss, field, '|'))
            {
                userFields.push_back(field);
            }

            if (userFields.size() >= 8)
            {
                std::string usernameInFile = userFields[3];
                std::string passwordInFile = userFields[4];

                if (username == usernameInFile && password == passwordInFile)
                {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
    }
    return false;
}

void displayUserList(const std::string& filename, int userListX, int userListY, int startRow)
{
    std::ifstream file(filename);
    if (file)
    {
        std::string line;
        int stt = 1;
        int row = startRow;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::vector<std::string> userFields;
            std::string field;
            while (std::getline(iss, field, '|'))
            {
                userFields.push_back(field);
            }

            if (userFields.size() >= 8)
            {
                gotoxy(userListX + 3, userListY + row);
                std::cout << stt;
                gotoxy(userListX + 10, userListY + row);
                std::cout << userFields[0];
                gotoxy(userListX + 30, userListY + row);
                std::cout << userFields[1];
                gotoxy(userListX + 55, userListY + row);
                std::cout << userFields[2];
                gotoxy(userListX + 75, userListY + row);
                std::cout << userFields[3];
                gotoxy(userListX + 90, userListY + row);
                std::cout << userFields[5];
                gotoxy(userListX + 110, userListY + row);
                std::cout << userFields[6];
                gotoxy(userListX + 120, userListY + row);
                std::cout << userFields[7];

                stt++;
                row++;
            }
        }
        file.close();
    }
}

bool deleteUser(const std::string& filename, const std::string& username, const std::string& password)
{
    std::ifstream file(filename);
    if (file)
    {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::vector<std::string> userFields;
            std::string field;
            while (std::getline(iss, field, '|'))
            {
                userFields.push_back(field);
            }

            if (userFields.size() >= 8)
            {
                std::string usernameInFile = userFields[3];
                std::string passwordInFile = userFields[4];

                if (username != usernameInFile || password != passwordInFile)
                {
                    lines.push_back(line);
                }
            }
        }
        file.close();

        std::ofstream outFile(filename);
        if (outFile)
        {
            for (const std::string& line : lines)
            {
                outFile << line << '\n';
            }
            outFile.close();
            return true;
        }
    }
    return false;
}

void drawInputBox(int x, int y, const std::string& label, std::string& input)
{
    gotoxy(x, y);
    std::cout << label;

    std::getline(std::cin, input);
}
