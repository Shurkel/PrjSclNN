#include "../utils/andreinet.h"



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
   
    
    
    
    t.start();

    
    net n({1, 1});
    n.loggingLayer(1);


    n.connectLayers();
    n.setValue(0,0,1);

    n.passValues();
    
    n.setExpected({1});
    n.getCosts();
    n.logCosts();

    n.printNet();
    
    
    t.stop();
    u.logTime();
    l.flush();
    l.clear();
    
    
    
}