# WINDOWS SERVER USER MANAGEMENT SIMULATION
## SETUP
To run this project, install it locally using g++
``` 
g++ App.cpp -o App
.\App
```
## Before install app, we need create 2 folder
- data folder: create info.txt file to create default account
    + FullName|Email|Phone number|Username|Password|Account type|Disable|Change password|
    + Explain:
        * Account type is administrator or user,
        * Disable is 1 or 0,
        * Change password is 1 or 0
- log folder
    + All activity of user will be saved here
