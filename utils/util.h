#include "includes.h"
class util
{
public:
    double relu(double x)
    {
        if (x > 0)
        {
            return x;
        }
        else
        {
            return 0;
        }
    }
    double sigmoid(double x)
    {
        return 1 / (1 + exp(-x));
    }
    void logVector(vector<double> v)
    {
        for (int i = 0; i < v.size(); i++)
        {
            l << v[i] << " ";
        }
        len
    }
    void logTime()
    {
        //curent time and date
        l << "Last Build: " << __TIME__ << ", " << __DATE__ << "\n";
    }
    
    
}u;