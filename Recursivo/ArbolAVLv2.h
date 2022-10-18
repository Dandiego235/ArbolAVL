// C++ program to delete a node from AVL Tree

#include "NodeAVLv2.h"
#include <iostream>

using namespace std;

class ArbolAVL{
    private:
        NodeAVL<int> *root;

    public:
        ArbolAVL(){
            root = nullptr;
        }

        NodeAVL<int> *getRoot(){
            return root;
        }
        
        // A utility function to get height
        // of the tree
        int height(NodeAVL<int> *N)
        {
            if (N == nullptr)
                return 0;
            return N->height;
        }
        
        // A utility function to get maximum
        // of two integers
        int max(int a, int b){
            return (a > b)? a : b;
        }
        
        /* Helper function that allocates a
        new node with the given key and
        nullptr left and right pointers. */
        NodeAVL<int>* newNode(int key){   
            int* data = new int(key);
            NodeAVL<int>* node = new NodeAVL<int>(data);
            if (!root){
                root = node; // si es el primer nodo generado, lo hacemos la raiz
            }
            return(node);
        }
        
        // A utility function to right
        // rotate subtree rooted with y
        // See the diagram given above.
        /*   T1, T2, T3 and T4 are subtrees.
                     z                                     Z
                    / \                                  /   \
                  y   T4      Right Rotate (z)         x     T4
                / \          - - - - - - - - ->      /  \   
               x   T3                               T1  y
             / \                                       / \
            T1 T2                                     T2 T3
        */
        NodeAVL<int> *rightRotate(NodeAVL<int> *y){
            NodeAVL<int> *z = y->parent;
            NodeAVL<int> *x = y->left;
            NodeAVL<int> *T2 = x->right;

        
            // Perform rotation
            x->right = y;
            y->left = T2;
            x->parent = z;
            y->parent = x;
            if (!z){ // Si el padre de y es nulo, es la raiz, entonces x tiene que ser la nueva raiz
                root = x;
            }
            if (T2){
                T2->parent = y;
            }
            // Update heights
            y->height = max(height(y->left),
                            height(y->right)) + 1;
            x->height = max(height(x->left),
                            height(x->right)) + 1;
        
            // Return new root
            return x;
        }
        
        // A utility function to left
        // rotate subtree rooted with x
        // See the diagram given above.
        /*        z                                z
                /  \                            /   \ 
            T1   y     Left Rotate(z)      T1     x
                /  \   - - - - - - - ->           / \
                T2   x                            y  T4
                    / \                          / \
                T3  T4                        T2 T3
        
        */
        NodeAVL<int> *leftRotate(NodeAVL<int> *y){
            NodeAVL<int> *z = y->parent;
            NodeAVL<int> *x = y->right;
            NodeAVL<int> *T3 = x->left;
        
            // Perform rotation
            x->left = y;
            y->right = T3;
            x->parent = z;
            y->parent = x;
            if (!z){ // Si el padre de y es nulo, es la raiz, entonces x tiene que ser la nueva raiz
                root = x;
            }
            if (T3){
                T3->parent = y;
            }
            // Update heights
            x->height = max(height(x->left),
                            height(x->right)) + 1;
            y->height = max(height(y->left),
                            height(y->right)) + 1;
        
            // Return new root
            return y;
        }
        
        // Get Balance factor of node N
        int getBalance(NodeAVL<int> *N){
            if (N == nullptr)
                return 0;
            return height(N->left) -
                height(N->right);
        }
        
        NodeAVL<int>* insert(NodeAVL<int>* node, int key){
            /* 1. Perform the normal BST rotation */
            if (node == nullptr)
                return(newNode(key));
        
            if (key < *node->data){
                node->left = insert(node->left, key);
                node->left->parent = node; // enlazamos el nuevo nodo con su padre.
            } else if (key > *node->data) {
                node->right = insert(node->right, key);
                node->right->parent = node; // enlazamos el nuevo nodo con su padre.
            } else { // Equal keys not allowed
                return node;
            }
            

            /* 2. Update height of this ancestor node */
            node->height = 1 + max(height(node->left),
                                height(node->right));
        
            /* 3. Get the balance factor of this
                ancestor node to check whether
                this node became unbalanced */
            int balance = getBalance(node);
        
            // If this node becomes unbalanced,
            // then there are 4 cases
        
            // Left Left Case
            if (balance > 1 && key < *node->left->data)
                return rightRotate(node);
        
            // Right Right Case
            if (balance < -1 && key > *node->right->data)
                return leftRotate(node);
        
            // Left Right Case
            if (balance > 1 && key > *node->left->data)
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        
            // Right Left Case
            if (balance < -1 && key < *node->right->data)
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        
            /* return the (unchanged) node pointer */
            return node;
        }
        
