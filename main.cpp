#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;
#define en cout << '\n';
#define cls system("cls");
class Node
{

public:
    double value;
    double bias = 0.0;
    int id = 0;
    int layerId = 0;
    vector<pair<Node *, double>> nextNodes;//with weights
    
    Node(double val, double b = 0.0)
    {
        value = val;
        bias = b;
    }

    void connect(Node *next, double w=1.0)
    {
        nextNodes.push_back(make_pair(next, w));
    }
    void setWeight(Node *next, double w)
    {
        for (int i = 0; i < nextNodes.size(); i++)
        {
            if (nextNodes[i].first == next)
            {
                nextNodes[i].second = w;
            }
        }
    }
    void setWeightAll(double w)
    {
        for (int i = 0; i < nextNodes.size(); i++)
        {
            nextNodes[i].second = w;
        }
    }
    void disconnect(Node *next)
    {
        for (int i = 0; i < nextNodes.size(); i++)
        {
            if (nextNodes[i].first == next)
            {
                nextNodes.erase(nextNodes.begin() + i);
            }
        }
    }
    void disconnectAll()
    {
        nextNodes.clear();
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
    }
    void setBias(double w)
    {
        bias = w;
    }
    void setId(int id)
    {
        this->id = id;
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

int main()
{
    cls

    net n({2, 2, 2});
    en

    n.connectLayers();  


    n.layers[0].setValueAll(1);
    n.layers[0].nodes[0].setWeightAll(0.5);
    
    
    
    n.passValues();
    
    //analytics
    n.printLayers();
    n.printNextNodes(0, 0);
    n.printNextNodes(0, 1);
    n.printNextNodes(1, 0);
    n.printNextNodes(1, 1);
    n.printNextNodes(2, 0);
    n.printNextNodes(2, 1);
    en
    

    return 0;
}