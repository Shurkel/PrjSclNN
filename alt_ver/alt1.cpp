#include <iostream>
#include <vector>


using namespace std;

int adjMatrix[10][10];
double weightMatrix[10][10];


class node
{
public:
    int id;
    double val;
    double bias;
    void connect(int nextID, double w=1.0)
    {
        adjMatrix[id][nextID] = 1;
        weightMatrix[id][nextID] = w;
    }
};



int main()
{
    node n1;
    n1.id = 1;
    n1.val = 0.5;
    n1.bias = 0.0;
    node n2;
    n2.id = 2;
    n2.val = 0.5;
    n2.bias = 0.0;
    n1.connect(2, 0.5);
    //print matrix;
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}