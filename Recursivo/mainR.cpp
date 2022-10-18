#include "ArbolAVL.h"
#include <iostream>

// Driver Code
int main()
{
    ArbolAVL *arbol = new ArbolAVL();
    NodeAVL<int> *root = arbol->getRoot();
    /* Constructing tree given in
    the above figure */
    root = arbol->insert(root, 9);
    arbol->printTree(root, "", true);
    root = arbol->insert(root, 5);
    arbol->printTree(root, "", true);
    root = arbol->insert(root, 10);
    arbol->printTree(root, "", true);
    root = arbol->insert(root, 0);
    arbol->printTree(root, "", true);
    root = arbol->insert(root, 6);
    arbol->printTree(root, "", true);
    root = arbol->insert(root, 11);
    arbol->printTree(root, "", true);
    root = arbol->insert(root, -1);
    arbol->printTree(root, "", true);
    root = arbol->insert(root, 1);
    arbol->printTree(root, "", true);
    root = arbol->insert(root, 2);
    arbol->printTree(root, "", true);

    /* The constructed AVL Tree would be
            9
        / \
        1 10
        / \ \
    0 5 11
    / / \
    -1 2 6
    */

    cout << "Preorder traversal of the "
            "constructed AVL tree is \n";
    arbol->preOrder(root);

    root = arbol->deleteNode(root, 10);

    /* The AVL Tree after deletion of 10
            1
        / \
        0 9
        / / \
    -1 5     11
        / \
        2 6
    */

    cout << "\nPreorder traversal after"
        << " deletion of 10 \n";
    arbol->preOrder(root);

    return 0;
}