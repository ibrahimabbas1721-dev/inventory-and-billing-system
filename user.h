#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;
class User
{
    string username, password, role;

public:
    User(string u = "", string p = "", string r = "") : username(u), password(p), role(r) {}
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
};
#endif