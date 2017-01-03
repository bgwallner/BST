//
//  main.c
//  BST
//
//  Created by Bo-Göran Wallner on 2016-12-28.
//  Copyright © 2016 Bo-Göran Wallner. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/************** Node definition **************/

typedef struct node node_t;

struct node {
    node_t* left;
    node_t* right;
    int key;
};

/************** Helper methods **************/

/* Return a new node of 'node_t' */
static node_t* newNode() {
    
    /* Create node */
    node_t *node = malloc(sizeof(node_t));
    
    /* Init parameters */
    node->key = 0;
    node->right = NULL;
    node->left = NULL;
    
    return node;
}

/* Deletes node 'x'. Must not be called unless */
/* x->right = x->left = NULL.                  */
static void deleteNode(node_t* x) {
    
    /* Return if node not valid */
    if (x == NULL)
        return;
    
    /* Return if children not NULL */
    if (x->left == NULL || x->right == NULL)
        return;
    
    /* Free node */
    free(x);
    x = NULL;
}

/************** Comparison method **************/

static int compareTo(int a, int b) {
    if (a >= b)
        return 1;
    else
        return -1;
}

/************** BST implementation **************/

/* Inserts node 'z' into BST tree 'T' */
static void treeInsert(node_t* T, node_t* z) {
    
    /* Return if node not valid */
    if (T == NULL || z == NULL)
        return;
    
    node_t* y = NULL;
    node_t* x = T;
    node_t* pz = NULL;
    
    /* Traverse 'T' until the right place found */
    while(x != NULL) {
        /* Save parent of 'x' in 'y' */
        y = x;
        
        /* If z less than x, go left. Otherwise go right */
        if (compareTo(z->key, x->key) < 0)
            x = x->left;
        else
            x = x->right;
    }
    
    /* Store parent to 'z' */
    pz = y;
    
    if (y == NULL)
        T = z;
    else {
        if (compareTo(z->key, y->key) < 0)
            y->left = z;
        else
            y->right = z;
    }
}

/* Traverses tree in increasing order and print keys */
static void inOrderTreeWalk(node_t* x) {
    
    if (x != NULL) {
        inOrderTreeWalk(x->left);
        printf("key (%d)\n", x->key);
        inOrderTreeWalk(x->right);
    }
    
}

/* Return maximum in tree */
static node_t* treeMaximum(node_t* x) {
    node_t* px = NULL;
    /* Go right */
    while (x != NULL) {
        px = x;
        x = x->right;
    }
    return px;
}

/* Return minimum in tree */
static node_t* treeMinimum(node_t* x) {
    node_t* px = NULL;
    /* Go left */
    while (x != NULL) {
        px = x;
        x = x->left;
    }
    return px;
}

/* Return node 'x' containing key */
static node_t* treeSearch(node_t* x, int key) {
    if (x == NULL || key == x->key)
        return x;
    if (key < x->key)
        return treeSearch(x->left, key);
    else
        return treeSearch(x->right, key);
}

/************** Test client **************/

int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    node_t *T = newNode();
    T->key = 5;
    
    node_t* z1 = newNode();
    z1->key = 3;
    treeInsert(T, z1);
    
    node_t* z2 = newNode();
    z2->key = 7;
    treeInsert(T, z2);
    
    node_t* z3 = newNode();
    z3->key = 2;
    treeInsert(T, z3);
    
    node_t* z4 = newNode();
    z4->key = 5;
    treeInsert(T, z4);
    
    inOrderTreeWalk(T);
    
    node_t* z5 = newNode();
    z5 = treeMaximum(T);
    printf("Tree max is (%d)\n", z5->key);
    deleteNode(z5);
    
    node_t* z6 = newNode();
    z6 = treeMinimum(T);
    printf("Tree min is (%d)\n", z6->key);
    deleteNode(z6);
    
    node_t* z7;
    z7 = treeSearch(T, 7);
    if (z7 != NULL) {
        printf("Key found (%d) (%p)\n", z7->key, z7);
    }
    
    return 0;
}
