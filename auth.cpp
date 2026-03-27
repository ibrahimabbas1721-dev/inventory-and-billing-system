#include "auth.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "ui.h"
using namespace std;

authSystem::authSystem() {
    ifstream file("data/users.txt");

    // If the file doesn't exist, create it with default users
    if (!file) {
        cout << "users.txt not found. Creating default user file...\n";
        ofstream newFile("data/users.txt");
        newFile << "admin,admin123,admin\n";
        newFile << "cashier,cashier123,cashier\n";
        newFile.close();
        // Reopen the newly created file for reading
        file.open("data/users.txt");
    }

    // Load users from the file
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string u, p, r;
        getline(ss, u, ',');
        getline(ss, p, ',');
        getline(ss, r, ',');
        users.push_back(User(u, p, r));
    }

    file.close();
}

User* authSystem::login() {
    string u, p;
    printTitle("Login Page");
    cout << "Enter Username: ";
    cin >> u;
    cout << "Enter Password: ";
    cin >> p;

    for (auto &user : users) {
        if (user.getUsername() == u && user.getPassword() == p) {
            cout << "Login Successful! Role: " << user.getRole() << endl;
            return &user;
        }
    }

    cout << "Invalid Username or Password\n";
    return nullptr;
}

void authSystem :: saveToFile(){
    ofstream file("data/users.txt");
    for(auto &u : users){
        file << u.getUsername()<<","<< u.getPassword()<<","<< u.getRole() << "\n";
    }
};

void authSystem :: listUser(){
    printTitle("Users");
    cout << "Username\tRole\n";
    cout << "-----------------------------\n";
    for(auto &u : users){
        cout << u.getUsername() << "\t\t" << u.getRole()<< endl;
    }
}

void authSystem :: addUser(){
    string username, password , role;
    printTitle("Add User");
    cout << "Enter User Name : ";
    cin >> username;
    cout << "Enter User Password : ";
    cin >> password;
    cout << "Enter User Role : ";
    cin >> role;

    for(auto &u:users){
        if(u.getUsername() == username){
            cout << "User Already Exist...\n";
            return;
        }
    }
    users.push_back(User(username,password,role));
    saveToFile();
    cout << "User Added Successully..\n";
}
void authSystem::delUser(){
    string username;
    cout << "Enter User Name To Delete\n";
    cin >> username;
    for(int i = 0; i < users.size() ; i++){
        if(users[i].getUsername() == username){
            users.erase(users.begin() + i);
            saveToFile();
            cout << "User Deleted Successfully..\n";
            return;
        }
    }
    cout << "User not found!\n";
}