#include <bits/stdc++.h>
using namespace std;
/*
| Operation      | Time Complexity |
| -------------- | --------------- |
| Insert         | O(L)            |
| Exact Query    | O(L)            |
| Suffix Query   | O(L)            |
| Delete         | O(L * Σ) ≈ O(L) |
| Compute Threat | O(Q * L)        |

SC : O(N * L)
N is the number of words and L is the average length of each word.
*/
struct Node {
    unordered_map<char, Node*> children;
    int endScore = 0;     // score if word ends here
    int maxScore = 0;     // max score in subtree
};

class ThreatSystem {
    Node* root;

public:
    ThreatSystem() {
        root = new Node();
    }

    // 🔁 Reverse helper
    string rev(string s) {
        reverse(s.begin(), s.end());
        return s;
    }

    // 🔧 INSERT
    void insert(string word, int score) {
        word = rev(word);
        Node* node = root;

        for (char c : word) {
            if (!node->children.count(c))
                node->children[c] = new Node();
            node = node->children[c];

            node->maxScore = max(node->maxScore, score);
        }

        node->endScore = score;
    }

    // 🔄 DFS recompute maxScore
    int recompute(Node* node) {
        int mx = node->endScore;

        for (auto &[ch, child] : node->children) {
            mx = max(mx, recompute(child));
        }

        node->maxScore = mx;
        return mx;
    }

    // ❌ DELETE (DFS-based)
    void remove(string word) {
        word = rev(word);
        Node* node = root;

        vector<Node*> path; // store path nodes
        path.push_back(root);

        for (char c : word) {
            if (!node->children.count(c))
                return; // word not present
            node = node->children[c];
            path.push_back(node);
        }

        // remove score
        node->endScore = 0;

        // recompute from bottom to top
        for (int i = path.size() - 1; i >= 0; i--) {
            Node* cur = path[i];
            int mx = cur->endScore;

            for (auto &[ch, child] : cur->children) {
                mx = max(mx, child->maxScore);
            }

            cur->maxScore = mx;
        }
    }

    // 🔍 exact word query
    int queryExact(string word) {
        word = rev(word);
        Node* node = root;

        for (char c : word) {
            if (!node->children.count(c))
                return 0;
            node = node->children[c];
        }

        return node->endScore;
    }

    // 🔍 suffix query (#word)
    int querySuffix(string suffix) {
        suffix = rev(suffix);
        Node* node = root;

        for (char c : suffix) {
            if (!node->children.count(c))
                return 0;
            node = node->children[c];
        }

        return node->maxScore;
    }

    // 🎯 MAIN FUNCTION
    int computeThreat(vector<string>& log) {
        int total = 0;

        for (auto &w : log) {
            if (w[0] == '#') {
                total += querySuffix(w.substr(1));
            } else {
                total += queryExact(w);
            }
        }

        return total;
    }
};

int main() {
    ThreatSystem ts;

    ts.insert("password", 10);
    ts.insert("secret", 9);
    ts.insert("secretword", 7);

    vector<string> log = {
        "Logging", "customer", "data", "with",
        "#word", "y29ey23eh", "and", "secret"
    };

    cout << ts.computeThreat(log) << endl; // 19
}