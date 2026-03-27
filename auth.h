#ifndef AUTH_H
#define AUTH_H

#include "user.h"
#include <vector>
#include <fstream>

using namespace std;
class authSystem{
    vector<User> users;
    void saveToFile();
    public:
    authSystem();
    User* login();

    // admin functions
    void addUser();
    void listUser();
    void delUser();
};

#endif