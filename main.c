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

/* Size of tree (T != NULL) */
static int treeSize = 1;

/* Pointer to root */
static node_t* T    = NULL;

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

/* Returns 1 if a >= b */
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
        printf("%d ", x->key);
        inOrderTreeWalk(x->right);
    }
}

/* Traverses tree in post order and print keys */
static void postOrderTreeWalk(node_t* x) {
    
    if (x != NULL) {
        inOrderTreeWalk(x->left);
        inOrderTreeWalk(x->right);
		printf("%d ", x->key);
    }
}

/* Traverses tree in pre order and print keys */
static void preOrderTreeWalk(node_t* x) {

    if (x != NULL) {
		printf("%d ", x->key);
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
	if (T != NULL)
		return treeSize;
	else
		return 0;
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

/* Deletes a node 'z' from 'T' and returns 'z' */
/* for the client to free memory.              */
static node_t* treeDelete(node_t* T, node_t* z) {
	node_t* y = NULL;
	node_t* x = NULL;

	if (z->left == NULL || z->right == NULL)
		y = z;
	else 
		y = treeSuccessor(z);
	
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;

	if (x != NULL)
		x->parent = y->parent;

	node_t* temp = y->parent;
	if (y->parent == NULL)
		T = x;
	else if (y == temp->left)
		temp->left = x;
	else 
		temp->right = x;

	if (y != z) {
		z->key = y->key;
	}

	return y;
}

/************** Test client **************/

int main(int argc, const char * argv[]) {
    // insert code here...

    /* Figure 13.2 'Introduction to algorithms */
	/* 15 6 18 3 7 17 20 2 4 13 9 */

	printf("\n");
	printf("\n");
	printf("/******************* TEST BINARY SEARCH TREE ************/ \n");
	printf("\n");
	printf("/******************* (1) TEST INSERTION *********************/ \n");
	printf("\n");
	printf("/******************* (TREEWALK AFTER EACH INSERTION) ********/ \n");
	printf("\n");

	/* Create the root */
    T = newNode();
    T->key = 15;

	printf("Current tree T: ");
	inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

    node_t* z1 = newNode();
    z1->key = 6;
    treeInsert(T, z1);

	printf("Current tree T: ");
	inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

    node_t* z2 = newNode();
    z2->key = 18;
    treeInsert(T, z2);

	printf("Current tree T: ");
	inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

    node_t* z3 = newNode();
    z3->key = 3;
    treeInsert(T, z3);

	printf("Current tree T: ");
	inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

    node_t* z4 = newNode();
    z4->key = 7;
    treeInsert(T, z4);
	
	printf("Current tree T: ");
	inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

	node_t* z5 = newNode();
    z5->key = 17;
    treeInsert(T, z5);

	printf("Current tree T: ");
	inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

	node_t* z6 = newNode();
    z6->key = 20;
    treeInsert(T, z6);

	printf("Current tree T: ");
	inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

	node_t* z7 = newNode();
    z7->key = 2;
    treeInsert(T, z7);

	printf("Current tree T: ");
	inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

	node_t* z8 = newNode();
    z8->key = 4;
    treeInsert(T, z8);

	printf("Current tree T: ");
	inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

	node_t* z9 = newNode();
    z9->key = 13;
    treeInsert(T, z9);

	printf("Current tree T: ");
	inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

	node_t* z10 = newNode();
    z10->key = 9;
    treeInsert(T, z10);

	printf("Current tree T: ");
	inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

    printf("/******************* (2) TEST TREEWALK **********************/ \n");
	printf("\n");

	printf("Pre order tree walk: ");
	preOrderTreeWalk(T);
	printf("\n");
	printf("\n");

	printf("In order tree walk: ");
    inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

	printf("Post order tree walk: ");
	postOrderTreeWalk(T);
	printf("\n");
	printf("\n");

    printf("/******************* (3) TEST MAX/MIN NODES *****************/ \n");
	printf("\n");

    node_t* temp = treeMaximum(T);
    printf("Tree max: (%d)\n", temp->key);
	printf("\n");

    temp = treeMinimum(T);
    printf("Tree min: (%d)\n", temp->key);
	printf("\n");

	printf("/******************* (4) TEST TREE SEARCH *******************/ \n");
	printf("\n");

    node_t* z70;
    z70 = treeSearch(T, 7);
    if (z70 != NULL) {
        printf("Key found: (%d) (Correct key=7)\n", z70->key);
		printf("\n");
    }

	printf("/******************* (5) TEST TREE SIZE *********************/ \n");
	printf("\n");

	printf("The size of tree: (%d)\n", size());
	printf("\n");

	printf("/******************* (6) TEST TREE SUCCESSOR ****************/ \n");
	printf("\n");

	node_t* z80 = treeSuccessor(T);
	printf("Tree successor to T (key=%d) has value (%d)\n", T->key, z80->key);
	printf("\n");

	printf("/******************* (7) TEST TREE DELETION *****************/ \n");
	printf("\n");

	/******************* CASE 1 *********************/

	/* Remove element with no children z8 (key=4) */

	printf("Deleting key=4 (no children node):\n");
	printf("\n");
	node_t* deleted = treeDelete(T, z8);

	/* Free memory */
	deleteNode(deleted);

	printf("In order tree walk: ");
    inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

	/******************* CASE 2 *********************/

	/* Remove element with one child z9 (key=13) */
	printf("Deleting key=13 (one child node):\n");
	printf("\n");
	deleted = treeDelete(T, z9);

    /* Free memory */
	deleteNode(deleted);

	printf("In order tree walk: ");
    inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

	/******************* CASE 3 *********************/

	/* Remove element with two children z2 (key=18) */
	printf("Deleting key=18 (two children node):\n");
	printf("\n");
	deleted = treeDelete(T, z2);

    /* Free memory */
	deleteNode(deleted);

	printf("In order tree walk: ");
    inOrderTreeWalk(T);
	printf("\n");
	printf("\n");

	printf("/******************* END TEST *******************************/ \n");

    return 0;
}
