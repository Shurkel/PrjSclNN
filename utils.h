/*
///////////////////////////////////////////
//         ROMAN ANDREI DAN              //
//         2023-2024                     //
//       NAME: andreiNET                 //
//       VERSION: 1.0                    //
///////////////////////////////////////////
*/

//FLAGS 
// $TD - TO DO
// $NW - NOT WORKING
// $O - OPTIMIZATION
// $OF - OPTIONAL FEATURE

/*
    relu - 0
    sigmoid - 1
*/


//INCLUDES
#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <random>
#include <chrono>
#include <string>
#include <cstdlib>



using namespace std;




std::ofstream l("logs/logs.out");
void setLogFile(const std::string& filename) {
    if (l.is_open()) {
        l.close();
    }
    std::string fullPath = "logs/" + filename;
    l.open(fullPath, std::ios::app);
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




//CLASSES

class util
{
public:
    double relu(double x)
    {
        if (x > 0)
        {
            return x;
        }
        else
        {
            return 0;
        }
    }
    double sigmoid(double x)
    {
        return 1 / (1 + exp(-x));
    }
    void logVector(vector<double> v)
    {
        for (int i = 0; i < v.size(); i++)
        {
            l << v[i] << " ";
        }
        len
    }
    

    void deleteLogs() {
    
    system("del /Q logs\\*");
}
    
    
}u;

class timer {
public:
    chrono::time_point<chrono::high_resolution_clock> startTime, endTime;
    chrono::duration<float> duration;

    void start() {
        startTime = chrono::high_resolution_clock::now();
    }

    void stop() {
        endTime = chrono::high_resolution_clock::now();
        duration = endTime - startTime;

        //time in milliseconds
        l << "Time: " << duration.count() * 1000 << "ms\n";
    }
}t;

//node
class Node
{

public:
    double value;
    double bias = 0.0;
    int id = 0;
    int layerId = 0;
    bool log = false;
    bool yesActivate = true;
    int activationFunction = 0;
    vector<pair<Node *, double>> nextNodes;//with weights


    

    Node(double val, double b = 0.0)
    {
        

        value = val;
        bias = b;

    }

    //////////////////////////
    //////NODE FUNCTIONS//////
    //////////////////////////
    void activate(int function)
    {
        //relu
        if (function == 0)
        {
            value = u.relu(value);
        }
        //sigmoid
        else if (function == 1)
        {
            value = u.sigmoid(value);
        }
        
    }
    void logging()
    {
        if(log)
        {
            
            l << "[-] Logging disabled for node with id " << id << "\n";
            log = false;
        }
        else
        {
            l << "[+] Logging enabled for node with id " << id << ", layer: " << layerId << "\n";
            log = true;
        }            
    }
    void connect(Node *next, double w=1.0)
    {
        nextNodes.push_back(make_pair(next, w));
        //log
        if(log)
        {
            l << "[+] Node " << id << " connected to node " << next->id << " with weight " << w << "\n";
        }
    }
    void setWeight(Node *next, double w)
    {
        for (int i = 0; i < nextNodes.size(); i++)
        {
            if (nextNodes[i].first == next)
            {
                
                nextNodes[i].second = w;
                if(log)
                    l << "[+] Weight set to " << w << " for node " << next->id << " from node " << id << "\n";
            }
        }
    }
    void setWeightAll(double w)
    {
        for (int i = 0; i < nextNodes.size(); i++)
        {
            nextNodes[i].second = w;
            if(log)
                l << "[+] Weight set to " << w << " for node " << nextNodes[i].first->id << " from node " << id << "\n";
        }
    }
    void disconnect(Node *next)
    {
        for (int i = 0; i < nextNodes.size(); i++)
        {
            if (nextNodes[i].first == next)
            {
                nextNodes.erase(nextNodes.begin() + i);
                if(log)
                    l << "[-] Node " << id << " disconnected from node " << next->id << "\n";
            }
        }
    }
    void disconnectAll()
    {
        nextNodes.clear();
        if(log)
            l << "[-] Cleared all connections for node " << id << "\n";
    }
    int getId()
    {
        return id;
    }
    double getValue()
    {
        return value;
    }

    void setValue(double val)
    {
        value = val;
        if(log)
            l << "[+] Node " << id << " value set to " << val << "\n";
    }
    
    void setBias(double w)
    {
        bias = w;
        if(log)
            l << "[+] Node " << id << " bias set to " << w << "\n";
    }
    void setId(int id)
    {
        this->id = id;
         if(log)
            l << "[+] Node " << id << " ID set to " << id << "\n";

    }

    vector<pair<Node*, double>> getNextNodes() const
    {
        return nextNodes;
    }
    void passValues()
    {
        value += bias;
        if(yesActivate)
        {
            activate(activationFunction);
        }
        
        for (int i = 0; i < nextNodes.size(); i++)
        {

            nextNodes[i].first->setValue(
                (value*nextNodes[i].second) + nextNodes[i].first->getValue()
                );
            if(log)
            {
                l << "[+] Node " << id << " passed value " << value << " to node " << nextNodes[i].first->id << " with weight " << nextNodes[i].second << "\n";
            }
        }

    }
    void printNextNodes()
    {
        cout << "[x] Node " << id << " at layer " << layerId << " is connected to nodes:\n"
        <<"LayerID | nodeID |  weight\n";
        for (int i = 0; i < nextNodes.size(); i++)
        {
            cout << "  "  << nextNodes[i].first->layerId << "          " << nextNodes[i].first->getId()<< "         " << nextNodes[i].second << "\n";
        }
        en
    }
};

// layer
class Layer
{
public:
    vector<Node> nodes;
    bool yesActivate = true;
    int layerId = 0;

    Layer(int n)
    {
        
        for (int i = 0; i < n; i++)
        {
            nodes.push_back(Node(0));
            nodes[i].yesActivate = yesActivate;
        }
    }

    void setValueFromVector(vector<double> values)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes[i].setValue(values[i]);
        }
    }

    void noActivate()
    {
        if(yesActivate)
        {
            yesActivate = false;
            for (int i = 0; i < nodes.size(); i++)
            {
                nodes[i].yesActivate = yesActivate;
            }
            l << "[-] Layer " << layerId << " deactivated\n";
        }
        else
        {
            yesActivate = true;
            for (int i = 0; i < nodes.size(); i++)
            {
                nodes[i].yesActivate = yesActivate;
            }
            l << "[+] Layer " << layerId << " activated\n";
        }
        
    }
    void setActivateAll(int function)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes[i].activate(function);
        }
    }
    void setActivate(int function)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes[i].activationFunction = function;
        }
    }
    void setValueAll(double val)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes[i].setValue((double)val);
            //cout << "Node " << nodes[i].getId() << " set to " << nodes[i].getValue() << "\n";
        }
    }
    void setBiasAll(double w)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes[i].setBias(w);
        }
    }
    void setIdAll(int id)
    {

        layerId = id;
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes[i].setId(i);
            nodes[i].layerId = layerId;
        }
    }
    
    void connect(Layer *next)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            for (int j = 0; j < next->nodes.size(); j++)
            {
                nodes[i].connect(&next->nodes[j]);
            }
        }
    }
    void disconnect(Layer *next)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            for (int j = 0; j < next->nodes.size(); j++)
            {
                nodes[i].disconnect(&next->nodes[j]);
            }
        }
    }
    void passValues()
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes[i].passValues();

        }
    }
    void printLayer()
    {
        // make it fancy with "" and id and stuff
        l << "--------------\n";
        l << "|LayerID " << layerId << "   |\n";
        l << "--------------\n";
        l << "Node Id | Value\n";
        for (int i = 0; i < nodes.size(); i++)
        {
            l << "  " << nodes[i].getId() << " ------> " << nodes[i].getValue() << "\n";
        }
        len 
    }
    
};

