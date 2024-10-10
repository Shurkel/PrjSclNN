#include "../../experimental/utils/andreinet.h"
int main()
{
    system("cls");
    net n({2, 2, 1});
    n.setInputFromVector({0, 1});
    
    n.setActivateAll(1);
    n.noActivate(0); 
    
    n.setWeightAll(1); 
    n.setBiasAll(0);  
    n.passValues();
    n.printActualOutput();
    n.printLayers();
    n.layers[0].nodes[0].printNextNodes();
    n.disconnectLayers();
    
    n.clean();
    n.setInputFromVector({0, 1});
    n.passValues();
    n.layers[0].nodes[0].printNextNodes();
    n.printLayers();
    cout << u.sigmoid(0);
    
}