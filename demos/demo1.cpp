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

    
    vector<vector<double>> inputs = {{1, 1}, {1, 0}, {0, 1}, {0, 0}};
    vector<vector<double>> outputs = {{0}, {1}, {1}, {0}};
    
    //t.start();

    
    net n({2, 3, 1});
    
    n.setActivateAll(1);
    
    n.setWeightAll(1.0);
    
    n.connectLayers();
    cout << "Before training\n";
    en en
    for(int i = 0; i < inputs.size(); i++)
    {
        

        n.setValueFromVector(inputs[i]);
        n.passValues();
        n.setExpected(outputs[i]);
        n.getCosts();
        cout << "Input: " << inputs[i][0] << " " << inputs[i][1] << "\n";
        cout << "Output: " << n.layers.back().nodes[0].value << "\n";
        cout << "Expected: " << outputs[i][0] << "\n";
        cout << "Cost: " << n.costs[0] << "\n";
        cout << "-----\n";

    }
    cout << "Press any key to continue\n";
    cin.get();
    cout << "[+]Training\n";
    for(int i = 0; i < 100; i++)
    {
        cout << "Epoch " << i << "\n";
        for(int j = 0; j < inputs.size(); j++)
        {
            
            n.setValueFromVector(inputs[j]);
            
            n.passValues();
            
            n.setExpected(outputs[j]);
            
            n.getCosts();
            n.backpropagation(0.1);
            
            
        }
    }

    cout << "After training\n";
    double avgCost = 0;
    for(int i = 0; i < inputs.size(); i++)
    {
        

        n.setValueFromVector(inputs[i]);
        n.passValues();
        n.setExpected(outputs[i]);
        n.getCosts();
        cout << "Input: " << inputs[i][0] << " " << inputs[i][1] << "\n";
        cout << "Output: " << n.layers.back().nodes[0].value << "\n";
        cout << "Expected: " << outputs[i][0] << "\n";
        cout << "Cost: " << n.costs[0] << "\n";
        cout << "-----\n";
        avgCost += n.costs[0];
    }
    avgCost /= inputs.size();
    cout << "Average cost: " << avgCost << "\n";
    
    //t.stop();
    u.logTime();
    l.flush();
    l.clear();
    
    
    
}