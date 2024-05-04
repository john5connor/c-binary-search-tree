#ifndef INTEGERBST_H
#define INTEGERBST_H

#include<stdio.h>
#include<stdlib.h>

// A structure to represent a node of the binary search tree
// and pointers to the left and right child nodes
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// A structure to represent the binary search tree containing a pointer to the root node,
// the total number of nodes in the tree, and a function pointer to compare two integers
typedef struct IntegerBST {
    Node *root;
    int totalNodes;
    int (*compare)(int, int);
} IntegerBST;

// A function to create a binary search tree, which takes a function pointer to compare two integers
IntegerBST* initializeIntegerBST(int (*compare)(int, int)) {
    IntegerBST *bst = (IntegerBST*)malloc(sizeof(IntegerBST)); // Allocate memory for the binary search tree
    // Reset the binary search tree to an initial state if not empty
    if(bst->totalNodes > 0) {
        free(bst->root); // Free memory allocated for the root node
        bst->root = NULL;
        bst->totalNodes = 0;
    }
    bst->root = NULL; // Initially, the root node is NULL
    bst->totalNodes = 0; // Initially, the total number of nodes is 0
    bst->compare = compare;
    return bst;
}

// A function to create a node of the binary search tree
Node* createNode(int data) {
    Node *node = (Node*)malloc(sizeof(Node)); // Allocate memory for the node
    node->data = data; // Set the data of the node to the data passed as an argument
    node->left = NULL;
    node->right = NULL;
    return node;
}

// A function to insert a node into the binary search tree
int insertNodeByKey(IntegerBST *bst, int data) {
    Node *node = createNode(data); // Create a node with the data passed as an argument
    Node *current = bst->root; // Set the current node to the root node
    Node *parent = NULL; // Set the parent node to NULL
    // Traverse the binary search tree to find the correct position to insert the node
    while (current != NULL) {
        parent = current; 
        if(bst->compare(data, current->data) == 0) {
            printf("Failed insertion. The node with the key %d already exists in the binary search tree\n", data);
            return -1;
        } 
        else if (bst->compare(data, current->data) < 0) { 
            current = current->left; 
        } else {
            current = current->right; 
        }
    }
    // If the binary search tree is empty, set the root node to the node
    if (parent == NULL) {
        bst->root = node;
    } else if (bst->compare(data, parent->data) < 0) {
        parent->left = node; 
    } else {
        parent->right = node; 
    }
    bst->totalNodes++;
    return 1;
}

// A function to search a node by key in the binary search tree
int searchNodeByKey(IntegerBST *bst, int data) {
    Node *current = bst->root; // Set the current node to the root node
    // Traverse the binary search tree to find the node with the key
    while (current != NULL) {
        // If the node with the key is found, return 1
        if(bst->compare(data, current->data) == 0) {
            printf("Successful search. The node with the key %d exists in the binary search tree\n", data);
            return 1;
        } 
        else if (bst->compare(data, current->data) < 0) { 
            current = current->left; 
        } else {
            current = current->right; 
        }
    }
    // If the node is not in the binary search tree, return 0
    printf("Failed search. The node with the key %d does not exist in the binary search tree\n", data);
    return 0;
}

void queryMinMax(IntegerBST *bst, int *min, int *max) {
    *min, *max = 0;
    if(bst->root == NULL) {
        printf("The binary search tree is empty\n");
        return;
    }

    Node *current = bst->root; // Set the current node to the root node

    while (current->left != NULL) { // Traverse the binary search tree to find the node with the minimum key
        current = current->left;
    }
    *min = current->data;
    printf("The minimum key in the binary search tree is %d\n", *min);

    current = bst->root; // Set the current node to the root node
    
    while (current->right != NULL) { // Traverse the binary search tree to find the node with the maximum key
        current = current->right;
    }
    *max = current->data;
    printf("The maximum key in the binary search tree is %d\n", *max);
}

// A function to print out the values in the binary search tree using inorder traversal
void inorderTraversal(Node *node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->data);
        inorderTraversal(node->right);
    }
}

// A function to print out the values in the binary search tree using preorder traversal
void preorderTraversal(Node *node) {
    if (node != NULL) {
        printf("%d ", node->data);
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

// A function to print out the values in the binary search tree using postorder traversal
void postorderTraversal(Node *node) {
    if (node != NULL) {
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        printf("%d ", node->data);
    }
}

// A function that accepts a traversal type and calls the corresponding traversal function
void printOnConsole(IntegerBST *bst, char traversalType) {
    if (traversalType == 'i') {
        inorderTraversal(bst->root);
    } else if (traversalType == 'p') {
        preorderTraversal(bst->root);
    } else if (traversalType == 'o') {
        postorderTraversal(bst->root);
    } else {
        printf("Invalid traversal type\n");
    }
    printf("\n");
}

// A function to recursively free the binary search tree
void freeBST(Node *node) {
    if (node != NULL) {
        freeBST(node->left);  // Free the left subtree
        freeBST(node->right); // Free the right subtree
        free(node);           // Free the current node
    }
}

#endif // INTEGERBST_H
