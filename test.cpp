#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <unistd.h>
#include <conio.h> // Include the conio.h header for _getch() function
#include "Draw.h"
#include "Draw.cpp"
#include "CharacterHandling.h"
#include "CharacterHandling.cpp"
#include "Struct.h"
#include "FileManager.h"
#include "FileManager.cpp"

int main()
{
    Account account;
    account.checkInfo("tmq", "123");
    cout << account.getInfo().username;

    FileManager fileManager;
    return 0;
}
