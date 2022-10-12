#include "ArbolAVL.h"
#include <iostream>

int main(){
    ArbolAVL *arbol = new ArbolAVL();

    arbol->insert(40);
    arbol->insert(20);
    arbol->insert(80);
    arbol->insert(10);
    arbol->insert(30);
    //arbol->insert(50);
    arbol->printTree(arbol->getRoot(), "", true);
}