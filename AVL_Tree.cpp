#include "AVL_Node.h"
#include <iostream>

using namespace std;

class AVL_Tree{
    private:
        AVL_Node* raiz;
    
    public:
        AVL_Tree(){
            raiz = nullptr;
        }
        /*
            Function to get the height of the tree
        */

        AVL_Node* getRaiz(){
            return raiz;
        }
        int height(AVL_Node *N){
            if (N == NULL)
                return 0;
            return N->height;
        }

        /*
            Function to create a new AVL_Node 
            Adding the newly created node as leaf node
        */

        AVL_Node* newAVL_Node(AVL_Node* par, int key){
            AVL_Node* node = new AVL_Node();
            node->key = key;
            node->left = NULL;
            node->right = NULL;
            node->height = 1;
            node->parent = par;
            if (!raiz){
                raiz = node;
            }
            return(node);
        }

        /*
            Function to update the heights
        */
        void update_height(AVL_Node* root){
            if (root != NULL) {
                int val = 1;
                if (root->left != NULL)
                    val = root->left->height + 1;
                if (root->right != NULL)
                    val = max(val, root->right->height + 1);
                root->height = val;
            }
        }

        /*
            Function for right rotation
        */
        AVL_Node *rightRotate(AVL_Node *y){
            AVL_Node *x = y->left;
            AVL_Node *T2 = x->right;

            if (x->right != NULL)
                x->right->parent = y;

        /*
            Perform rotation
        */
            y->left = T2;
            x->right = y;

            x->parent = y->parent;
            y->parent = x;

            if (x->parent != NULL && y->key < x->parent->key) {
                x->parent->left = x;
            }
            else{
                if (x->parent != NULL)
                    x->parent->right = x;
                else {
                    raiz = x;
                }
            }

            y = x;

        /*
            Update the heights
        */    
            update_height(y->left);
            update_height(y->right);
            update_height(y);
            update_height(y->parent);

        /*
            Return new root
        */
            return y;
        }

        /*
            Function for left rotation
        */
        AVL_Node *leftRotate(AVL_Node *x){
            AVL_Node *y = x->right;
            AVL_Node *T2 = y->left;

        /*
            Perform rotation
        */
            x->right = T2;

            if (y->left != NULL)
                y->left->parent = x;
            y->left = x;

            y->parent = x->parent;
            x->parent = y;

            if (y->parent != NULL && x->key < y->parent->key) {
                y->parent->left = y;
            }
            else{
                if (y->parent != NULL)
                    y->parent->right = y;
                else {
                    raiz = y;
                }
            }

        /*
            Update heights
        */

            update_height(x->left);
            update_height(x->right);
            update_height(x);
            update_height(x->parent);

        /*
            Return new root
        */
            return y;
        }

        /*
            Function to find the Balance factor of Nodes
        */
        int getBalance(AVL_Node *N){
            if (N == NULL)
                return 0;
            return height(N->left) - height(N->right);
        }


        /*
            Function to construct a tree.
        */
        AVL_Node* AVL_insert(int key){
            return AVL_insert(NULL, raiz, key);
        }

        AVL_Node* AVL_insert(AVL_Node *par, AVL_Node* root, int key){

        /*
            Perform the normal BST insertion
        */
            if (root == NULL)
                return(newAVL_Node(par, key));

            if (key < root->key)
                root->left = AVL_insert(root, root->left, key);

            else if (key > root->key)
                root->right = AVL_insert(root, root->right, key);
            else 
                return root;

        /*
            Step 1: Find the balance factor of parent\
        */
            int balance = getBalance(root);
        /*
            If this Node becomes unbalanced, all four cases are:
        */
        /*
            1. Left Left Case
        */
            if (balance > 1 && key < root->left->key)
                return rightRotate(root);

        /*
            2. Right Right Case
        */
            if (balance < -1 && key > root->right->key)
                return leftRotate(root);

        /*
            3. Left Right Case
        */
            if (balance > 1 && key > root->left->key){
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }

        /* 
            4. Right Left Case
        */
            if (balance < -1 && key < root->right->key){
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }

        /*
            Update the heights
        */
            update_height(root);

        /*
            Return the (unchanged) Node pointer
        */
            return root;
        }

