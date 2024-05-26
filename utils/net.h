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
    //derivative of SSR
    double dSSR = 0.0;


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
    
    void clean()
    {
        for(int i = 0; i < layers.size(); i++)
        {
            layers[i].clean();
        }
    }

    void clean(int i)
    {
        for(int i = 0; i < layers.size(); i++)
        {
            if(layers[i].layerId == 0)
                continue;
            layers[i].clean();
        }
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
    
    double weight(int layerId, int nodeId, int nextLayerId, int nextNodeId)
    {
        return layers[layerId].nodes[nodeId].weight(&layers[nextLayerId].nodes[nextNodeId]);
    }
    
    double weight(Node *node, Node *nextNode)
    {
        return node->weight(nextNode);
    }

    void setExpected(vector<double> expectedValues)
    {
        expected.clear();
        for (int i = 0; i < layers.back().nodes.size(); i++)
        {
            expected.push_back(expectedValues[i]);
        }
    }
    
    void getCosts()
    {
        costs.clear();
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
        for(int i = 0; i < layers.back().nodes.size(); i++)
        {
            costs.push_back(layers.back().nodes[i].value - expected[i]);
            
            /* cout << "costs.push_back ( layers.back().nodes[i].value - expected[i] ) " << "\n";
            cout << "layers.back().nodes[i].value: " << layers.back().nodes[i].value << "\n";
            cout << "expected[i]: " << expected[i] << "\n"; */
        }
        
    }
    
    void getSSR()
    {
        clearCosts();
        getCosts();
        for (int i = 0; i < costs.size(); i++)
        {
            SSR += pow(costs[i], 2);
            dSSR += -2 * costs[i];
            

            //cout << "SSR += pow(costs[i], 2) "<< "\n";
            //cout << "costs[i]: " << costs[i] << "\n";
        }
        
    }

    void clearCosts()
    {
        costs.clear();
    }
    
    void clearSSR()
    {
        SSR = 0.0;
        dSSR = 0.0;
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
    
    void setInputFromVector(vector<double> values)
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

    void noActivate(int layerId, int nodeId)
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

    void logLayers()
    {
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i].logLayer();
        }
    }
    // node functions
    void setWeight(int layerID, int nodeID, int nextLayerID, int nextNodeID, double w)
    {
        layers[layerID].nodes[nodeID].setWeight(nextNodeID, nextLayerID, w);
    }

    void setBias(int layerID, int nodeID, double b)
    {
        layers[layerID].nodes[nodeID].setBias(b);
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

    void setBiasAll(double b)
    {
        for (int i = 0; i < layers.size(); i++)
        {
            for (int j = 0; j < layers[i].nodes.size(); j++)
            {
                layers[i].nodes[j].setBias(b);
            }
        }
    }

    void ranomiseAllWeights()
    {
        // ! not working
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

    void printSSR()
    {
        cout << "\n[+]SSR: " << SSR;
        cout.flush();}

    void applyGradient(int learningRate)
    {
        for (int i = 0; i < layers.size(); i++)
        {
            for (int j = 0; j < layers[i].nodes.size(); j++)
            {
                for(int k = 0; k < layers[i].nodes[j].next.size(); k++)
                {
                    layers[i].nodes[j].next[k].weight = layers[i].nodes[j].next[k].gradient * learningRate;
                }
                layers[i].nodes[j].bias -= layers[i].nodes[j].biasGradient * learningRate;
            }
        }
    }



    void getGradients(pair<vector<double>, vector<double>> trainingData, double learningRate, int inputIndex)
    {
        const double h = 0.0001;
        clean();
        setInputFromVector({trainingData.first[inputIndex]});
        setExpected({trainingData.second[inputIndex]});
        passValues();
        getSSR();
        double oldSSR = SSR;
        //iterate trough layers
        for(int i = 0; i < layers.size(); i++)
        {
            for(int j = 0; j < layers[i].nodes.size(); j++)
            {
                if(i < layers.size())
                {
                    for(int k = 0; k < layers[i].nodes[j].next.size(); k++)
                    {
                        layers[i].nodes[j].next[k].weight += h;
                        clean(0);
                        passValues();
                        getSSR();
                        cout << "Old SSR: " << oldSSR << "\n";
                        cout << "New SSR: " << SSR << "\n";
                        double deltaCost = SSR - oldSSR;
                        layers[i].nodes[j].next[k].weight -= h;
                        layers[i].nodes[j].next[k].gradient = deltaCost / h;
                    }
                }
                layers[i].nodes[j].bias += h;
                clean(0);
                passValues();
                getSSR();
                double deltaCost = SSR - oldSSR;
                layers[i].nodes[j].bias -= h;
                layers[i].nodes[j].biasGradient = deltaCost / h;
                
            }
        }
        
    }



    void backPropagate(pair<vector<double>, vector<double>> trainingData, int epochs, double learningRate)
    {
        //passValues();
        //getSSR();
        //getCosts
        for(int i = 0; i < epochs; i++)
        {
            for(int j = 0; j < trainingData.first.size(); j++)
            {
                
                

                //https://www.youtube.com/watch?v=hfMk-kjRv4c&t=1397s&ab_channel=SebastianLague
                getGradients(trainingData, learningRate, j);
                applyGradient(learningRate);
                //printSSR();
                clearCosts();
                clearSSR();
            }
            
        }
        

        
        
        




        
        /* double dSSR_dBias = dSSR;
        double stepSize = dSSR_dBias * learningRate;
        layers.back().nodes[0].bias += stepSize;

        double dSSR_dWeight = dSSR * layers[1].nodes[0].value;
        stepSize = dSSR_dWeight * learningRate;
        layers[1].nodes[0].next[0].weight += stepSize;

        cout << "\nSSR: " << SSR;
        cout << "\nBias " << layers.back().nodes[0].bias;
        cout << "\nWeight " << layers[1].nodes[0].next[0].weight;
        //cout << "slope: " << slope << "\n";
        //cout << "stepSize: " << stepSize << "\n";
        //cout << "Old bias: " << layers.back().nodes[0].bias << "\n";
        
        //cout << "New bias: " << layers.back().nodes[0].bias << "\n"; */
        
    }



};
