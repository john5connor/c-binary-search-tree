#include<stdio.h>
#include<assert.h>
#include "IntegerBST.h"

// A function to compare two integers based on their value
int compareValue(int a, int b) {
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}
// A function to compare two integers based on the sum of their digits
int compareSumOfDigits(int a, int b) {
    int sumA = 0;
    int sumB = 0;
    while (a > 0) {
        sumA += a % 10;
        a /= 10;
    }
    while (b > 0) {
        sumB += b % 10;
        b /= 10;
    }
    if (sumA > sumB) {
        return 1;
    } else if (sumA < sumB) {
        return -1;
    } else {
        return 0;
    }
}

// A function to compare two integers based on the number of digits in each integer
int compareNumberOfDigits(int a, int b) {
    int countA = 0;
    int countB = 0;
    while (a > 0) {
        countA++;
        a /= 10;
    }
    while (b > 0) {
        countB++;
        b /= 10;
    }
    if (countA > countB) {
        return 1;
    } else if (countA < countB) {
        return -1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {        
    // Declare variables to store user input for traversal type, and minimum and maximum values in the binary search tree
    int c, min, max;

    // Initialize the binary search tree with the compareValue function
    IntegerBST *bst = initializeIntegerBST(compareValue); 

    // Check if binary search tree is initialized correctly
    assert(bst->root == NULL && bst->totalNodes == 0 && bst->compare != NULL); 

    // Insert values into the binary search tree by iterating over command line arguments 
    for(int i = 1; i < argc; i++) { 
        insertNodeByKey(bst, atoi(argv[i]));
    }
    // Query the user for the type of traversal they would like to perform
    printf("What type of traversal would you like to perform?\nEnter 'i' for inorder traversal, 'p' for preorder traversal, or 'o' for postorder traversal\n");

    // Print the values in the binary search tree depending on the traversal type chosen by the user
    printOnConsole(bst, getchar());

    queryMinMax(bst, &min, &max);
    printf("Total nodes in the binary search tree: %d\n", bst->totalNodes);

    freeBST(bst->root);

    return 0;
}