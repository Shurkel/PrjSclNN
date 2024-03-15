//test evolution 1

#include <iostream>
#include "utils.h"
#include <vector>

using namespace std;









int main() {
    cls
    setLogFile("logs.out");
    net initialNet({2, 2, 1});
    initialNet.loggingGlobal();
    initialNet.setActivateAll(0);
    initialNet.setWeightsAll(1);
    

    vector<net> generation;
    int generationSize = 10;
    for(int i = 0; i < generationSize; i++){
        generation.push_back(initialNet);
    }
    
    return 0;
}