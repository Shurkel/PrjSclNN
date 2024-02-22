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


//INCLUDES
#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
using namespace std;



//DEFINES
#define en cout << '\n';
#define cls system("cls");


ofstream l("logs.out");


//CLASSES
class Node
{

public:
    double value;
    double bias = 0.0;
    int id = 0;
    int layerId = 0;
    bool log = false;
    vector<pair<Node *, double>> nextNodes;//with weights


    

    Node(double val, double b = 0.0)
    {
        

        value = val;
        bias = b;
    }

    //////////////////////////
    //////NODE FUNCTIONS//////
    //////////////////////////
    void logging()
    {
        if(log)
        {
            
            l << "[-] Logging disabled for node with id " << id << "\n";
            log = false;
        }
        else
        {
            l << "[+] Logging enabled for node with id " << id << "\n";
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
    int layerId = 0;
    Layer(int n)
    {
        for (int i = 0; i < n; i++)
        {
            nodes.push_back(Node(0));
        }
    }
    void setValueAll(double val)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes[i].setValue(val);
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
        cout << "--------------\n";
        cout << "|LayerID " << layerId << "   |\n";
        cout << "--------------\n";
        cout << "Node Id | Value\n";
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << "  " << nodes[i].getId() << " ------> " << nodes[i].getValue() << "\n";
        }
        en
    }
    
};

class net
{
public:
    vector<Layer> layers;

    net(vector<int> layerSizes)
    {
        for (int i = 0; i < layerSizes.size(); i++)
        {
            cout << "[+]Layer created";
            layers.push_back(Layer(layerSizes[i])); // Create the layer first
            layers[i].setIdAll(i);                  // Then set its ID
            cout << " at id " << layers[i].layerId;
            cout << " with size " << layers[i].nodes.size() << "\n";
        }
    }
    void setWeight(Node *n1, Node *n2, double w)
    {
        n1->setWeight(n2, w);
    }
    void printLayer(int id)
    {
        layers[id].printLayer();
    }
    
    void printLayers()
    {
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i].printLayer();
        }
    }
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
        {
            layers[i].passValues();
        }
    }
    void printNextNodes(int layerId, int nodeId)
    {
        layers[layerId].nodes[nodeId].printNextNodes();
    }
    
};