//net
class net
{
public:
    vector<Layer> layers;
    vector<double> expected;
    vector<double> costs;
    
    net(vector<int> layerSizes)
    {
        for (int i = 0; i < layerSizes.size(); i++)
        {
            
            l << "[+]Layer created";
            layers.push_back(Layer(layerSizes[i])); // Create the layer first
            layers[i].setIdAll(i);                  // Then set its ID
            l << " at id " << layers[i].layerId;
            l << " with size " << layers[i].nodes.size() << "\n";
            
        }
        len
    }

    //layer functions
    void loggingGlobal()
    {
        for (int i = 0; i < layers.size(); i++)
        {
            for (int j = 0; j < layers[i].nodes.size(); j++)
            {
                layers[i].nodes[j].logging();
            }
        }
    }
    void loggingLayer(int layerId)
    {
        for (int i = 0; i < layers[layerId].nodes.size(); i++)
        {
            layers[layerId].nodes[i].logging();
        }
    }
    void setExpected(vector<double> expectedValues)
    {
        expected = expectedValues;
       
    }
    void getCosts()
    {
        for (int i = 0; i < layers.back().nodes.size(); i++)
        {
            costs.push_back(layers.back().nodes[i].value - expected[i]);
        }
    }
    void logCosts()
    {
        l << "[+]Costs: ";
        for (int i = 0; i < costs.size(); i++)
        {
            l << costs[i] << " ";
        }
        len
    }
    void setValueAll(int layerId, double val)
    {
        layers[layerId].setValueAll(val);
    }   

    void setBiasAll(int layerId, double w)
    {
        layers[layerId].setBiasAll(w);
    }

    void setIdAll(int layerId, int id)
    {
        layers[layerId].setIdAll(id);
    }

    void setActivateAll(int function)
    {
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i].setActivateAll(function);
        }
    }

    void noActivate(int layerId)
    {
        layers[layerId].noActivate();
    }

    void noActivateAll()
    {
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i].noActivate();
        }
    }

    void setActivate(int layerId, int function)
    {
        layers[layerId].setActivate(function);
    }

    void printLayer(int id)
    {
        layers[id].printLayer();
    }

    void printNet()
    {
        len
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i].printLayer();
        }
    }

    //node functions
    void setWeight(Node *n1, Node *n2, double w)
    {
        n1->setWeight(n2, w);
    }

    void printNextNodes(int layerId, int nodeId)
    {
        layers[layerId].nodes[nodeId].printNextNodes();
    }
    
    //net functions
    void connectLayers()
    {
        for (int i = 0; i < layers.size() - 1; i++)
        {
            layers[i].connect(&layers[i + 1]);
        }
    }
    void passValues()
    {
        for (int i = 0; i < layers.size(); i++)
                layers[i].passValues();
    }
    
    
    




};


