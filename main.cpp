#include "ArbolAVL.h"
#include <iostream>

int main(){
    ArbolAVL *arbol = new ArbolAVL();

    /*arbol->insert(40);
    arbol->insert(20);
    arbol->insert(80);
    arbol->insert(10);
    arbol->insert(30);
    arbol->insert(50);
    arbol->insert(90);
    arbol->insert(45);
    arbol->insert(75);
    arbol->printTree(arbol->getRoot(), "", true);
    arbol->insert(60);
    arbol->printTree(arbol->getRoot(), "", true);*/

    /*arbol->insert(33);
    arbol->insert(13);
    arbol->insert(53);
    arbol->insert(61);
    arbol->insert(11);
    arbol->insert(21);
    arbol->insert(8);
    arbol->insert(9);*/

    /*arbol->insert(13);
    arbol->insert(10);
    arbol->insert(15);
    arbol->insert(5);
    arbol->insert(11);
    arbol->insert(16);
    arbol->insert(4);
    arbol->insert(8);
    arbol->insert(3);*/

    arbol->insert(13);
    arbol->insert(10);
    arbol->insert(15);
    arbol->insert(5);
    arbol->insert(1);
    arbol->insert(16);
    arbol->insert(4);
    arbol->printTree(arbol->getRoot(), "", true);
    arbol->insert(6);
    arbol->printTree(arbol->getRoot(), "", true);
    arbol->insert(7);
    arbol->printTree(arbol->getRoot(), "", true);
}