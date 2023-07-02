#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <conio.h> // Thư viện dùng để đọc phím bấm

using namespace std;

// Function to draw a checkbox
void drawCheckbox(bool isChecked, const string& label)
{
    if (isChecked)
        cout << "[x] " << label;
    else
        cout << "[ ] " << label;
}

int main()
{
    // Initialize checkbox states
    vector<bool> checkboxes = {false, false, false, false};
    bool isDisable = false, isRequest = false;

    string filename = "./data/info.txt";
    ifstream file(filename);
    vector<vector<string>> data;

    if (file)
    {
        string line;
        while (getline(file, line))
        {
            vector<string> row;
            stringstream ss(line);
            string value;

            while (getline(ss, value, '|'))
            {
                row.push_back(value);
            }

            data.push_back(row);
        }

        file.close();

        // Nhập tên người dùng cần sửa dữ liệu
        string username;
        cout << "Account name: ";
        getline(cin, username);

        // Tìm kiếm người dùng trong dữ liệu và sửa dữ liệu của họ
        bool found = false;

        for (auto& row : data)
        {
            if (row.size() > 3 && row[3] == username)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            // Main loop
            while (true)
            {
                // Clear the terminal screen
                system("cls");

                // Draw checkboxes
                cout << "You're working on account: " << username << endl;
                cout << endl;
                cout << "Press button 1 or 2 or 3 or 4 or Q to:\n";
                drawCheckbox(checkboxes[0], "Deactivate account");
                cout << "\n";
                drawCheckbox(checkboxes[1], "Request a password change");
                cout << "\n";
                drawCheckbox(checkboxes[2], "Undeactivate account");
                cout << "\n";
                drawCheckbox(checkboxes[3], "Delete password change request");
                cout << "\n";
                cout << "[Q] Quit";
                cout << "\n";

                // Wait for user input
                char input = getch();

                // Handle user input
                switch (input)
                {
                    case '1':
                        checkboxes[0] = !checkboxes[0];
                        checkboxes[1] = false;
                        checkboxes[2] = false;
                        checkboxes[3] = false;
                        isDisable = true;
                        break;
                    case '2':
                        checkboxes[1] = !checkboxes[1];
                        checkboxes[0] = false;
                        checkboxes[2] = false;
                        checkboxes[3] = false;
                        isRequest = true;
                        break;
                    case '3':
                        checkboxes[2] = !checkboxes[2];
                        checkboxes[0] = false;
                        checkboxes[1] = false;
                        checkboxes[3] = false;
                        isDisable = false;
                        break;
                    case '4':
                        checkboxes[3] = !checkboxes[3];
                        checkboxes[0] = false;
                        checkboxes[2] = false;
                        checkboxes[1] = false;
                        isRequest = false;
                        break;
                    case 'q':
                    case 'Q':
                        break;
                }
                if (input == 'q' || input == 'Q')
                    break;
            }

            // Sửa dữ liệu người dùng
            for (auto& row : data)
            {
                if (row.size() > 3 && row[3] == username)
                {
                    if (isDisable)
                        row[row.size() - 2] = "1";
                    if (isRequest)
                        row[row.size() - 1] = "1";
                    if (!isDisable)
                        row[row.size() - 2] = "0";
                    if (!isRequest)
                        row[row.size() - 1] = "0";
                }
            }

            // Ghi dữ liệu đã sửa đổi vào tệp
            ofstream outFile(filename);
            if (outFile)
            {
                for (const auto& row : data)
                {
                    for (size_t i = 0; i < row.size(); i++)
                    {
                        outFile << row[i];
                        if (i != row.size() - 1)
                        {
                            outFile << "|";
                        }
                    }
                    outFile << "\n";
                }

                outFile.close();
                cout << "Complete\n";
            }
            else
            {
                cerr << "Error: can't write\n";
            }
        }
        else
        {
            cout << "User not found in the data.\n";
        }
    }
    else
    {
        cerr << "Error: can't open\n";
    }

    return 0;
}
