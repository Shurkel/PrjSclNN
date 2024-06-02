#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <random>
#include <chrono>
#include <string>
#include <cstdlib>
#include "TextTable.h"

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
#define tab cout << (char)9;
//https://stackoverflow.com/questions/9158150/colored-output-in-c/9158263
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */