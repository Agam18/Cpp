#include <bits/stdc++.h>
using namespace std;

class SGT{
public:

    // seg[] stores maximum prefix value in the segment
    // lazy[] stores pending additions for lazy propagation
    vector<long long> seg, lazy;

    SGT(int n){
        seg.resize(4*n+1);
        lazy.resize(4*n+1,0);
    }

    // Build segment tree from prefix array
    void build(int i,int low,int high,vector<long long>&a){

        // Leaf node
        if(low==high){
            seg[i]=a[low];
            return;
        }

        int mid=(low+high)/2;

        // Build left and right children
        build(2*i+1,low,mid,a);
        build(2*i+2,mid+1,high,a);

        // Store maximum prefix in this segment
        seg[i]=max(seg[2*i+1],seg[2*i+2]);
    }

    // Query maximum prefix value in range [l,r]
    long long query(int i,int low,int high,int l,int r){
        
        // Resolve pending lazy updates first
        if(lazy[i]!=0){
            seg[i]+=lazy[i];

            // propagate lazy to children
            if(high!=low){
                lazy[2*i+1]+=lazy[i];
                lazy[2*i+2]+=lazy[i];
            }

            lazy[i]=0;
        }
        
        // No overlap
        if(r<low || l>high) 
            return LLONG_MIN;

        // Complete overlap
        if(l<=low && high<=r) 
            return seg[i];

        int mid=(low+high)/2;

        // Query left and right children
        long long left=query(2*i+1,low,mid,l,r);
        long long right=query(2*i+2,mid+1,high,l,r);

        return max(left,right);
    }

    // Range update: add val to range [l,r]
    void update(int ind,int low,int high,int l,int r,long long val){
        
        // First resolve lazy value if exists
        if(lazy[ind]!=0){
            seg[ind]+=lazy[ind];

            if(high!=low){
                lazy[2*ind+1]+=lazy[ind];
                lazy[2*ind+2]+=lazy[ind];
            }

            lazy[ind]=0;
        }

        // No overlap
        if(low>r || high<l) 
            return;
        
        // Complete overlap
        if(low>=l && high<=r){
            seg[ind]+=val;

            // propagate lazily
            if(low!=high){
                lazy[2*ind+1]+=val;
                lazy[2*ind+2]+=val;
            }

            return;
        }
        
        int mid=(low+high)/2;

        // Partial overlap
        update(2*ind+1,low,mid,l,r,val);
        update(2*ind+2,mid+1,high,l,r,val);

        // Recalculate max for current node
        seg[ind]=max(seg[2*ind+1],seg[2*ind+2]);
    }
};

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q;
    cin>>n>>q;

    // a[] will store prefix sums
    vector<long long>a(n);

    // originalA[] stores the original array values
    // needed to compute difference during updates
    vector<long long>originalA(n);

    for(int i=0;i<n;i++){
        cin>>a[i];

        originalA[i]=a[i];

        // Build prefix array
        if(i>0) 
            a[i]+=a[i-1];
    }
    
    // Build segment tree over prefix array
    SGT seg(n);
    seg.build(0,0,n-1,a);

    while(q--){

        int type;
        cin>>type;

        // Update query
        if(type==1){

            int k;
            long long u;

            cin>>k>>u;

            // difference between new and old value
            long long diff = u - originalA[k-1];

            // update stored original value
            originalA[k-1] = u;

            // prefix[k..n-1] increases by diff
            seg.update(0,0,n-1,k-1,n-1,diff);
        }

        // Range query
        else{

            int a,b;
            cin>>a>>b;

            // maximum prefix in [a,b]
            long long p1 = seg.query(0,0,n-1,a-1,b-1);

            // prefix[a-1]
            long long p2 = 0;

            if(a>1)
                p2 = seg.query(0,0,n-1,a-2,a-2);

            // subtract to get prefix starting from a
            // also allow empty prefix -> max with 0
            cout<<max(0LL,p1-p2)<<"\n";
        }
    }
}