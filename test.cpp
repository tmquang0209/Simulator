#include <iostream>
#include <ctime>
#include <math.h>
#include <fstream>
using namespace std;
int main()
{
    char c;
    int r;
    srand(time(NULL));
    fstream f1;
    f1.open("test.txt", ios::app);
    for (int i = 0; i < 8; i++)
    {
        r = rand() % 26;
        c = 'A' + r;
        f1 << c;
    }
    f1 << endl;
    f1.close();
}