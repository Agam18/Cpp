#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

void binUplifting(int u,int p,vector<vector<int>>&g,vector<vector<int>>&binUp){
    binUp[u][0]=p;
    for(int i=1;i<20;i++){
        if(binUp[u][i-1]!=-1){
            binUp[u][i]=binUp[binUp[u][i-1]][i-1];
        }
    }
    for(auto it:g[u]){
        if(p!=it){
            binUplifting(it, u, g, binUp);
        }
    }
}

void calculateLevel(int u,int p,vector<vector<int>>&g, vector<int>&lev){
    for(auto it:g[u]){
        if(it!=p){
            lev[it]=lev[u]+1;
            calculateLevel(it, u, g, lev);
        }
    }
}

int liftNode(int u,int j,vector<vector<int>>&binUp){
    if(u==-1 || j<=0) return u;
    for(int i=19;i>=0;i--){
        if((1<<i)<=j){
            return liftNode(binUp[u][i], j-(1<<i), binUp);
        }
    }
    return -1;
}

int findLCA(int u,int v,vector<vector<int>>&binUp,vector<int>&lev){
    if(lev[u]<lev[v]) swap(u,v);
    int p=-1;
    u=liftNode(u,lev[u]-lev[v],binUp);
    if(u==v) return u;
    for(int i=19;i>=0;i--){
        if(binUp[u][i]!=binUp[v][i]){
            u=binUp[u][i];
            v=binUp[v][i];
        }
    }
    return binUp[u][0];
}



void dfs(int node, int par, vector<vector<int>>&g, vector<vector<int>>&binUp,vector<int>&up,vector<int>&down) {
    for (auto child : g[node]) {
        if (child == par) continue;

        dfs(child, node,g,binUp,up,down);

        up[node] += up[child];
        down[node] += down[child];

        // check conflict on edge node-child
        if (up[child] > 0 && down[child] > 0) {
            cout << "NO\n";
            exit(0);
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n,m;
    cin>>n>>m;
    vector<vector<int>>g(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        u--;v--;
        g[u].push_back(v);
    }
    vector<int>up(n,0),down(n,0);
    vector<vector<int>>binUp(n,vector<int>(20,-1));
    vector<int>lev(n,1e9);
    lev[0]=0;
    calculateLevel(0, -1, g, lev);
    binUplifting(0, -1, g, binUp);

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        u--;v--;
        up[u]++;
        down[v]++;
        int lca = findLCA(u, v, binUp, lev);
        lca = binUp[lca][0];
        if(lca!=-1){
            up[lca]--;
            down[lca]--;
        }
    }

    dfs(0,-1,g,binUp,up,down);
    cout<<"YES"<<endl;

    return 0;
}