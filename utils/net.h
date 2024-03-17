#include "layer.h"
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
    void setValue(int layerId, int nodeId, double val)
    {
        layers[layerId].setValue(nodeId, val);
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
