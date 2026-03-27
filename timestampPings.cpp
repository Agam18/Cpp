Solution:
int main() {
    vector<vector<int>> pings={{0,1},{1,1},{0,2},{1,2}};
    vector<vector<int>> queries={{2,2}};
    vector<vector<int>> q;
    for(int i=0;i<queries.size();i++){
        q.push_back({queries[i][0], queries[i][1],i});
    }

    sort(q.begin(),q.end());

    unordered_map<int,int> nodeVsPingCount;
    int l=0,r=0;
    int count=0;
    vector<int> ans(q.size(),0);
    for(int i=0;i<q.size();i++){
        while(r<pings.size() && pings[r][1]<=q[i][1]){
            nodeVsPingCount[pings[r][0]]++;
            if(nodeVsPingCount[pings[r][0]]==1){
                count++;
            }
            r++;
        }
        cout<<count<<endl;

        while(l<pings.size() && pings[l][1]<q[i][0]){
            nodeVsPingCount[pings[l][0]]--;
            if(nodeVsPingCount[pings[l][0]]==0){
                count--;
            }
            l++;
        }

        ans[q[i][2]]=count;
    }

    for(int i=0;i<q.size();i++){
        cout<<ans[i]<<endl;
    }
}