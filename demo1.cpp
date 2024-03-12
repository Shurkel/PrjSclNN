#include "utils.h"



void runDemo1(string outputfile)
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
    setLogFile(outputfile);
     
    t.start();

    
    
    net n({1, 3});
    n.loggingLayer(1);
    n.connectLayers();
    n.setValueAll(0, 1);
    n.passValues();
    n.setExpected({1, 0});
    n.getCosts();
    n.logCosts();
    n.printNet();
    
    
    t.stop();
    
    l.flush();
    l.clear();
    
    
    
}