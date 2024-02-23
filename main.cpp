#include "utils.h"




int main()
{
    net n({2, 2, 1});
    n.connectLayers();
    n.printLayers();

}