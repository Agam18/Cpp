#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class DSU{
    vector<int>par;
    vector<int>size;
    vector<int> nodes;
    vector<int> edges;
public:
    DSU(int n){
        par.resize(n);
        size.resize(n,1);
        nodes.resize(n,1);
        edges.resize(n,0);
        for(int i=0;i<n;i++){
            par[i]=i;
        }

    }

    int findPar(int v){
        if(par[v]==v) return v;
        return par[v]=findPar(par[v]);
    }

    int isEligible(int u,int v){
        u=findPar(u);
        v=findPar(v);
        if(u!=v) return edges[u]+1+edges[v]<=nodes[u]+nodes[v];
        return edges[u]+1<=nodes[u];
    }

    void updateEdges(int u){
        u=findPar(u);
        edges[u]++;
    }

    void unite(int u,int v){
        u=findPar(u);
        v=findPar(v);
        if(u==v) return;
        if(size[u]<size[v]) swap(u,v);
        size[u]+=size[v];
        par[v]=u;
        nodes[u]+=nodes[v];
        edges[u]+=1+edges[v];
    }
};
int main() {
    int n,m;
    cin>>n>>m;
    DSU dsu(n);
    vector<vector<int>>req(m);
    for(int i=0;i<m;i++){
        int u,v,p;
        cin>>u>>v>>p;
        req[i]={p,u,v};

    }

    sort(req.begin(),req.end());
    int ans=0;
    for(int i=m-1;i>=0;i--){
        if(dsu.isEligible(req[i][1],req[i][2])){
            if(dsu.findPar(req[i][1])!=dsu.findPar(req[i][2])){
                dsu.unite(req[i][1],req[i][2]);
                ans+=req[i][0];
            } else{
                dsu.updateEdges(req[i][1]);
                ans+=req[i][0];
            }

        }
    }
    cout<<ans<<endl;

}