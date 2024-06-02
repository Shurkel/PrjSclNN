#include "../utils/andreinet.h"


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

    n.noActivate(0);     // Deactivate all layers initially
    n.setActivate(1, 1); // Set ReLU activation for the hidden layer
    n.setActivate(2, 1); // Set sigmoid activation for the output layer
    n.connectLayers();   // Connect layers

    // Initialize weights and biases
    n.setWeightAll(1); // Set all weights to 1 (you may want to initialize them randomly or set them differently)
    n.setBiasAll(0);   // Example bias setting for the output layer (this can be adjusted or randomized)

    // Input features: [Hours Studied, Sleep (hours)]
    // C++ input data
vector<pair<double, double>> input = {
    // Fail values
    {2, 4}, {3, 5}, {1, 3}, {4, 2}, {2, 1},
    {3, 2}, {1, 5}, {4, 3}, {2, 6}, {3, 1},
    {2, 7}, {1, 4}, {4, 5}, {3, 6}, {1, 1},
    {4, 1}, {2, 2}, {3, 3}, {1, 2}, {4, 4},
    // Pass values
    {8, 10}, {9, 11}, {7, 9}, {10, 8}, {8, 7},
    {9, 8}, {7, 11}, {10, 9}, {8, 12}, {9, 7},
    {8, 13}, {7, 10}, {10, 11}, {9, 12}, {7, 7},
    {10, 7}, {8, 8}, {9, 9}, {7, 8}, {10, 10},
    {6, 6}, {11, 11}, {5, 5}, {12, 12}, {6, 5}
};

// Expected outputs: 0 for Fail, 1 for Pass
vector<double> expected = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1
};



    pair<
        vector<
            pair<double, double>>,
        vector<double>>
        trainingData;
    trainingData.first = input;
    trainingData.second = expected;
    /*
    trainingData = o pereche de vectori
    input = un vector de perechi de double-uri
    output = un vector de double-uri
    */

    int epochs = 10000;
    double learningRate = 0.06;
    cout << "BEFORE TRAINING";
    n.testNet(trainingData, true);

    n.backPropagate(trainingData, epochs, learningRate);

    cout << "\nAFTER TRAINING";
    n.testNet(trainingData, true);
    n.printCosts();


    

    








    // test network manually

    double threshold = 0.708253;
    n.clean();
    // not press escape
    double testStudy;
    double testSleep;
    pair<double, double> testInput;
    //
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        cout << "Enter study hours and sleep hours: ";
        cin >> testStudy;
        cin>> testSleep;
        testInput = {testStudy, testSleep};
        n.clean();
        n.clearSSR();
        n.setInputFromVector(testInput);
        n.passValues();
        double value = n.layers.back().nodes.back().value;
        cout << "Test value: " << value << "\n";
        if (value > threshold)
        {
            cout << "Pass\n";
        }
        else
        {
            cout << "Fail\n";
        }

    }

    
    t.stop();
    u.logTime();
    l.flush();
}