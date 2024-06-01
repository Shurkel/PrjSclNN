#include "../utils/andreinet.h"
#include <vector>
using namespace std;



void runDemo2(string outputfile)
{
    

    /*
    activate functions:
    0 - relu
    1 - sigmoid
    2 - softmax
    
    */
    
    t.start();
    
    
    net n({2, 4, 1});
    
    // Set activation functions for the layers
    
    n.noActivate(0);          // Deactivate all layers initially
    n.setActivate(1, 1);          // Set ReLU activation for the hidden layer
    n.setActivate(2, 1);          // Set sigmoid activation for the output layer
    n.connectLayers();            // Connect layers        
    
    // Initialize weights and biases
    n.setWeightAll(1);            // Set all weights to 1 (you may want to initialize them randomly or set them differently)
    n.setBiasAll(0) ;       // Example bias setting for the output layer (this can be adjusted or randomized)

    // Input features: [Hours Studied, Sleep (hours)]
    vector<pair<double, double>> input = {
        {2, 4}, // Fail
        {3, 6}, // Fail
        {4, 5}, // Fail
        {5, 7}, // Pass
        {6, 7}, // Pass
        {7, 8}  // Pass
    };

    // Expected outputs: 0 for Fail, 1 for Pass
    vector<double> expected = {0, 0, 0, 1, 1, 1};

    
        pair<
            vector< 
                pair<double, double>
            >,
            vector<double>
        > trainingData;
        trainingData.first = input;
        trainingData.second = expected;
    /*
    trainingData = o pereche de vectori
    input = un vector de perechi de double-uri
    output = un vector de double-uri
    */



    
    int epochs = 1;
    double learningRate = 0.1;
    
    for(int i = 0; i < trainingData.first.size(); i++)
    {
        n.clean();
        
        n.setInputFromVector(trainingData.first[i]); // input = {2, 4}
        n.setExpected({trainingData.second[i]}); // output = 0
        n.passValues(); // Forward pass
        n.getSSR(); // Calculate SSR
        n.printInput(); // Print input
        n.printExpected(); // Print expected output
        n.printActualOutput(); // Print output
        n.printSSR(); // Print SSR
        n.printNodeDetails(0, 2);
        en
        cout << u.sigmoid(3.99011);
        en en
        cin.get();
        return;
        
    }
    
    //n.backPropagate(trainingData, epochs, learningRate);

    
    

    



    t.stop();
    u.logTime();
    l.flush();
    
    
    
    
}