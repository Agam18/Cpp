class Solution {
    public:
        class DSU {
            public:

                vector<int> parent;
                vector<int> depth;

                DSU(int n) {
                    parent = vector<int>(n);
                    depth = vector<int>(n, 0);
                    for (int i = 0; i<n; i++) {
                        parent[i] = i;
                    }
                }

                int findParent(int node) {
                    if (node != parent[node]) {
                        parent[node] = findParent(parent[node]);
                    }
                    return parent[node];
                }

                void unionNodes(int x, int y) {
                    int px = findParent(x);
                    int py = findParent(y);
                    if (px == py) {
                        return;
                    }
                    if (depth[px] < depth[py]) {
                        parent[px] = py;
                    } else if (depth[py] < depth[px]) {
                        parent[py] = px;
                    } else {
                        parent[py] = px;
                        depth[px]++;
                    }
                }
        };

        int getPairs(int n, vector<vector<int>>&edges) {
            DSU* lowDSU = new DSU(n);
            DSU* highDSU = new DSU(n);
            for (int i = 0; i<edges.size(); i++) {
                if (edges[i][2] == 1) {
                    highDSU->unionNodes(edges[i][0], edges[i][1]);
                } else {
                    lowDSU->unionNodes(edges[i][0], edges[i][1]);
                }
            }

            unordered_map<int, int> lowComponents;
            unordered_map<int, int> highComponents;
            for (int i = 0; i<n; i++) {
                int pLow = lowDSU->findParent(i);
                int pHigh = highDSU->findParent(i);
                lowComponents[pLow]++;
                highComponents[pHigh]++;
            }
            int ans = 0;
            for (auto& entry: lowComponents) {
                ans += entry.second * (entry.second - 1);
            }
            for (auto& entry: highComponents) {
                ans += entry.second * (entry.second - 1);
            }
            for (int i = 0; i<n; i++) {
                ans += (lowComponents[lowDSU->findParent(i)] - 1) * (highComponents[highDSU->findParent(i)] - 1);
            }
            return ans;
        }

};