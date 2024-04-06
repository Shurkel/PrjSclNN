
#include "timer.h"

class Node
{

public:
    double value;
    double bias = 0.0;
    double delta;
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
    
    // * *NODE FUNCTIONS
    
    void setActivate(int function)
    {
        activationFunction = function;
        if(log)
        {
            l << "[+] Activation function set to " << function << " for node " << id << "\n";
        }
    }
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
            //cout << "Activating node " << id << " with value " << value << "\n";
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
    void randomiseWeights()
    {
        for (int i = 0; i < nextNodes.size(); i++)
        {
            nextNodes[i].second = u.randomDouble(-1, 1);
        }
    }
};