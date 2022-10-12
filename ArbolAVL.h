#ifndef ARBOLAVL

#define ARBOLAVL 1

#include "NodeAVL.h"
#include <iostream>

using namespace std;

class ArbolAVL {
    private:
        NodeAVL<int>* root;
    public:
        ArbolAVL(){
            root = NULL;
        }

        bool isEmpty(){
            return !root; // si no hay un hay un nodo raíz, se retorna verdadero.
        }

        NodeAVL<int>* getRoot(){
            return root;
        }

        void updateFE(NodeAVL<int>* pNode){
            NodeAVL<int>* nodePtr = pNode;
            NodeAVL<int>* parent = nodePtr->getParent();
            while(parent){ // mientras el puntero no sea nulo
                if (*nodePtr->getData() < *parent->getData()){ // si el hijo es a la izquierda
                    if (parent->decFE() == -2){
                        //rotacion
                        if (nodePtr->getFE() <= 0){
                            rightRotate(parent);
                            //rotacion a la derecha
                        } else {
                            leftRotate(parent);
                            rightRotate(nodePtr);
                            //rotacion izquierda-derecha
                        }
                        return;
                    }
                } else {
                    if (parent->incFE() == 2){
                        //rotacion
                        if (nodePtr->getFE() >= 0){
                            leftRotate(parent);
                            //rotacion a la izquierda
                        } else {
                            rightRotate(parent);
                            leftRotate(parent);
                            //rotacion dercha-izquierda
                        }
                        return;
                    }
                }
                nodePtr = parent;
                parent = nodePtr->getParent();
            }
        }

        void rightRotate(NodeAVL<int> *pNode){
            NodeAVL<int> *parent = pNode->getParent();
            NodeAVL<int> *child = pNode->getLeft();
            if (parent){
                parent->setLeft(child);
            } else {
                root = child;  
            }
            NodeAVL<int> *tempNode = child->getRight();
            child->setRight(pNode);
            pNode->setLeft(tempNode);
            calculateFE(pNode); // recalculamos los factores de equilibrio
            calculateFE(pNode->getParent());
        }

        void leftRotate(NodeAVL<int> *pNode){
            NodeAVL<int> *parent = pNode->getParent();
            NodeAVL<int> *child = pNode->getRight();
            if (parent){
                parent->setRight(child);
            } else {
                root = child;  
            }
            NodeAVL<int> *tempNode = child->getLeft();
            child->setLeft(pNode);
            pNode->setRight(tempNode);
            calculateFE(pNode); // recalculamos los factores de equilibrio
            calculateFE(pNode->getParent());
        }

        void calculateFE(NodeAVL<int> *pNode){
            int left = 0;
            int right = 0;
            if (pNode->getLeft()){
                left = pNode->getLeft()->getFE();
            }
            if (pNode->getRight()){
                right = pNode->getRight()->getFE();
            }
            pNode->setFE(right - left);
        }

        // Print the tree
        void printTree(NodeAVL<int> *root, string indent, bool last) {
            if (root != nullptr) {
                cout << indent;
                if (last) {
                cout << "R----";
                indent += "   ";
                } else {
                cout << "L----";
                indent += "|  ";
                }
                cout << *root->getData() << endl;
                printTree(root->getLeft(), indent, false);
                printTree(root->getRight(), indent, true);
            }
        }

        void insert(int pNum){
            if (!isEmpty()){
                bool inserted = false;
                NodeAVL<int> *nodePtr = root;

                while (!inserted){
                    if (pNum < *nodePtr->getData()){ // si es menor, vamos al subárbol izquierdo
                        if (!nodePtr->getLeft()){ // si no tiene nodo hijo izquierdo
                            int* data = (int*) malloc(sizeof(int));
                            *data = pNum;
                            NodeAVL<int>* newNode = new NodeAVL<int>(data);
                            newNode->setParent(nodePtr);
                            nodePtr->setLeft(newNode); // ponemos el hijo izquierdo como el nuevo nodo.
                            // si ingresamos un nodo a la izquierda, el FE del camino se incrementa
                            updateFE(newNode); // recalculamos los factores de equilibrio y realizamos la rotación
                            inserted = true;
                        } else {
                            nodePtr = nodePtr->getLeft(); // nos movemos el subarbol izquierdo;
                        }
                    } else if (pNum > *nodePtr->getData()) { // si es mayor, vamos al subárbol derecho
                        if (!nodePtr->getRight()){ // si no tiene nodo hijo derecho
                            int* data = (int*) malloc(sizeof(int));
                            *data = pNum;
                            NodeAVL<int>* newNode = new NodeAVL<int>(data);
                            newNode->setParent(nodePtr);
                            nodePtr->setRight(newNode); // ponemos el hijo derecho como el nuevo nodo.
                            // si ingresamos un nodo a la derecha, el FE del camino se incrementa
                            updateFE(newNode); // recalculamos los factores de equilibrio y realizamos la rotación
                            inserted = true;
                        } else {
                            nodePtr = nodePtr->getRight(); // nos movemos el subarbol izquierdo;
                        }
                    } else { // si son iguales, no debemos realizar nada, entonces salimos
                        return;
                    }
                }

            } else {
                int* data = (int*) malloc(sizeof(int));
                *data = pNum;
                root = new NodeAVL<int>(data);
            }
        }

};

#endif