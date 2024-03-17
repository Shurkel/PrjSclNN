#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <random>
#include <chrono>
#include <string>
#include <cstdlib>
using namespace std;




ofstream l("../logs/logs.out");
void setLogFile(const string& filename) {
    if (l.is_open()) {
        l.close();
    }
    string fullPath = "./../logs/" + filename;
    l.open(fullPath, std::ios::trunc);
    if (!l) {
        std::cerr << "Failed to open log file: " << fullPath << '\n';
        exit(1);
    }
}


//DEFINES
#define en cout << '\n';
#define len l << '\n';
#define cls system("cls");
#define test cout << "test\n";
#define ltest l << "test\n";l.flush();