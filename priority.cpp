class DSU{
    vector<int> parent;
    vector<int> sz;

    public:
    DSU(int n){
        for(int i=0;i<n;i++){
            parent.push_back(i);
            sz.push_back(1);
        }
    }

    int findParent(int ind){
        if(ind==parent[ind]){
            return ind;
        }
        return parent[ind]=findParent(parent[ind]);
    }

    bool unite(int a, int b){
        int pa=findParent(a);
        int pb=findParent(b);
        if(pa==pb){
            return false;
        }

        if(sz[pa]<sz[pb]){
            swap(pa,pb);
        }

        sz[pa]+=sz[pb];
        parent[pb]=pa;
        return true;
    }

    int getTotalEdges(){
        int ans=0;
        for(int i=0;i<parent.size();i++){
            if(parent[i]==i){
                long long int componentSize=sz[i];
                ans+=(componentSize*(componentSize-1))/2;
            }
        }
        return ans;
    }

    bool isPartOfComponent(int a){
        int pa=findParent(a);
        return sz[pa]>1;
    }

    int getSize(int a){
        int pa=findParent(a);
        return sz[pa];
    }

};

//void dfs(int ind, int p, vector<vector<int>> &v, DSU &low, DSU &high, int &ans){
//
//
//    if(low.isPartOfComponent(ind) && high.isPartOfComponent(ind)){
//        int sizeOfLow=low.getSize(ind);
//        int sizeOfHigh=high.getSize(ind);
//        ans+=sizeOfHigh*sizeOfLow;
//    }
//
//    for(auto it:v[ind]){
//        if(it==p){
//            continue;
//        }
//        dfs(it,ind,v,low,high, ans);
//    }
//}

int main() {

    vector<vector<int>> edges={{}};
    int n;
    vector<vector<int>> graph(n+1,vector<int>());
    DSU low(n+1);
    DSU high(n+1);

    for(auto edge: edges){
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
        if(edge[2]==1){
            low.unite(edge[0], edge[1]);
        } else {
            high.unite(edge[0], edge[1]);
        }
    }

    int ans=low.getTotalEdges()+high.getTotalEdges();
    vector<int>visLow(n+1,0),visHigh(n+1,0);
    for(int i=1;i<=n;i++){
        int u=low.findPar(i);
        int v=high.findPar(i);
        if(low.isPartOfComponent(i) && high.isPartOfComponent(i)){
            ans+=(low.getSize(u)-1)*(high.getSize(v)-1);
        }

    }
}