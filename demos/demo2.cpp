#include "../utils/andreinet.h"




void runDemo2(string outputfile)
{
    


    
    t.start();
    
    net n({1, 2, 1});
    
    n.setActivateAll(2);
    n.noActivate(0, 0);
    n.noActivate(0, 2);
    
    n.connectLayers();
    
    n.setWeight(0, 0, 0, 1, 3.34);
    n.setWeight(0, 0, 1, 1, -3.53);
    n.setWeight(0, 1, 0, 2, -1.22);
    n.setWeight(1, 1, 0, 2, -2.30);
    n.setBias(0, 1, -1.43);
    n.setBias(1, 1, 0.57);
    n.setBias(0, 2, 3);

    

    vector<double> input = {0, 0.5, 1};
    vector<double> expected = {0, 1, 0};
    
    for(int i = 0; i < input.size(); i++)
    {
        n.setValueAll(0);
        n.setValueFromVector(input);
        n.passValues();
        n.setExpectedFromVector(expected);
        n.getCosts();
        n.getSSR();
        n.printNet();
        n.logLayers();
        
        n.printCosts();
        n.clearCosts();
        cout << "----------------\n";
    }
    
    
    
    

    



    t.stop();
    u.logTime();
    l.flush();
    
    
    
    
}