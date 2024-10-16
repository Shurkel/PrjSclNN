
#include "timer.h"



class Node
{

public:
    struct nextNodes
    {
        Node *node;
        double weight;
    };
    vector<nextNodes> next;//<node, weight>
    double value;
    double unactivatedValue;
    double bias = 0.0;
    int id = 0;
    int layerId = 0;
    bool yesActivate = true;
    int activationFunction = 0;
    

    
    
    

    Node(double val = 0.0, double b = 0.0)
    {
        value = val;
        bias = b;
    }

    //////////////////////////
    
    // * *NODE FUNCTIONS
    double getValue()
    {
        return value;
    }
    void setValue(double val)
    {
        value = val;
        unactivatedValue = val;
    }
    
    int getId()
    {
        return id;
    }
    void setId(int id)
    {
        this->id = id;
    }

    double getBias()
    {
        return bias;
    }
    void setBias(double b)
    {
        bias = b;
    }

    void clean()
    {
        value = 0;
    }
    
    double weight(int nextNodeID)
    {
        return next[nextNodeID].weight;
    }
    double weight(Node *nextNode)
    {
        for (int i = 0; i < next.size(); i++)
        {
            if (next[i].node == nextNode)
            {
                return next[i].weight;
            }
        }
        return 0;
    }
    void randomiseWeights()
    {
        for (int i = 0; i < next.size(); i++)
        {
            next[i].weight = u.randomDouble(-1, 1);
        }
    }

    int getActivate()
    {
        return activationFunction;
    }
    void setActivate(int function)
    {
        activationFunction = function;
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
        if(yesActivate)
            yesActivate = false;
        else
            yesActivate = true;
    }
    

    void setWeight(int nextNodeID, int nextLayerID, double w)
    {
        next[nextNodeID].weight = w;
    }
    void setWeightAll(double w)
    {
        for (int i = 0; i < next.size(); i++)
        {
            next[i].weight = w;
        }
    }
    double getWeight(int nextNodeID)
    {
        return next[nextNodeID].weight;
    }

    void passValues()
    {
        value += bias;
        unactivatedValue = value;
        
        if(yesActivate)
        {
            //cout << "Activating node " << id << " with value " << value << "\n";
            activate(activationFunction);
        }    
            
        for (int i = 0; i < next.size(); i++)
        {

            next[i].node->value = value*next[i].weight + next[i].node->getValue();// next node value += this value * weight 
        }
        

    }
    
    void connect(Node *nextNode, double w=1.0)
    {
        next.push_back({nextNode, w});
    }
    void disconnect(Node *nextNode)
    {
        for (int i = 0; i < next.size(); i++)
        {
            if (next[i].node == nextNode)
            {
                next.erase(next.begin() + i);
            }
        }
    }
    void disconnectAll()
    {
        next.clear();
    }
    
    vector<nextNodes> getNextNodes()
    {
        return next;
    }
    void setNextNodes(vector<nextNodes> next)
    {
        this->next = next;
    }
    
    void printNextNodes()
    {
        TextTable t('-', '|', '+');
        t.add("LayerID");
        t.add("nodeID");
        t.add("weight");
        t.endOfRow();
        cout << "[x] Node " << id << " at layer " << layerId << " is connected to nodes:\n";
        for (int i = 0; i < next.size(); i++)
        {
            t.add(to_string(next[i].node->layerId));
            t.add(to_string(next[i].node->id));
            t.add(to_string(next[i].weight));
            t.endOfRow();   
        }
        t.setAlignment(2, TextTable::Alignment::RIGHT);
        cout << t;
        en
    }
    void printDetails()
    {
        cout 
        << '\n'
        << (char)218 << "Node: " << id << '\n' 
        << (char)195 << " Value: " << value << '\n'
        << (char)195 << " Unactivated value: " << unactivatedValue << '\n'
        << (char)195 << " Layer: " << layerId << '\n'
        << (char)195 << " Bias: " << bias << "\n"
        << (char)195 << " Activation function: " << activationFunction << "\n"
        << (char)192 << " Next nodes: \n";
        if(next.size() != 0)
        {
            cout << (char)9 << (char)218 << "Node " << next[0].node->id << " -->  weight " << next[0].weight;
            en
            for (int i = 1; i < next.size(); i++)
            {
                cout << (char)9 << (char)195 << "Node " << next[i].node->id << " -->  weight " << next[i].weight;
                en
            }
        }
        cout.flush();
    }

};