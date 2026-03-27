#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

void topK(Node* root, int K, vector<int>& res) {
    if (!root || res.size() >= K) return;

    topK(root->right, K, res);   // right first (larger values)

    if (res.size() < K)
        res.push_back(root->val);

    topK(root->left, K, res);    // then left
}

// Build predecessor stack (nodes smaller than x)
void buildPredStack(Node* root, int x, stack<Node*>& pred) {
    while (root) {
        if (root->val < x) {
            pred.push(root);
            root = root->right;  // go right to find closer to x
        } else {
            root = root->left;
        }
    }
}

// Build successor stack (nodes larger than x)
void buildSuccStack(Node* root, int x, stack<Node*>& succ) {
    while (root) {
        if (root->val > x) {
            succ.push(root);
            root = root->left;  // go left to find closer to x
        } else {
            root = root->right;
        }
    }
}

// Get next predecessor (next smaller value)
int getPred(stack<Node*>& pred) {
    Node* curr = pred.top();
    pred.pop();
    int val = curr->val;
    curr = curr->left;
    while (curr) {
        pred.push(curr);
        curr = curr->right;
    }
    return val;
}

// Get next successor (next larger value)
int getSucc(stack<Node*>& succ) {
    Node* curr = succ.top();
    succ.pop();
    int val = curr->val;
    curr = curr->right;
    while (curr) {
        succ.push(curr);
        curr = curr->left;
    }
    return val;
}

// Example usage:
int main() {
    /*
            20
           /  \
          10   30
         / \   / \
        5  15 25 35
    */
    Node* root = new Node(20);
    root->left = new Node(10);
    root->right = new Node(30);
    root->left->left = new Node(5);
    root->left->right = new Node(15);
    root->right->left = new Node(25);
    root->right->right = new Node(35);

    int x = 18;  // value to find nearest 10 smaller/larger
    stack<Node*> pred, succ;
    buildPredStack(root, x, pred);
    buildSuccStack(root, x, succ);

    cout << "Nearest smaller values: ";
    for (int i = 0; i < 10 && !pred.empty(); i++) {
        cout << getPred(pred) << " ";
    }
    cout << "\nNearest larger values: ";
    for (int i = 0; i < 10 && !succ.empty(); i++) {
        cout << getSucc(succ) << " ";
    }
}