        /* Given a non-empty binary search tree,
        return the node with minimum key value
        found in that tree. Note that the entire
        tree does not need to be searched. */
        NodeAVL<int> * minValueNode(NodeAVL<int>* node){
            NodeAVL<int>* current = node;
        
            /* loop down to find the leftmost leaf */
            while (current->left != nullptr)
                current = current->left;
        
            return current;
        }
        
        // Recursive function to delete a node
        // with given key from subtree with
        // given root. It returns root of the
        // modified subtree.
        NodeAVL<int>* deleteNode(NodeAVL<int>* pRoot, int key){
            
            // STEP 1: PERFORM STANDARD BST DELETE
            if (pRoot == nullptr)
                return pRoot;
        
            // If the key to be deleted is smaller
            // than the root's key, then it lies
            // in left subtree
            if ( key < *pRoot->data )
                pRoot->left = deleteNode(pRoot->left, key);
        
            // If the key to be deleted is greater
            // than the root's key, then it lies
            // in right subtree
            else if( key > *pRoot->data )
                pRoot->right = deleteNode(pRoot->right, key);
        
            // if key is same as root's key, then
            // This is the node to be deleted
            else
            {
                // node with only one child or no child
                if( (pRoot->left == nullptr) || (pRoot->right == nullptr) ) {
                    NodeAVL<int> *temp = pRoot->left ? pRoot->left : pRoot->right;
        
                    // No child case
                    if (temp == nullptr)
                    {
                        temp = pRoot;
                        pRoot = nullptr; // lo desconectamos del arbol
                    }
                    else // One child case
                    *pRoot = *temp; // Copy the contents of
                                // the non-empty child
                    delete(temp); // borramos la hoja
                } else {
                    // node with two children: Get the inorder
                    // successor (smallest in the right subtree)
                    NodeAVL<int>* temp = minValueNode(pRoot->right);
        
                    // Copy the inorder successor's
                    // data to this node
                    *pRoot->data = *temp->data;
        
                    // Delete the inorder successor
                    pRoot->right = deleteNode(pRoot->right,
                                            *temp->data);
                }
            }
        
            // If the tree had only one node
            // then return
            if (pRoot == nullptr)
            return pRoot;
        
            // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
            pRoot->height = 1 + max(height(pRoot->left),
                                height(pRoot->right));
        
            // STEP 3: GET THE BALANCE FACTOR OF
            // THIS NODE (to check whether this
            // node became unbalanced)
            int balance = getBalance(pRoot);
        
            // If this node becomes unbalanced,
            // then there are 4 cases
        
            // Left Left Case
            if (balance > 1 &&
                getBalance(pRoot->left) >= 0)
                return rightRotate(pRoot);
        
            // Left Right Case
            if (balance > 1 &&
                getBalance(pRoot->left) < 0)
            {
                pRoot->left = leftRotate(pRoot->left);
                return rightRotate(pRoot);
            }
        
            // Right Right Case
            if (balance < -1 &&
                getBalance(pRoot->right) <= 0)
                return leftRotate(pRoot);
        
            // Right Left Case
            if (balance < -1 &&
                getBalance(pRoot->right) > 0)
            {
                pRoot->right = rightRotate(pRoot->right);
                return leftRotate(pRoot);
            }
        
            return pRoot;
        }
        
        // A utility function to print preorder
        // traversal of the tree.
        // The function also prints height
        // of every node
        void preOrder(NodeAVL<int> *pRoot){
            if(pRoot != nullptr)
            {
                cout << *pRoot->data << " ";
                preOrder(pRoot->left);
                preOrder(pRoot->right);
            }
        }
        
        // Print the tree
        void printTree(NodeAVL<int> *pRoot, string indent, bool last) {
            if (pRoot != nullptr) {
                cout << indent;
                if (last) {
                cout << "R----";
                indent += "   ";
                } else {
                cout << "L----";
                indent += "|  ";
                }
                cout << *pRoot->getData() << endl;
                printTree(pRoot->getLeft(), indent, false);
                printTree(pRoot->getRight(), indent, true);
            }
        }
};
 
// This code is contributed by rathbhupendra