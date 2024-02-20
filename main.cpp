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
    double Bias  = 1.0;
    int id = 0;
    int layerId = 0;
    vector<Node *> nextNodes;
    Node(double val, double w = 1.0)
    {
        value = val;
        Bias = w;
    }

    void connect(Node *next)
    {
        nextNodes.push_back(next);
    }
    void disconnect(Node *next)
    {
        for (int i = 0; i < nextNodes.size(); i++)
        {
            if (nextNodes[i] == next)
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
        Bias = w;
    }
    void setId(int id)
    {
        this->id = id;
    }

    vector<Node *> getNextNodes() const
    {
        return nextNodes;
    }
    void passValues()
    {
        for (int i = 0; i < nextNodes.size(); i++)
        {

            nextNodes[i]->setValue(
                value * nextNodes[i]->Bias + nextNodes[i]->getValue());
        }
    }
    void printNextNodes()
    {
        cout << "Node " << id << " from layer " << layerId << " is connected to nodes ";
        for (int i = 0; i < nextNodes.size(); i++)
        {
            cout << nextNodes[i]->getId() << " ";
        }
        cout << "from layer " << nextNodes[0]->layerId << "\n";
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
            cout << "Node " << nodes[i].getId() << " set to " << nodes[i].getValue() << "\n";
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
            cout << "Layer created";
            layers.push_back(Layer(layerSizes[i])); // Create the layer first
            layers[i].setIdAll(i);                  // Then set its ID
            cout << " at id " << layers[i].layerId;
            cout << " with size " << layers[i].nodes.size() << "\n";
        }
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
};

int main()
{
    cls

    net n({2, 2, 2});

    n.layers[0].setValueAll(1);
    n.layers[2].setBiasAll(0.5);

    n.connectLayers();
    n.passValues();

    n.printLayers();
    return 0;
}