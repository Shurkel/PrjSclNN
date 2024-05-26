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
    
    net n({1, 1, 1});
    
    n.noActivateAll();
    n.noActivate(1, 0);
    n.setActivate(1, 2);
    n.connectLayers();
    
    n.setWeightAll(1);
    n.setWeight(1, 0, 2, 0, 3);
    n.setBias(2, 0, 3);






    vector<double> input = {0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5};
    vector<double> expected = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5};
    pair<double, double> trainingData;
    int epochs = 1;
    
    n.backPropagate({input, expected}, epochs, 0.1);

    
    

    



    t.stop();
    u.logTime();
    l.flush();
    
    
    
    
}