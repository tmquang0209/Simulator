#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <conio.h>

using namespace std;

int width, height;

void gotoxy(int x, int y);
void drawBox(int x, int y, int width, int height);
void signUp(int width, int height);
void saveUserToFile(const string& filename, const string& name, const string& gmail, const string& phoneNumber, const string& account, const string& passWord);
bool hasUppercase(const string& str);
bool hasLowercase(const string& str);
bool hasDigit(const string& str);
bool isExistingAccount(const string& filename, const string& account);

int main()
{
    system("cls");
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
    signUp(width, height);
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

void signUp(int width, int height)
{
    // Tạo một cửa sổ con để hiển thị giao diện đăng nhập
    int loginWinHeight = 12; // Tăng chiều cao cửa sổ đăng nhập để chứa thêm các trường thông tin
    int loginWinWidth = 40;
    int loginWinY = (height - loginWinHeight) / 2;
    int loginWinX = (width - loginWinWidth) / 2;

    drawBox(loginWinX, loginWinY, loginWinWidth, loginWinHeight);

    gotoxy(loginWinX + 2, loginWinY + 2);
    cout << "\tFill your information";

    gotoxy(loginWinX + 2, loginWinY + 4);
    cout << "Full name: ";

    gotoxy(loginWinX + 2, loginWinY + 5);
    cout << "Email: ";

    gotoxy(loginWinX + 2, loginWinY + 6);
    cout << "Phone number: ";

    gotoxy(loginWinX + 2, loginWinY + 7);
    cout << "Account: ";

    gotoxy(loginWinX + 2, loginWinY + 8);
    cout << "Password: ";

    gotoxy(loginWinX + 2, loginWinY + 9);
    cout << "Confirm password: ";

    string name, gmail, phoneNumber, account, passWord, confirmPassword;

    gotoxy(loginWinX + 20, loginWinY + 4);
    getline(cin, name);

    gotoxy(loginWinX + 20, loginWinY + 5);
    getline(cin, gmail);

    gotoxy(loginWinX + 20, loginWinY + 6);
    getline(cin, phoneNumber);

    gotoxy(loginWinX + 20, loginWinY + 7);
    getline(cin, account);

    while (isExistingAccount("./data/info.txt", account))
    {
        gotoxy(loginWinX + 2, loginWinY + 12);
        cout << "The account already exists!";     // Thông báo trùng lặp

        gotoxy(loginWinX + 20, loginWinY + 7);
        cout << setw(loginWinWidth - 22) << " ";  // Xóa nội dung dòng tài khoản
        gotoxy(loginWinX + 20, loginWinY + 7);
        getline(cin, account);

        gotoxy(loginWinX + 2, loginWinY + 12);
        cout << setw(loginWinWidth) << " ";  // Xóa nội dung dòng thông báo
    }

    gotoxy(loginWinX + 20, loginWinY + 8);
    getline(cin, passWord);

    string passwordRequirements = "";

    // Kiểm tra mật khẩu 
    while (passWord.length() < 8 || passWord.length() > 12 || !hasUppercase(passWord) || !hasLowercase(passWord) || !hasDigit(passWord))
    {
        passwordRequirements = "";
        if (passWord.length() < 8 || passWord.length() > 12) {
            passwordRequirements += "8-12 characters, ";
        }
        if (!hasUppercase(passWord)) {
            passwordRequirements += "at least one uppercase letter, ";
        }
        if (!hasLowercase(passWord)) {
            passwordRequirements += "at least one lowercase letter, ";
        }
        if (!hasDigit(passWord)) {
            passwordRequirements += "at least one digit, ";
        }

        gotoxy(loginWinX + 2, loginWinY + 12);
        cout << "Password required " << passwordRequirements.substr(0, passwordRequirements.length() - 2);  // Thông báo lỗi

        gotoxy(loginWinX + 20, loginWinY + 8);
        cout << setw(loginWinWidth - 22) << " ";  // Xóa nội dung dòng mật khẩu
        gotoxy(loginWinX + 20, loginWinY + 8);
        getline(cin, passWord);

        gotoxy(loginWinX + 2, loginWinY + 12);
        cout << setw(loginWinWidth + 45) << " ";  // Xóa nội dung dòng thông báo
    }

    gotoxy(loginWinX + 20, loginWinY + 9);
    getline(cin, confirmPassword);

    // Kiểm tra nhập lại mật khẩu
    while (passWord != confirmPassword) {
        gotoxy(loginWinX + 2, loginWinY + 12);      
        cout << "Password mismatch. Try again!";    // Thông báo lỗi

        gotoxy(loginWinX + 20, loginWinY + 9);
        cout << setw(loginWinWidth - 22) << " ";  // Xóa nội dung dòng nhập lại mật khẩu
        gotoxy(loginWinX + 20, loginWinY + 9);
        getline(cin, confirmPassword);
    }

    // Lưu thông tin người dùng vào file
    if (name.empty() || gmail.empty() || phoneNumber.empty() || account.empty() || passWord.empty() || confirmPassword.empty())
    {
        cout << "Fill in information: " << endl;
    }
    else
    {
        saveUserToFile("./data/info.txt", name, gmail, phoneNumber, account, passWord);
        system("cls");
        cout << "User information saved" << endl;
    }
}

void saveUserToFile(const string& filename, const string& name, const string& gmail, const string& phoneNumber, const string& account, const string& passWord)
{
    ofstream fout(filename, ios::app); // Mở file để ghi dữ liệu ở cuối file

    if (fout.is_open())
    {
        fout << name << "|" << gmail << "|" << phoneNumber << "|" << account << "|" << passWord << "|0|0|";
        fout << endl;
        fout.close();
    }
    else
    {
        cout << "Unable to open file: " << filename << endl;
    }
}

bool hasUppercase(const string& str)
{
    for (char c : str)
    {
        if (isupper(c))
        {
            return true;
        }
    }
    return false;
}

bool hasLowercase(const string& str)
{
    for (char c : str)
    {
        if (islower(c))
        {
            return true;
        }
    }
    return false;
}

bool hasDigit(const string& str)
{
    for (char c : str)
    {
        if (isdigit(c))
        {
            return true;
        }
    }
    return false;
}

bool isExistingAccount(const string& filename, const string& account)
{
    ifstream fin(filename);
    if (fin.is_open())
    {
        string line;
        while (getline(fin, line))
        {
            stringstream ss(line);
            string savedAccount;
            int fieldCount=0;

            while (getline(ss, savedAccount, '|'))
            {
                fieldCount++;
                if (fieldCount == 4) 
                {
                    if (savedAccount == account)
                    {
                        fin.close();
                        return true;
                    }
                }
            }
        }
        fin.close();
    }
    return false;
}