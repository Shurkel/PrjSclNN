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
    int id = 0;
    int layerId = 0;
    vector<Node *> nextNodes;
    Node(double val) : value(val) {}

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

            nextNodes[i]->setValue(value + nextNodes[i]->getValue());
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
            cout << " size of layer " << i << " is " << layers[i].nodes.size() << "\n";
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
    //create a network of 3 layers of 2 nodes
    /* net n1({2, 2, 2});
    n1.connectLayers();
    n1.layers[0].setValueAll(1);
    n1.passValues();
    en
    n1.printLayers(); */
    
    Layer l1(2);
    l1.setIdAll(1);
    l1.setValueAll(1);
    Layer l2(2);
    l2.setIdAll(2);
    l1.connect(&l2);
   
    l1.passValues();
    l1.printLayer();
    l2.printLayer();
    l1.nodes[0].printNextNodes();en
    l1.disconnect(&l2);
    l1.nodes[0].printNextNodes();
    return 0;
}