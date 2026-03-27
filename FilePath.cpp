#include <bits/stdc++.h>
using namespace std;

struct Node {
    unordered_map<string, Node*> children;
    int fileCount = 0; // number of files ending here
};

Node* root = new Node();

// split path
vector<string> split(string &s) {
    vector<string> res;
    string cur;
    for (char c : s) {
        if (c == '/') {
            if (!cur.empty()) {
                res.push_back(cur);
                cur.clear();
            }
        } else cur += c;
    }
    if (!cur.empty()) res.push_back(cur);
    return res;
}

// build trie
void insertPath(string &path) {
    vector<string> parts = split(path);
    Node* node = root;

    for (auto &p : parts) {
        if (!node->children.count(p))
            node->children[p] = new Node();
        node = node->children[p];
    }

    node->fileCount++; // handle multiple files too
}

// DFS DP
multiset<int>* solve(Node* node, int depth) {

    multiset<int>* cur = new multiset<int>();

    // process children
    for (auto &[_, child] : node->children) {
        auto childSet = solve(child, depth + 1);

        // small-to-large merge
        if (cur->size() < childSet->size())
            swap(cur, childSet);

        cur->insert(childSet->begin(), childSet->end());
    }

    // add files at this node
    for (int i = 0; i < node->fileCount; i++) {
        cur->insert(depth);
    }

    // if no file here → pull one from children
    if (node->fileCount == 0 && !cur->empty()) {
        auto it = prev(cur->end()); // largest depth
        cur->erase(it);
        cur->insert(depth);
    }

    return cur;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string path;
        getline(cin, path);
        insertPath(path);
    }

    auto finalSet = solve(root, 0);

    long long ans = 0;
    for (auto d : *finalSet) ans += d;

    cout << ans << endl;

    return 0;
}