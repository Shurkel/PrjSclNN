
#include "timer.h"

class Node
{

public:
    double value;
    double bias = 0.0;
    double gradient = 0.0;
    int id = 0;
    int layerId = 0;
    bool log = false;
    bool yesActivate = true;
    int activationFunction = 0;
    

    vector<pair<Node *, double>> nextNodes;//with weights
    double delta = 0.0;
    double error = 0.0;

    

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
        // * * add more functions here
        //relu
        if (function == 0)
            value = u.relu(value);
        //sigmoid
        else if (function == 1)
            value = u.sigmoid(value);
        //softmax
        else if (function == 2)
            value = u.softmax(value);
    }
    void noActivate()
    {
        yesActivate = false;
        if(log)
        {
            l << "[-] Node " << id << " deactivated\n";
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
    void setWeight(int nextNodeID, int nextLayerID, double w)
    {
        nextNodes[nextNodeID].second = w;
        if(log)
        {
            l << "[+] Weight set to " << w << " for node " << nextNodes[nextNodeID].first->id << " from node " << id << "\n";
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
    double getDelta(double expected)
    {
        // ! not verified
        delta = value * (1 - value) * (expected - value);
        return delta;
    }

    void setValue(double val)
    {
        value = val;
        if(log)
            l << "[+] Node " << id << " value set to " << val << "\n";
    }
    
    void setBias(double b)
    {
        bias = b;
        if(log)
            l << "[+] Node " << id << " bias set to " << b << "\n";
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
        TextTable t('-', '|', '+');
        t.add("LayerID");
        t.add("nodeID");
        t.add("weight");
        t.endOfRow();
        cout << "[x] Node " << id << " at layer " << layerId << " is connected to nodes:\n";
        for (int i = 0; i < nextNodes.size(); i++)
        {
            t.add(to_string(nextNodes[i].first->layerId));
            t.add(to_string(nextNodes[i].first->id));
            t.add(to_string(nextNodes[i].second));
            t.endOfRow();   
        }
        t.setAlignment(2, TextTable::Alignment::RIGHT);
        cout << t;
        en
    }
    void randomiseWeights()
    {
        for (int i = 0; i < nextNodes.size(); i++)
        {
            nextNodes[i].second = u.randomDouble(-1, 1);
        }
    }
    void printDetails()
    {
        cout 
        << (char)218 << "Node: " << id << '\n' 
        << (char)195 << " Value: " << value << '\n'
        << (char)195 << " Layer: " << layerId << '\n'
        << (char)195 << " Bias: " << bias << "\n"
        << (char)195 << " Activation function: " << activationFunction << "\n"
        << (char)195 << " Logging: " << log << "\n"
        << (char)195 << " Delta: " << delta << "\n"
        << (char)195 << " Error: " << error << "\n"
        << (char)192 << " Next nodes: \n";
        cout << (char)9 << (char)218 << "Node " << nextNodes[0].first->id << " -->  weight " << nextNodes[0].second;
        en
        for (int i = 1; i < nextNodes.size(); i++)
        {
            
            cout << (char)9 << (char)195 << "Node " << nextNodes[i].first->id << " -->  weight " << nextNodes[i].second;

            en
        }
        cout.flush();
    }


    
};