#ifndef UI_H
#define UI_H
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

// Change text color easily
inline void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Fancy title banner
inline void printTitle(const string &title) {
    setColor(11);
    cout << "\n==============================\n";
    cout << "   " << title << "\n";
    cout << "==============================\n";
    setColor(7);
}

// Clean table header
inline void printTableHeader() {
    setColor(14);
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Price"
         << setw(10) << "Qty" << endl;
    setColor(7);
    cout << "---------------------------------------------\n";
}

#endif
