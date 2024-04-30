#include "layer.h"
// net
class net
{
public:
    vector<Layer> layers;
    vector<double> expected;
    vector<double> costs;
    bool log = true;
    double cost = 0.0;
    //sum of squared residuals
    double SSR = 0.0;



    net(vector<int> layerSizes)
    {
        if(log)
        {
            l << "[+]Net created\n";
            l << "[+]Creating layers\n";
        }
        
        for (int i = 0; i < layerSizes.size(); i++)
        {

            
            layers.push_back(Layer(layerSizes[i])); // Create the layer first
            layers[i].setIdAll(i);     
            if(log)
            {
                l << "|    [+]Layer created";             // Then set its ID
                l << " at id " << layers[i].layerId;
                l << " with size " << layers[i].nodes.size() << "\n";
            }
            
            
        }
        
        clearCosts();
    }

    // layer functions
    void logNet()
    {
        if(log)
            log = false;
        else
            log = true;
    }
    


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
    
    void setExpectedFromVector(vector<double> expectedValues)
    {
        for (int i = 0; i < layers.back().nodes.size(); i++)
        {
            expected.push_back(expectedValues[i]);
        }
    }
    
    void getCosts()
    {
        
        if (expected.empty())
        {
            cerr << (char)218 << "[x] Error: Costs vector is empty.\n"
            << (char)192 << "Please use setExpected() before calling getCosts().\n";

            if (l.is_open())
            {
                l << "[x] Error: Costs vector is empty.\n"
                << ">>Please use setExpected() before calling getCosts()\n";
                l.flush();
            }
            return;
        }
        for (int i = 0; i < layers.back().nodes.size(); i++)
        {
            costs.push_back(expected[i] - layers.back().nodes[i].value);
            layers.back().nodes[i].error = costs[i];
        }
        
    }
    
    void getSSR()
    {
        for (int i = 0; i < costs.size(); i++)
        {
            SSR += pow(costs[i], 2);
            //cout << "SSR += pow(costs[i], 2) "<< "\n";
            //cout << "costs[i]: " << costs[i] << "\n";
        }
    }

    void clearCosts()
    {
        costs.clear();
    }
    
    void logCosts()
    {
        l << "\n\n[+]Costs: ";
        for (int i = 0; i < costs.size(); i++)
        {
            l << costs[i] << " ";
        }
        len
    }
    
    void printCosts()
    {
        cout << "\n[+]Costs: ";
        for (int i = 0; i < costs.size(); i++)
        {
            cout << costs[i] << " ";
        }
        cout << "\n";
        cout.flush();
    }
    
    void printExpected()
    {
        cout << "\n[+]Expected: ";
        for (int i = 0; i < expected.size(); i++)
        {
            cout << expected[i] << " ";
        }
        cout << "\n";
        cout.flush();
    }

    void printActualOutput()
    {
        cout << "\n[+]Actual output: ";
        for (int i = 0; i < layers.back().nodes.size(); i++)
        {
            cout << layers.back().nodes[i].value << " ";
        }
        cout << "\n";
        cout.flush();
    }
    
    void setValueAll( double val)
    {
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i].setValueAll(val);
        }
    }
    
    void setValue(int layerId, int nodeId, double val)
    {
        layers[layerId].setValue(nodeId, val);
    }
    
    void setValueFromVector(vector<double> values)
    {
        layers[0].setValueFromVector(values);
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

    void noActivate(int nodeId, int layerId)
    {
        layers[layerId].noActivate(nodeId);
    }

    void noActivateAll()
    {
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i].noActivateAll();
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
        cout << (char)218 << "Layer count: " << layers.size() << '\n';
        cout << (char)195 << "SSR: " << SSR << '\n';
        cout << (char)195 << "Layer | Size\n";

        cout << char(195);
        cout << "  " << layers[0].layerId << "   |    " << layers[0].nodes.size() << "\n";
        
        for(int i = 1; i < layers.size()-1; i++)
        {
            cout << char(195) << "  ";
            cout << layers[i].layerId << "   |    " << layers[i].nodes.size() << "\n";
        }

        cout << char(192);
        cout << "  " << layers.back().layerId << "   |    " << layers.back().nodes.size();
        cout.flush();
        
    }
    
    void printLayers()
    {
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i].printLayer();
        }
    }

    // node functions
    void setWeight(int nodeID, int layerID, int nextNodeID, int nextLayerID, double w)
    {
        layers[layerID].nodes[nodeID].setWeight(nextNodeID, nextLayerID, w);
    }

    void setBias(int nodeID, int layerID, double w)
    {
        layers[layerID].nodes[nodeID].setBias(w);
    }   
    
    void printNextNodes(int layerId, int nodeId)
    {
        layers[layerId].nodes[nodeId].printNextNodes();
    }

    // net functions
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

    void updateGradient()
    {
        passValues();

        //update output layer gradient
        
    }

    void setWeightAll(double w)
    {
        for (int i = 0; i < layers.size(); i++)
        {
            for (int j = 0; j < layers[i].nodes.size(); j++)
            {
                layers[i].nodes[j].setWeightAll(w);
            }
        }
    }

    void ranomiseAllWeights()
    {
        for (int i = 0; i < layers.size(); i++)
        {
            for (int j = 0; j < layers[i].nodes.size(); j++)
            {
                layers[i].nodes[j].randomiseWeights();
            }
        }
    }
    void printNodeDetails(int nodeId, int layerId)
    {
        layers[layerId].nodes[nodeId].printDetails();
    }
};
