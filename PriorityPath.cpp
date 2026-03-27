#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> par, size;

    DSU(int n) {
        par.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int findPar(int x) {
        if (par[x] == x) return x;
        return par[x] = findPar(par[x]);
    }

    void unite(int a, int b) {
        a = findPar(a);
        b = findPar(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }

    int getSize(int x) {
        return size[findPar(x)];
    }
};

int main() {
    int n;
    cin >> n;

    vector<tuple<int,int,int>> edges; // u, v, type

    for (int i = 0; i < n-1; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        u--; v--;
        edges.push_back({u, v, t});
    }

    DSU dsu_low(n);

    // Step 1: unite LOW edges
    for (auto &[u,v,t] : edges) {
        if (t == 0) {
            dsu_low.unite(u, v);
        }
    }

    // Step 2: count pairs inside LOW components
    long long ans = 0;
    unordered_map<int,int> compSize;

    for (int i = 0; i < n; i++) {
        compSize[dsu_low.findPar(i)]++;
    }

    for (auto &[_, sz] : compSize) {
        ans += 1LL * sz * (sz - 1) / 2;
    }

    // Step 3: compress nodes to LOW components
    DSU dsu_high(n);

    // initialize sizes as LOW component sizes
    vector<long long> comp(n, 0);
    for (auto &[root, sz] : compSize) {
        comp[root] = sz;
    }

    // Step 4: process HIGH edges
    for (auto &[u,v,t] : edges) {
        if (t == 1) {
            int pu = dsu_low.findPar(u);
            int pv = dsu_low.findPar(v);

            pu = dsu_high.findPar(pu);
            pv = dsu_high.findPar(pv);

            if (pu != pv) {
                ans += comp[pu] * comp[pv];

                dsu_high.unite(pu, pv);
                int newPar = dsu_high.findPar(pu);

                comp[newPar] = comp[pu] + comp[pv];
            }
        }
    }

    cout << ans << endl;
}