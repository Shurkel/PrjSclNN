#include "utils.h"
#include <chrono>

using namespace std;
int main()
{
    

    /* ifstream f("config.cfg");
    //read line 5 from file
    int currentLine = 0;
    int targetLine = 4;
    string line;
    while (currentLine < targetLine && getline(f, line)) {
        currentLine++;
    } */




    /*
    relu - 0
    sigmoid - 1
    */
    cls
    t.start();

    
    net n({1, 5});
    n.loggingLayer(1);
    n.connectLayers();
    n.setValueAll(0, 1);
    n.passValues();
    n.setExpected({1, 0, 1, 0, 0});
    n.getCosts();
    n.logCosts();
    n.printNet();
    
    
    t.stop();
    
    l.flush();
    
    return 0;
    
    
}