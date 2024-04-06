#include "layer.h"
// net
class net
{
public:
    vector<Layer> layers;
    vector<double> expected;
    vector<double> costs;

    net(vector<int> layerSizes)
    {
        l << "[+]Net created\n";
        l << "[+]Creating layers\n";
        for (int i = 0; i < layerSizes.size(); i++)
        {

            l << "|    [+]Layer created";
            layers.push_back(Layer(layerSizes[i])); // Create the layer first
            layers[i].setIdAll(i);                  // Then set its ID
            l << " at id " << layers[i].layerId;
            l << " with size " << layers[i].nodes.size() << "\n";
        }
        l << "-----";
        len len
    }

    // layer functions
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
        if (costs.empty())
        {
            cerr << (char)218 << "[x] Error: Costs vector is empty.\n"
                 << (char)192 << "Please use setExpected() before calling getCosts().\n";

            if (l.is_open())
            {
                l << "[x] Error: Costs vector is empty.\n"
                  << ">>Please use setExpected() before calling getCosts()\n";
                l.flush();
            }
        }
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
    void setValueAll(int layerId, double val)
    {
        layers[layerId].setValueAll(val);
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
        len for (int i = 0; i < layers.size(); i++)
        {
            layers[i].printLayer();
        }
    }

    // node functions
    void setWeight(Node *n1, Node *n2, double w)
    {
        n1->setWeight(n2, w);
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

    void backpropagation(double learningRate) {
        // ! needs work
        // Step 1: Calculate output layer deltas
        for (int i = 0; i < layers.back().nodes.size(); i++) {
            double output = layers.back().nodes[i].getValue();
            double expectedOutput = expected[i];
            double delta = output * (1 - output) * (expectedOutput - output);
            layers.back().nodes[i].delta = delta;
        }

        // Step 2: Calculate hidden layer deltas
        for (int i = layers.size() - 2; i > 0; i--) {
            for (int j = 0; j < layers[i].nodes.size(); j++) {
                double output = layers[i].nodes[j].getValue();
                double sum = 0.0;
                for (int k = 0; k < layers[i + 1].nodes.size(); k++) {
                    double weight = 0.0;
                    for (const auto& pair : layers[i + 1].nodes[k].nextNodes) {
                        if (pair.first == &layers[i].nodes[j]) {
                            weight = pair.second;
                            break;
                        }
                    }
                    sum += layers[i + 1].nodes[k].delta * weight;
                }
                double delta = output * (1 - output) * sum;
                layers[i].nodes[j].delta = delta;
            }
        }

        // Step 3: Update weights
        for (int i = 0; i < layers.size() - 1; i++) {
            for (int j = 0; j < layers[i].nodes.size(); j++) {
                for (int k = 0; k < layers[i + 1].nodes.size(); k++) {
                    double output = layers[i].nodes[j].getValue();
                    double delta = layers[i + 1].nodes[k].delta;
                    double weightDelta = learningRate * output * delta;
                    for (auto& pair : layers[i + 1].nodes[k].nextNodes) {
                        if (pair.first == &layers[i].nodes[j]) {
                            pair.second += weightDelta;
                            break;
                        }
                    }
                }
            }
        }
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
};
