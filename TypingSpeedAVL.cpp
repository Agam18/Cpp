#include <bits/stdc++.h>
using namespace std;

/*
Each node stores:
key    -> typing speed
height -> needed to maintain AVL balance
size   -> number of nodes in subtree (including duplicates)
count  -> number of times this key appears (handles duplicates)
*/
struct Node {
    int key;
    int height;
    int size;
    int count;
    Node *left, *right;

    Node(int k) {
        key = k;
        height = 1;
        size = 1;
        count = 1;
        left = right = NULL;
    }
};

/* Return height of node */
int getHeight(Node* n) {
    return n ? n->height : 0;
}

/* Return subtree size */
int getSize(Node* n) {
    return n ? n->size : 0;
}

/*
Update height and subtree size after modifications
size = left subtree + right subtree + duplicates at this node
*/
void update(Node* n) {
    if(!n) return;

    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    n->size = getSize(n->left) + getSize(n->right) + n->count;
}

/* Balance factor = left height - right height */
int balanceFactor(Node* n) {
    if(!n) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

/*
Right Rotation (used for LL imbalance)

        y                              x
       / \                            / \
      x   T3        →               T1  y
     / \                                / \
    T1 T2                              T2 T3
*/
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* t2 = x->right;

    x->right = y;
    y->left = t2;

    update(y);
    update(x);

    return x;
}

/*
Left Rotation (used for RR imbalance)

      x                                y
     / \                              / \
    T1  y         →                  x  T3
       / \                          / \
      T2 T3                        T1 T2
*/
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* t2 = y->left;

    y->left = x;
    x->right = t2;

    update(x);
    update(y);

    return y;
}

/*
Insert key into AVL tree and compute how many elements are greater.

greaterCount tracks number of speeds greater than current speed.
*/
Node* insert(Node* node, int key, int &greaterCount) {

    /* Standard BST insertion */
    if(!node)
        return new Node(key);

    /*
    If key is smaller than current node:

    All nodes in:
    - right subtree
    - current node itself

    are greater than this key
    */
    if(key < node->key) {
        greaterCount += getSize(node->right) + node->count;
        node->left = insert(node->left, key, greaterCount);
    }

    /*
    If key is greater:

    just go right since no greater elements found here
    */
    else if(key > node->key) {
        node->right = insert(node->right, key, greaterCount);
    }

    /* Duplicate key */
    else {
        node->count++;
    }

    /* Update height and subtree size */
    update(node);

    int bf = balanceFactor(node);

    /*
    ---------------- ROTATION CASES ----------------
    */

    /*
    LL Case (Left Left)

    Happens when:
    - tree becomes left heavy (bf > 1)
    - new key inserted in left subtree of left child

            30
           /
         20
        /
      10

    Fix → Right Rotation
    */
    if(bf > 1 && key < node->left->key)
        return rightRotate(node);

    /*
    RR Case (Right Right)

    Happens when:
    - tree becomes right heavy (bf < -1)
    - new key inserted in right subtree of right child

      10
        \
         20
           \
            30

    Fix → Left Rotation
    */
    if(bf < -1 && key > node->right->key)
        return leftRotate(node);

    /*
    LR Case (Left Right)

            30
           /
         10
           \
            20

    Fix:
    1. Left rotate left child
    2. Right rotate node
    */
    if(bf > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    /*
    RL Case (Right Left)

        10
          \
           30
          /
        20

    Fix:
    1. Right rotate right child
    2. Left rotate node
    */
    if(bf < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/*
Find node with minimum key (used in delete)
*/
Node* minValueNode(Node* node) {

    Node* curr = node;

    while(curr->left)
        curr = curr->left;

    return curr;
}

/*
DELETE NODE
*/
Node* deleteNode(Node* root, int key) {

    if(!root)
        return root;

    /* Standard BST delete */
    if(key < root->key)
        root->left = deleteNode(root->left, key);

    else if(key > root->key)
        root->right = deleteNode(root->right, key);

    else {

        /* If duplicates exist just reduce count */
        if(root->count > 1) {
            root->count--;
        }

        else {

            /* Node with 0 or 1 child */
            if(!root->left || !root->right) {

                Node* temp = root->left ? root->left : root->right;

                if(!temp) {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;

                delete temp;
            }

            else {

                /* Node with 2 children */

                Node* temp = minValueNode(root->right);

                root->key = temp->key;
                root->count = temp->count;
                temp->count = 1;

                root->right = deleteNode(root->right, temp->key);
            }
        }
    }

    if(!root)
        return root;

    update(root);

    int bf = balanceFactor(root);

    /* LL Case */
    if(bf > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);

    /* LR Case */
    if(bf > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* RR Case */
    if(bf < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    /* RL Case */
    if(bf < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int main() {

    /* Incoming typing speeds */
    vector<int> speeds = {50, 40, 60, 55};

    Node* root = NULL;

    for(int speed : speeds) {

        int greaterCount = 0;

        /*
        Insert speed and calculate
        how many speeds are greater
        */
        root = insert(root, speed, greaterCount);

        /*
        Rank definition:
        rank = (#greater speeds) + 1
        */
        int rank = greaterCount + 1;

        cout << "Speed " << speed << " Rank " << rank << endl;
    }

    return 0;
}