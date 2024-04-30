#include "node.h"

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

    void noActivate(int nodeId)
    {
        nodes[nodeId].noActivate();
    }
    void noActivateAll()
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes[i].noActivate();
        }
    }
    void setActivateAll(int function)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes[i].setActivate(function);
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
    void setValue(int nodeId, double val)
    {
        nodes[nodeId].setValue(val);
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
    void logLayer()
    {
        
        len len
        l << "---------------------------\n";
        l << "| LayerID " << layerId << "                |\n";
        l << "---------------------------\n";
        l << "| Node Id | Value | Bias   |\n";
        l << "---------------------------\n";
        for (int i = 0; i < nodes.size(); i++)
        {
            l << "|  " << nodes[i].getId() << " ------> " << nodes[i].getValue() << " ------> " << nodes[i].bias << " |" << "\n";
        }
        l << "---------------------------\n";
        len 
    }
    void printLayer()
    {
        
        
        cout << "---------------------------\n";
        cout << "| LayerID " << layerId << "                |\n";
        cout << "---------------------------\n";
        cout << "| Node Id | Value | Bias   |\n";
        cout << "---------------------------\n";
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << "|  " << nodes[i].getId() << " ------> " << nodes[i].getValue() << " ------> " << nodes[i].bias << " |" << "\n";
        }
        cout << "---------------------------\n";
        en 
    }

    void printDetails(int nodeId)
    {
        nodes[nodeId].printDetails();
    }
};
