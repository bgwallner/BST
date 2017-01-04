//
//  main.c
//  BST
//
//  Created by Bo-Göran Wallner on 2016-12-28.
//  Copyright © 2016 Bo-Göran Wallner. All rights reserved.
//

// TODO: Fix size when creating tree. Somehow also root node must be created. 

#include <stdio.h>
#include <stdlib.h>

/************** Node definition **************/

typedef struct node node_t;

struct node {
    node_t* left;
    node_t* right;
	node_t* parent;
    int key;
};

/************** Local variables **************/

static int treeSize = 1;

/************** Helper methods **************/

/* Return a new node of 'node_t' */
static node_t* newNode() {
    
    /* Create node */
    node_t *node = malloc(sizeof(node_t));
    
    /* Init parameters */
    node->key = 0;
    node->right = NULL;
    node->left = NULL;
	node->parent = NULL;
    
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
    
    /* Store parent */
    z->parent = y;
    
    if (y == NULL)
        T = z;
    else {
        if (compareTo(z->key, y->key) < 0)
            y->left = z;
        else
            y->right = z;
    }
	
	/* Increase the size */
	treeSize++;
}

/* Traverses tree in increasing (sorted) order and print keys */
static void inOrderTreeWalk(node_t* x) {
    
    if (x != NULL) {
        inOrderTreeWalk(x->left);
        printf("key (%d)\n", x->key);
        inOrderTreeWalk(x->right);
    }  
}

/* Traverses tree in post order and print keys */
static void postOrderTreeWalk(node_t* x) {
    
    if (x != NULL) {
        inOrderTreeWalk(x->left);
        inOrderTreeWalk(x->right);
		printf("key (%d)\n", x->key);
    }  
}

/* Traverses tree in pre order and print keys */
static void preOrderTreeWalk(node_t* x) {
    
    if (x != NULL) {
		printf("key (%d)\n", x->key);
        inOrderTreeWalk(x->left);
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

/* Return the size of the tree */
static int size() {
	return treeSize;
}

/* Return the successor to 'x' */
static node_t* treeSuccessor(node_t* x) {
	node_t* y;
	if (x->right != NULL)
		return treeMinimum(x->right);
	
	y = x->parent;
	while (y != NULL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

/************** Test client **************/

int main(int argc, const char * argv[]) {
    // insert code here...
    
    /* Figure 13.2 'Introduction to algorithms */
	/* 15 6 18 3 7 17 20 2 4 13 9 */
	
    node_t *T = newNode();
    T->key = 15;
    
    node_t* z1 = newNode();
    z1->key = 6;
    treeInsert(T, z1);
    
    node_t* z2 = newNode();
    z2->key = 18;
    treeInsert(T, z2);
    
    node_t* z3 = newNode();
    z3->key = 3;
    treeInsert(T, z3);
    
    node_t* z4 = newNode();
    z4->key = 7;
    treeInsert(T, z4);
	
	node_t* z5 = newNode();
    z5->key = 17;
    treeInsert(T, z5);
	
	node_t* z6 = newNode();
    z6->key = 20;
    treeInsert(T, z6);
	
	node_t* z7 = newNode();
    z7->key = 2;
    treeInsert(T, z7);
	
	node_t* z8 = newNode();
    z8->key = 4;
    treeInsert(T, z8);
	
	node_t* z9 = newNode();
    z9->key = 13;
    treeInsert(T, z9);
	
	node_t* z10 = newNode();
    z10->key = 9;
    treeInsert(T, z10);
	
	printf("Pre order tree walk\n");
	preOrderTreeWalk(T);
    
	printf("In order tree walk\n");
    inOrderTreeWalk(T);
	
	printf("Post order tree walk\n");
	postOrderTreeWalk(T);
    
    node_t* z50 = newNode();
    z50 = treeMaximum(T);
    printf("Tree max is (%d)\n", z50->key);
    deleteNode(z50);
    
    node_t* z60 = newNode();
    z60 = treeMinimum(T);
    printf("Tree min is (%d)\n", z60->key);
    deleteNode(z60);
    
    node_t* z70;
    z70 = treeSearch(T, 7);
    if (z70 != NULL) {
        printf("Key found (%d) (%p)\n", z70->key, z70);
    }
	
	printf("The size of the tree (%d)\n", size());
	
	node_t* z80 = treeSuccessor(T);
	printf("Tree successor to T (root) has value (%d)\n", z80->key);
    
    return 0;
}
