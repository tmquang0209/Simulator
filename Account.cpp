#include "Account.h"

using namespace std;

Account::Account()
{
}

void Account::addToList(Info info)
{
    list.push_back(info);
}