        /*
            AVL Tree Traversal 
        */
        void PREORDER(AVL_Node *root){
            cout << "Node: " << root->key << ", Parent Node: ";

            if (root->parent != NULL)
                cout << root->parent->key << endl;
            else
                cout << "NULL" << endl;
            /* 
                Recur to the left subtree
            */
            if (root->left != NULL) {
                PREORDER(root->left);
            }

            /*
                Recur to the right subtree
            */
            if (root->right != NULL) {
                PREORDER(root->right);
            }
        }

        /*
            Function to find the AVL_Node with minimum key value
        */
        AVL_Node * minValueAVL_Node(AVL_Node* node){
            AVL_Node* current = node;
            /*
                Going to the left most side
            */
            while (current->left != NULL)
                current = current->left;
            return current;
        }

        AVL_Node* AVL_delete(int key){
            return AVL_delete(raiz, key);
        }
        /*
            Function to delete an AVL_Node with the given key from the subtree 
        */
        AVL_Node* AVL_delete(AVL_Node* root, int key){
        /*
            Perform normal BST deletion
        */
            if (root == NULL)
                return root;
        /*
            Find the node to be deleted
        */

        /*
            Left Side
        */
            if ( key < root->key )
                root->left = AVL_delete(root->left, key);

        /*
            Right Side
        */
            else if( key > root->key )
                root->right = AVL_delete(root->right, key);

        /*
            Root Node
        */
            else{
                if( (root->left != NULL) && (root->right == NULL) ){
                    AVL_Node *temp = root->left;

                    if (root->parent != NULL) {
                        if (root->parent->key < root->key)
                            root->parent->right = root->left;
                        else
                            root->parent->left = root->left;

                        /*
                            Update the height of root's parent
                        */
                        update_height(root->parent);
                    }
                    root->left->parent = root->parent;
                /*
                    One child case
                */
                *root = *temp; /*
                    Copy the contents of the non-empty child
                */
                delete(temp);

            } else if((root->left == NULL) && (root->right != NULL)){
                AVL_Node *temp = root->right;
                
                if (root->parent != NULL) {
                    if (root->parent->key < root->key)
                        root->parent->right = root->right;
                    else
                        root->parent->left = root->right;

                        /*
                            Update the height of root's parent
                        */
                    update_height(root->parent);
                }
                root->right->parent = root->parent;
                /*
                    One child case
                */
                *root = *temp; /*
                    Copy the contents of the non-empty child
                */
                delete(temp);
            } else if ((root->left == NULL) && (root->right == NULL)){ // case with no children
                cout << root->parent->key << " " << root->key << endl;
                if (root->parent->key < root->key) { // si estamos borrando uno de la derecha
                    root->parent->right = NULL;
                } else if (root->parent->key > root->key) { // si estamos borrando uno de la izquierda
                    root->parent->left = NULL;
                } else { //if (root->parent->key == root->key){
                    if (root->parent->left == root){
                        root->parent->left = NULL;
                    } else {
                        root->parent->right = NULL;
                    }
                }

                if (root->parent != NULL)
                    update_height(root->parent);
                AVL_Node *temp = root;
                root = NULL;
            } else{
                /*
                    AVL_Node with two children: Get the inorder successor (smallest in the right subtree)
                */
                AVL_Node* temp = minValueAVL_Node(root->right);
                /*
                    Copy the inorder successor's data to this AVL_Node
                */
                root->key = temp->key;  
                /*
                    Delete the inorder successor
                */
                root->right = AVL_delete(root->right,temp->key);
            }
        }

        /*
            If the tree had only one AVL_Node then return
        */
        if (root == NULL)
            return root;

        /*
            UPDATE HEIGHT OF THE CURRENT AVL_Node
        */
        update_height(root);

        /*
            GET THE BALANCE FACTOR OF THIS AVL_Node (to check whether this AVL_Node became unbalanced)
        */
        int balance = getBalance(root);

        /*
            If this AVL_Node becomes unbalanced, then there are 4 cases
        */

        /*
            Left Left Case
        */
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        /*
            Left Right Case
        */
        if (balance > 1 && getBalance(root->left) < 0){
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        /*
            Right Right Case
        */
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        /*
            Right Left Case
        */
        if (balance < -1 && getBalance(root->right) > 0){
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
        }

        // Print the tree
        void printTree(){
            printTree(raiz, "", true);
        }
        void printTree(AVL_Node *pRoot, string indent, bool last) {
            if (pRoot != nullptr) {
                cout << indent;
                if (last) {
                cout << "R----";
                indent += "   ";
                } else {
                cout << "L----";
                indent += "|  ";
                }
                cout << pRoot->key << endl;
                printTree(pRoot->left, indent, false);
                printTree(pRoot->right, indent, true);
            }
        }

        AVL_Node* searchI(int key){
            AVL_Node* nodePtr = raiz;
            while(nodePtr){
                if (key == nodePtr->key){
                    // si son iguales, no debemos realizar nada, entonces salimos.
                    return nodePtr;
                } else if (key < nodePtr->key){ // si es menor, vamos al subárbol izquierdo
                    nodePtr = nodePtr->left; // nos movemos el subarbol izquierdo;
                } else { 
                    nodePtr = nodePtr->right; // nos movemos el subarbol derecho;
                }
            }
            return NULL; // si no lo encontró, retorna NULL.
        }

        AVL_Node* searchR(AVL_Node *root, int key){
            if (root == NULL || root->key == key){
                return root; // casos base: Si la raíz es nula o si ya es la llave.
            }

            // Si la valor a buscar es mayor que el valor dado, nos movemos al subárbol derecho
            if (key > root->key){
                return searchR(root->right, key);
            }

            // Si el valor a buscar es menor que el valor dado, nos movemos al subárbol izquierdo
            return searchR(root->left, key);
        }
};


int main(){
    AVL_Tree *arbol = new AVL_Tree();
    AVL_Node *root = NULL;

/*
    Constructing tree 
*/
    root = arbol->AVL_insert(40);
    arbol->AVL_insert(20);
    arbol->AVL_insert(10);
    arbol->AVL_insert(30);
    arbol->AVL_insert(25);
    arbol->AVL_insert(60);
    arbol->AVL_insert(45);
    arbol->AVL_insert(42);
    arbol->AVL_insert(52);
    arbol->AVL_insert(50);
    arbol->AVL_insert(55);
    arbol->AVL_insert(75);
    arbol->AVL_insert(70);
    arbol->AVL_insert(80);
    arbol->AVL_insert(85);
    arbol->AVL_insert(10);
    arbol->printTree();


    AVL_Node *nodo = arbol->searchI(25);
    if (nodo){
        cout << "Se encontró el nodo con el valor " << nodo->key  << "." << endl;//nodo->parent->key << endl;
    } else {
        cout << "No se encontró el nodo." << endl;
    }

    nodo = arbol->searchR(arbol->getRaiz(), 85);
    if (nodo){
        cout << "Se encontró el nodo con el valor " << nodo->key  << "." << endl;//nodo->parent->key << endl;
    } else {
        cout << "No se encontró el nodo." << endl;
    }

    nodo = arbol->searchR(arbol->getRaiz(), 65);
    if (nodo){
        cout << "Se encontró el nodo con el valor " << nodo->key  << "." << endl;//nodo->parent->key << endl;
    } else {
        cout << "No se encontró el nodo." << endl;
    }
}
