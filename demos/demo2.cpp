#include "../utils/andreinet.h"




void runDemo2(string outputfile)
{
    

    /*
    activate functions:
    0 - relu
    1 - sigmoid
    2 - softmax
    
    */
    
    t.start();
    
    net n({1, 1});
    
    n.noActivateAll();
    
    
    n.connectLayers();
    
    n.setWeightAll(1);
    n.setBiasAll(0);
    

    vector<double> input = {0, 0.5, 1};
    vector<double> expected = {1, 1.5, 2};
    

    for(int j = 0; j < 5; j++)
    {
        cout << "/////////////GEN " << j << "/////////////\n";
        for(int i = 0; i < input.size(); i++)
        {
        n.setValueAll(0);
        n.setValueFromVector({input[i]});
        
        n.setExpected({expected[i]});
        
        cout << "[+]Input: " << input[i] << "\n";
        cout << "[+]Expected: " << expected[i];
        n.passValues();
        n.printActualOutput();
        
        n.backPropagate(0.1);
        n.printCosts();
        //cin.get();
        //n.printCosts();
        n.clearCosts();
        n.clearSSR();
        cout << "\n----------------\n";
        }
    }
    
    
    
    
    

    



    t.stop();
    u.logTime();
    l.flush();
    
    
    
    
}